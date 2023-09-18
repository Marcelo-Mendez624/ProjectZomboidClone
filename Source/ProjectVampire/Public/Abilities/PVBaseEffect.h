// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/PVBaseAbility.h"
#include "PVBaseEffect.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTVAMPIRE_API UPVBaseEffect : public UPVBaseAbility
{
	GENERATED_BODY()

public:
	UPVBaseEffect();
	
	virtual void StartAction_Implementation(AActor* Instigator) override;
	virtual void StopAction_Implementation(AActor* Instigator) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Effect")
	float Duration;
	
	UPROPERTY(EditAnywhere, Category = "Effect")
	float Period;

	FTimerHandle PeriodHandle;
	FTimerHandle DurationHandle;

	UFUNCTION(BlueprintNativeEvent, Category = "Effect")
	void ExecutePeriodicEffect(AActor* Instigator);
	
	
};
