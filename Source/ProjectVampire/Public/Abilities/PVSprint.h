// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PVBaseAbility.h"
#include "PVSprint.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTVAMPIRE_API UPVSprint : public UPVBaseAbility
{
	GENERATED_BODY()

public:
	UPVSprint();
	virtual void StartAction_Implementation(AActor* Instigator) override;
	virtual void StopAction_Implementation(AActor* Instigator) override;
	
};
