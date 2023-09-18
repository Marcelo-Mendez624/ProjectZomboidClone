// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "ProjectVampireCharacter.generated.h"


UCLASS(config=Game)
class AProjectVampireCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Run Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* RunAction;
	/** Run Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* CrouchAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;
	
	/** Zoom in and Zoom out Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ZoomAction;

	/** Guard Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* GuardAction;
	
	/** Attack Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* AttackAction;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	class UPVAbilitySystemComp* AbilitySystemComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	class UPVStatsComponent* StatsComponent;



public:
	AProjectVampireCharacter();
	virtual void Tick(float DeltaSeconds) override;

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			
	void CameraZoom(const FInputActionValue& Value);

	void InGuard(const FInputActionValue& Value);
	void Attack(const FInputActionValue& Value);
	
	void StartSprint(const FInputActionValue& Value);
	void EndSprint(const FInputActionValue& Value);
	void StartCrouch(const FInputActionValue& Value);

	void TraceFieldOfView();
	
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Vision")
	float HalfAngle;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Vision")
	float DeltaAngle;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Vision")
	float VisionDistance;
	
	
private:
	// Movement Settings
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"), Category = "Movement")
	float CharacterWalkSpeed;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"), Category = "Movement")
	float CharacterRunSpeed;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"), Category = "Movement")
	float CharacterCrouchSpeed;
	
	// Camera settings
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"), Category = "Camera")
	float CameraZoomSpeed;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"), Category = "Camera")
	int MinCameraZoom;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"), Category = "Camera")
	int MaxCameraZoom;

	UPROPERTY()
	int KillCount;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	// Returns Character crouch speed
	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetCharacterCrouchSpeed () const { return CharacterCrouchSpeed; }
	UFUNCTION(BlueprintPure)
	FORCEINLINE UPVStatsComponent* GetStatComponent () const { return StatsComponent; }
	// Returns Character walk speed
	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetCharacterWalkSpeed() const { return CharacterWalkSpeed; }
	// Returns Character run speed
	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetCharacterRunSpeed() const { return CharacterRunSpeed; }

	int GetKillCount() const { return KillCount; }
	int AddKillCount() { return ++KillCount; }

};

