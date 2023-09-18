// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "PVBTTask_Attack.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTVAMPIRE_API UPVBTTask_Attack : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	UPROPERTY(EditAnywhere)
	UAnimMontage* AttackMontage;
};
