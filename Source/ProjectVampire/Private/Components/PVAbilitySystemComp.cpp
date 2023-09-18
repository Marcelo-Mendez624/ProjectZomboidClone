// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PVAbilitySystemComp.h"

#include "GameFramework/Character.h"

// Sets default values for this component's properties
UPVAbilitySystemComp::UPVAbilitySystemComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void UPVAbilitySystemComp::BeginPlay()
{
	Super::BeginPlay();

	for (const TSubclassOf<UPVBaseAbility> NewAbility : DefaultAbilities)
		AddAbility(GetOwner(), NewAbility);
}


void UPVAbilitySystemComp::AddAbility(AActor* Instigator, TSubclassOf<UPVBaseAbility> AbilityClass)
{
	if(!ensure(AbilityClass)) return;

	if(UPVBaseAbility* NewAbility = NewObject<UPVBaseAbility>(this, AbilityClass))
	{
		Abilities.Add(NewAbility);

		if(NewAbility->bAutoStart && NewAbility->CanStart(Instigator))
			StartAbility(Instigator, NewAbility->AbilityName);
	}
}

bool UPVAbilitySystemComp::StartAbility(AActor* Instigator, FName AbilityName)
{
	for(UPVBaseAbility* Ability : Abilities)
		if(Ability && Ability->AbilityName == AbilityName)
		{
			if(Ability->CanStart(Instigator))
			{
				Ability->StartAction(Instigator);
				return true;
			}
		}
	
	return false;
}

bool UPVAbilitySystemComp::StopAbility(AActor* Instigator, FName AbilityName)
{
	for(UPVBaseAbility* Ability : Abilities)
		if(Ability->IsRunning() && Ability && Ability->AbilityName == AbilityName)
		{
			Ability->StopAction(Instigator);
			return true;
		}
	
	return false;
}

void UPVAbilitySystemComp::RemoveAbility(UPVBaseAbility* AbilityToRemove)
{
	if (!ensure(AbilityToRemove && !AbilityToRemove->IsRunning())) return;
	
	Abilities.Remove(AbilityToRemove);
}
