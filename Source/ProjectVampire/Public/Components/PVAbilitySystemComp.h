// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Abilities/PVBaseAbility.h"
#include "Components/ActorComponent.h"
#include "PVAbilitySystemComp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTVAMPIRE_API UPVAbilitySystemComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPVAbilitySystemComp();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tags")
	FGameplayTagContainer ActiveGameplayTags;

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void AddAbility(AActor* Instigator, TSubclassOf<UPVBaseAbility> AbilityClass);

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	bool StartAbility(AActor* Instigator, FName AbilityName);

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	bool StopAbility(AActor* Instigator, FName AbilityName);

	void RemoveAbility(UPVBaseAbility* AbilityToRemove);
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TArray<TSubclassOf<UPVBaseAbility>> DefaultAbilities;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TArray<UPVBaseAbility*>  Abilities;




		
};
