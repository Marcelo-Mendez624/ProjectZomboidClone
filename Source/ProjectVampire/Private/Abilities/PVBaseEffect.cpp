// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/PVBaseEffect.h"

#include "Components/PVAbilitySystemComp.h"



UPVBaseEffect::UPVBaseEffect():
Duration(1),
Period(1)
{
	bAutoStart = true;
}

void UPVBaseEffect::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	if(Duration > 0.f)
	{
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "StopAction", Instigator);
		GetWorld()->GetTimerManager().SetTimer(DurationHandle, Delegate, Duration, false);
	}
	if(Period > 0.f)
	{
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "ExecutePeriodicEffect", Instigator);
		GetWorld()->GetTimerManager().SetTimer(PeriodHandle, Delegate, Duration, true);
	}
	
	
}

void UPVBaseEffect::StopAction_Implementation(AActor* Instigator)
{
	if(GetWorld()->GetTimerManager().GetTimerRemaining(PeriodHandle) < KINDA_SMALL_NUMBER)
		ExecutePeriodicEffect(Instigator);
	
	Super::StopAction_Implementation(Instigator);

	GetWorld()->GetTimerManager().ClearTimer(PeriodHandle);
	GetWorld()->GetTimerManager().ClearTimer(DurationHandle);

	UPVAbilitySystemComp* Comp = GetOwningComponent();

	if(Comp)
		Comp->RemoveAbility(this);
}


void UPVBaseEffect::ExecutePeriodicEffect_Implementation(AActor* Instigator)
{
	GEngine->AddOnScreenDebugMessage(-1, Period, FColor::Green, FString::Printf(TEXT("Period remeining: %f"), Period));
}