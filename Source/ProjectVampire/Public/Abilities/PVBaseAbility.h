// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/NoExportTypes.h"
#include "PVBaseAbility.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PROJECTVAMPIRE_API UPVBaseAbility : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent)
	void StartAction(AActor* Instigator);
	UFUNCTION(BlueprintNativeEvent)
	void StopAction(AActor* Instigator);

	UFUNCTION(BlueprintNativeEvent)
	bool CanStart(AActor* Instigator);

	UFUNCTION(BlueprintCallable)
	bool IsRunning();
	

	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	FName AbilityName;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	bool bAutoStart;

protected:
	UFUNCTION(Blueprintable, Category = "Abilities")
	UPVAbilitySystemComp* GetOwningComponent() const;
	
	UPROPERTY(EditDefaultsOnly, Category = "Tags")
	FGameplayTagContainer GrantTags;
	
	UPROPERTY(EditDefaultsOnly, Category = "Tags")
	FGameplayTagContainer BlockTags;

	UPROPERTY(BlueprintReadWrite)
	bool bIsRunning;
	
};
