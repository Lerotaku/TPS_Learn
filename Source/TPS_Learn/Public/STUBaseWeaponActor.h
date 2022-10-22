// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBaseWeaponActor.generated.h"

UCLASS()
class TPS_LEARN_API ASTUBaseWeaponActor : public AActor
{
	GENERATED_BODY()

public:


protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USkeletalMeshComponent* WeaponComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float TraceMaxDistance = 1500.0f;







public:
	// Sets default values for this actor's properties
	ASTUBaseWeaponActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	virtual void StartFire();

	virtual void StopFire();

	virtual void MakeShot();

	APlayerController* GetPlayerController() const;

	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
	
	FVector GetMuzzleWorldLocation() const;

	virtual bool GetTraceDate(FVector& TraceStart, FVector& TraceEnd) const;

	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);

};