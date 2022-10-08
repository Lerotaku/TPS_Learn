// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged,float)
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPS_LEARN_API USTUHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USTUHealthComponent();

	float GetHealth() const { return Health; }

	UFUNCTION(BlueprintCallable)
	bool bDead() const { return FMath::IsNearlyZero(Health); }


	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	FOnDeath OnDeath;

	FOnHealthChanged OnHealthChanged;
	
	UFUNCTION()
	void HealUpdate();

	UFUNCTION()
	void SetHealth(float NewHealth);

protected:
	virtual void BeginPlay() override;

	float Health = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,meta = (ClampMin = "0",ClampMax = "1000"),Category = "Health")
	float MaxHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal")
	bool bAutoHeal = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal")
	float HealUpdateTime = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal")
	float HealDelay = 3.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal")
	float HealModifier = 5.0f;

	FTimerHandle HealTimeHandle;

private:


};
