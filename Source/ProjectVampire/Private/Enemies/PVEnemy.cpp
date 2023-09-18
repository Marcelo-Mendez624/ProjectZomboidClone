// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/PVEnemy.h"

#include "Perception/AIPerceptionComponent.h"


// Sets default values
APVEnemy::APVEnemy():
VisibleTime(1.5f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
	GetMesh()->SetVisibility(false);
}

// Called when the game starts or when spawned
void APVEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

void APVEnemy::InFOV_Implementation()
{
	if(!GetMesh()->IsVisible())
	{
		GetMesh()->SetVisibility(true);

		GetWorldTimerManager().SetTimer(InvisibleHandle, this, &APVEnemy::TurnInvisible, VisibleTime, false);
	}
	else
	{
		GetWorldTimerManager().ClearTimer(InvisibleHandle);
		
		GetWorldTimerManager().SetTimer(InvisibleHandle, this, &APVEnemy::TurnInvisible, VisibleTime, false );
	}
}

void APVEnemy::TurnInvisible()
{
	GetMesh()->SetVisibility(false);
	GetWorldTimerManager().ClearTimer(InvisibleHandle);
}

