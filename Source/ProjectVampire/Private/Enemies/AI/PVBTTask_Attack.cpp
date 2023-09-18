// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/AI/PVBTTask_Attack.h"

#include "AIController.h"
#include "GameFramework/Character.h"

EBTNodeResult::Type UPVBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* MyController = OwnerComp.GetAIOwner();

	if(ensure(MyController))
	{
		ACharacter* MyPawn = Cast<ACharacter>(MyController->GetPawn());
		
		if(MyPawn == nullptr)
			return EBTNodeResult::Failed;

		if(AttackMontage)
		{
			MyPawn->PlayAnimMontage(AttackMontage);
		
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
