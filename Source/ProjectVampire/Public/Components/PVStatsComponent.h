// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PVStatsComponent.generated.h"

USTRUCT(BlueprintType)
struct FStat
{
	GENERATED_BODY()

	float CurrentValue;
	float MaxValue;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnAttributeChanged, AActor*, InstigatorActor, UPVStatsComponent*, OwningComp, float, NewValue, float, Delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTVAMPIRE_API UPVStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPVStatsComponent();

	void KillActor(AActor* Instigator) const;
	bool IsAlive() const;

	void ChangeHealth(AActor* Instigator, float Delta);
	
	UPROPERTY(BlueprintAssignable, Category = "Stats")
	FOnAttributeChanged OnHealthChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "Stats")
	FOnAttributeChanged OnStaminaChanged;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Stats")
	FStat Health;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Stats")
	FStat Stamina;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Stats")
	FStat Hungry;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Stats")
	FStat Thirst;


public:
	FORCEINLINE float GetStatPercentage(FStat const Stat) const { return Stat.CurrentValue / Stat.MaxValue; }
	
	FORCEINLINE float GetHealth() const { return Health.CurrentValue; }
	FORCEINLINE float GetStamina() const { return Stamina.CurrentValue; }
	FORCEINLINE float GetHungry() const { return Hungry.CurrentValue; }
	FORCEINLINE float GetThirst() const { return Thirst.CurrentValue; }
	
};
