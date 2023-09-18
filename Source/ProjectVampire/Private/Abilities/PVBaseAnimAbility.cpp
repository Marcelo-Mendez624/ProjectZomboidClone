// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/PVBaseAnimAbility.h"

#include "GameFramework/Character.h"

void UPVBaseAnimAbility::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	ACharacter* InstigatorCharacter = Cast<ACharacter>(Instigator);
	
	if(InstigatorCharacter && AnimMontage)
	{
		const float AnimDuration = InstigatorCharacter->PlayAnimMontage(AnimMontage);
		
		FTimerHandle TimerHandle_AttackDelay;
		FTimerDelegate Delegate; // Delegate to bind function with parameters
		Delegate.BindUFunction(this, "FinishAnim", InstigatorCharacter); // Character is the parameter we wish to pass with the function.
		
		InstigatorCharacter->GetWorld()->GetTimerManager().SetTimer(TimerHandle_AttackDelay, Delegate, AnimDuration, false);
	}
}

void UPVBaseAnimAbility::FinishAnim(ACharacter* InstigatorCharacter)
{
	StopAction_Implementation(InstigatorCharacter);
}
