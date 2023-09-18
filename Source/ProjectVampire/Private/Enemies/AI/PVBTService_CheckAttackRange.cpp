// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/AI/PVBTService_CheckAttackRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UPVBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();

	if(ensure(BlackboardComponent))
	{
		const AActor* TargetActor =Cast<AActor>(BlackboardComponent->GetValueAsObject("TargetActor"));
		
		if(!TargetActor) return;

		const AAIController* MyController = OwnerComp.GetAIOwner();
		if(ensure(MyController))
		{
			if(ensure(MyController->GetPawn()))
			{
				const float DistanceToCharacter = FVector::Distance(TargetActor->GetActorLocation(), MyController->GetPawn()->GetActorLocation());
				const bool bWithinRange = DistanceToCharacter <= AttackRange;
				
				BlackboardComponent->SetValueAsBool(AttackRangeKey.SelectedKeyName, (bWithinRange));
			}
		}

	}
}
