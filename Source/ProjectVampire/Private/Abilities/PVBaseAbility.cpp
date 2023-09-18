// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/Abilities/PVBaseAbility.h"

#include "Components/PVAbilitySystemComp.h"


UPVAbilitySystemComp* UPVBaseAbility::GetOwningComponent() const
{
	if(GetOuter())
		return Cast<UPVAbilitySystemComp>(GetOuter());

	return nullptr;
}

void UPVBaseAbility::StartAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Warning, TEXT("Activate Ability"));

	bIsRunning = true;
	
	GetOwningComponent()->ActiveGameplayTags.AppendTags(GrantTags);
}

void UPVBaseAbility::StopAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Warning, TEXT("Cancel Ability"));

	bIsRunning = false;
	
	GetOwningComponent()->ActiveGameplayTags.RemoveTags(GrantTags);
}

bool UPVBaseAbility::CanStart_Implementation(AActor* Instigator)
{
	if(IsRunning()) return false;
	
	if(GetOwningComponent()->ActiveGameplayTags.HasAny(BlockTags))
		return false;

	return true;
}

bool UPVBaseAbility::IsRunning()
{
	return bIsRunning;
}
