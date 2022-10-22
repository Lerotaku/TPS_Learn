// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "STUBaseWeaponActor.h"
#include "STURifleWeapon.generated.h"

/**
 * 
 */
UCLASS()
class TPS_LEARN_API ASTURifleWeapon : public ASTUBaseWeaponActor
{
	GENERATED_BODY()

public:

	virtual void StartFire() override;

	virtual void StopFire() override;

	virtual void MakeShot() override;

	virtual bool GetTraceDate(FVector& TraceStart, FVector& TraceEnd) const override;

	void MakeDamage(const FHitResult& HitResult);  

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FTimerHandle ShotTimerHandle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float TimeBetweenShot = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float BulletSpread = 1.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float DamageAmount = 10.0f;
	
};
