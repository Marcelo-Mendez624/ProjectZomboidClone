// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PVHiddenActorInterface.h"
#include "GameFramework/Character.h"
#include "PVEnemy.generated.h"

UCLASS()
class PROJECTVAMPIRE_API APVEnemy : public ACharacter, public IPVHiddenActorInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APVEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Interface implementation when character sees the character 
	virtual void InFOV_Implementation() override;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Visible")
	float VisibleTime;

	UPROPERTY(EditAnywhere, Category = "AI")
	class UAIPerceptionComponent* AIPerception;

private:
	FTimerHandle InvisibleHandle;

	void TurnInvisible();
	

};
