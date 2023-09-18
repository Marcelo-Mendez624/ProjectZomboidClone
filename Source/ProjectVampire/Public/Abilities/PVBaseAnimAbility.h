// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/PVBaseAbility.h"
#include "PVBaseAnimAbility.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTVAMPIRE_API UPVBaseAnimAbility : public UPVBaseAbility
{
	GENERATED_BODY()
public:
	virtual void StartAction_Implementation(AActor* Instigator) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Anim")
	UAnimMontage* AnimMontage;

	UFUNCTION()
	void FinishAnim(ACharacter* InstigatorCharacter);
	
};
