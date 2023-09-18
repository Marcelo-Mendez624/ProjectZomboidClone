// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "PVBTService_CheckAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTVAMPIRE_API UPVBTService_CheckAttackRange : public UBTService
{
	GENERATED_BODY()

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;


	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector AttackRangeKey;

public:
	UPROPERTY(EditAnywhere, Category = "AI")
	float AttackRange;
	
};
