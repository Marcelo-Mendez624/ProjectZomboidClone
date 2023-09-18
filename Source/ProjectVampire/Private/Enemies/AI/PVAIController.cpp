// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/AI/PVAIController.h"


void APVAIController::BeginPlay()
{
	Super::BeginPlay();

	if(BT)
		RunBehaviorTree(BT);    
}
