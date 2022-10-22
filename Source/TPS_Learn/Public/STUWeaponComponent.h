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
	
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void SpawnWeapons();


	void StartFire();

	void StopFire();

	void AttachWeaponToSocket(ASTUBaseWeaponActor* Weapon, USceneComponent* SceneComponent, const FName& SocketName);

	void EquipWeapon(int32 WeaponIndex);

	void NextWeapon();

protected:

	UPROPERTY(EditDefaultsOnly,Category = "Weapon")
	TArray<TSubclassOf<ASTUBaseWeaponActor>> WeaponClasses;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponEquipSocketName = "Weapon";

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponArmorySocketName = "ArmorySocket";

	UPROPERTY()
	ASTUBaseWeaponActor* CurrentWeapon = nullptr;

	UPROPERTY()
	TArray<ASTUBaseWeaponActor*> Weapons ;
	
	int32 CurrentWeaponIndex = 0;

};
