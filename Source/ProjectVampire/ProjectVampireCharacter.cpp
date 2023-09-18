// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectVampireCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PVHiddenActorInterface.h"
#include "Components/PVAbilitySystemComp.h"
#include "Components/PVStatsComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"


//////////////////////////////////////////////////////////////////////////
// AProjectVampireCharacter

AProjectVampireCharacter::AProjectVampireCharacter():
	HalfAngle(55),
	DeltaAngle(1),
	VisionDistance(3000),
	CharacterWalkSpeed(135),
	CharacterRunSpeed(600),
	CharacterCrouchSpeed(60),
	CameraZoomSpeed(10),
	MinCameraZoom(200),
	MaxCameraZoom(2200)
	
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	SetActorTickEnabled(true);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = CharacterWalkSpeed;
	GetCharacterMovement()->MaxWalkSpeedCrouched = CharacterCrouchSpeed;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	AbilitySystemComp = CreateDefaultSubobject<UPVAbilitySystemComp>(TEXT("AbilitySystemComp"));
	StatsComponent = CreateDefaultSubobject<UPVStatsComponent>(TEXT("StatComponent"));
}

void AProjectVampireCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	TraceFieldOfView();
}

void AProjectVampireCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}



//////////////////////////////////////////////////////////////////////////
// Input

void AProjectVampireCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		//Sprint
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Triggered, this, &AProjectVampireCharacter::StartSprint);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Completed, this, &AProjectVampireCharacter::EndSprint);
		
		//crouch
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &AProjectVampireCharacter::StartCrouch);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AProjectVampireCharacter::Move);
		
		
		//Looking
		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &AProjectVampireCharacter::CameraZoom);
		
		EnhancedInputComponent->BindAction(GuardAction, ETriggerEvent::Triggered, this, &AProjectVampireCharacter::InGuard);
		
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AProjectVampireCharacter::Attack);

	}

}

void AProjectVampireCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AProjectVampireCharacter::Look(const FInputActionValue& Value)
{

}



void AProjectVampireCharacter::CameraZoom(const FInputActionValue& Value)
{
	// input is a float
	const float ZoomValue = Value.Get<float>();

	if(ZoomValue != 0)
	{
		if(CameraBoom->TargetArmLength + ZoomValue * CameraZoomSpeed >= MinCameraZoom && CameraBoom->TargetArmLength + ZoomValue * CameraZoomSpeed <= MaxCameraZoom)
			CameraBoom->TargetArmLength += ZoomValue * CameraZoomSpeed;
	}
}

void AProjectVampireCharacter::InGuard(const FInputActionValue& Value)
{
	if(AbilitySystemComp)
		AbilitySystemComp->StartAbility(this, "Guard");

	if(AbilitySystemComp)
		AbilitySystemComp->StopAbility(this, "Guard");
}

void AProjectVampireCharacter::Attack(const FInputActionValue& Value)
{
	if(AbilitySystemComp)
		AbilitySystemComp->StartAbility(this, "Attack");
}

void AProjectVampireCharacter::StartSprint(const FInputActionValue& Value)
{
	if(AbilitySystemComp)
		AbilitySystemComp->StartAbility(this, "Sprint");
}

void AProjectVampireCharacter::EndSprint(const FInputActionValue& Value)
{
	if(AbilitySystemComp)
		AbilitySystemComp->StopAbility(this, "Sprint");
}

void AProjectVampireCharacter::StartCrouch(const FInputActionValue& Value)
{
	if(!bIsCrouched)
	{
		Crouch();
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Crouch"));
	}
	else
	{
		UnCrouch();
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("UnCrouch"));
	}
		
}

void AProjectVampireCharacter::TraceFieldOfView()
{
	const float ViewAngle = HalfAngle * 2;

	const int NumberOfSections = ceil(ViewAngle / DeltaAngle);

	float DAngle = ViewAngle / NumberOfSections;

	for(int i=0; i < NumberOfSections; i++)
	{
		const float LCurrentAngle = (i * DAngle) - HalfAngle;

		FHitResult  HitResult;
		FVector Start = GetActorLocation();
		FVector End = UKismetMathLibrary::RotateAngleAxis(GetActorForwardVector(), LCurrentAngle, FVector(0, 0, 1)) * VisionDistance + Start;
		
		const bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility);

		if(bHit)
		{
			const IPVHiddenActorInterface* Interface = Cast<IPVHiddenActorInterface>(HitResult.GetActor());
			
			if(HitResult.GetActor()->GetClass()->ImplementsInterface(UPVHiddenActorInterface::StaticClass()))
				Interface->Execute_InFOV(HitResult.GetActor());
		}
	}
} 


