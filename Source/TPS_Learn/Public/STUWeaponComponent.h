// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUWeaponComponent.generated.h"

class ASTUBaseWeaponActor;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPS_LEARN_API USTUWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USTUWeaponComponent();

	void Fire();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void SpawnWeapon();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapons")
	TSubclassOf<ASTUBaseWeaponActor> WeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = "Weapons")
	FName WeaponAttachPointName = "Weapon";

	UPROPERTY(EditDefaultsOnly, Category = "Weapons")
	ASTUBaseWeaponActor* CurrentWeapon = nullptr;
};
