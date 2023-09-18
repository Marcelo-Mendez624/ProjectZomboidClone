// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PVStatsComponent.h"

#include "ProjectVampire/ProjectVampireCharacter.h"

// Sets default values for this component's properties
UPVStatsComponent::UPVStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	Health.MaxValue = 100;
	Health.CurrentValue = Health.MaxValue;

	Stamina.MaxValue = 100;
	Stamina.CurrentValue = Stamina.MaxValue;
	
	Hungry.MaxValue = 100;
	Hungry.CurrentValue = Hungry.MaxValue;
	
	Thirst.MaxValue = 100;
	Thirst.CurrentValue = Thirst.MaxValue;

	

	// ...
}

void UPVStatsComponent::KillActor(AActor* Instigator) const
{
	if(AProjectVampireCharacter* CharacterInstigator = Cast<AProjectVampireCharacter>(GetOwner()))
		CharacterInstigator->AddKillCount();
	
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("%ls is dead"), *GetOwner()->GetName()));
}

bool UPVStatsComponent::IsAlive() const
{
	if(Health.CurrentValue > 0)
		return true;

	return false;
}

void UPVStatsComponent::ChangeHealth(AActor* Instigator, float Delta)
{
	if(Health.CurrentValue + Delta >= Health.MaxValue)
	{
		Delta = Health.MaxValue - Health.CurrentValue;
		Health.CurrentValue = Health.MaxValue;
	}
	else
	{
		Health.CurrentValue += Delta;
		
		if(GetHealth() <= 0)
			KillActor(Instigator);
	}
	
	OnHealthChanged.Broadcast(Instigator, this, Health.CurrentValue, Delta);
	
}


// Called when the game starts
void UPVStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


