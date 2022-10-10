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

	// Called when the game starts
	virtual void BeginPlay() override;

	void SpawnWeapon();


	void Fire();

protected:
	UPROPERTY(EditDefaultsOnly,Category = "Weapon")
	TSubclassOf<ASTUBaseWeaponActor> WeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponSocketName = "Weapon";

	UPROPERTY()
	ASTUBaseWeaponActor* CurrentWeapon = nullptr;


};
