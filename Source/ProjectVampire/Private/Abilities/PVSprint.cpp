// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/PVSprint.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ProjectVampire/ProjectVampireCharacter.h"

UPVSprint::UPVSprint()
{

}

void UPVSprint::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	AProjectVampireCharacter* Player = Cast<AProjectVampireCharacter>(Instigator);

	if(!Player) return;
	
	if(!Player->CanCrouch())
		Player->UnCrouch();
	
	Player->GetCharacterMovement()->MaxWalkSpeed = Player->GetCharacterRunSpeed();
	
}

void UPVSprint::StopAction_Implementation(AActor* Instigator)
{
	Super::StopAction_Implementation(Instigator);

	AProjectVampireCharacter* Player = Cast<AProjectVampireCharacter>(Instigator);

	if(!Player) return;
	
	Player->GetCharacterMovement()->MaxWalkSpeed = Player->GetCharacterWalkSpeed();
}
