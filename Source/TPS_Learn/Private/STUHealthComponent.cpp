// Fill out your copyright notice in the Description page of Project Settings.


#include "STUHealthComponent.h"
#include"GameFramework/Actor.h"
#include"Engine/World.h"
#include"TimerManager.h"

// Sets default values for this component's properties
USTUHealthComponent::USTUHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;


}


// Called when the game starts
void USTUHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	SetHealth(MaxHealth);

	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamage);
	}
	
}


void USTUHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if(Damage <= 0.0f || bDead()||GetWorld())
	{
		return ;
	}
	SetHealth(Health - Damage);
	GetWorld()->GetTimerManager().ClearTimer(HealTimeHandle);
	
	if (bDead())
	{
		OnDeath.Broadcast();
	}
	else if (bAutoHeal )
	{
		GetWorld()->GetTimerManager().SetTimer(HealTimeHandle, this, &USTUHealthComponent::HealUpdate, HealUpdateTime, 1, HealDelay);
	}
}

void USTUHealthComponent::HealUpdate()
{
	SetHealth(Health + HealModifier);

	if (FMath::IsNearlyEqual(Health,MaxHealth )&& GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(HealTimeHandle);
	}
		
}

void USTUHealthComponent::SetHealth(float NewHealth)
{
	Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(Health);
}
