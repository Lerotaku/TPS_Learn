// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "STUBaseWeaponActor.h"
#include "STULauncherWeapon.generated.h"

/**
 * 
 */
UCLASS()
class TPS_LEARN_API ASTULauncherWeapon : public ASTUBaseWeaponActor
{
	GENERATED_BODY()

public:

	virtual void StartFire() override;
	virtual void StopFire() override;
	virtual void MakeShot() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf<class ASTUProjectile> ProjectileClass;




	
};
