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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TraceMaxDistance = 1500.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float DamageAmount = 10.0f;

public:
	// Sets default values for this actor's properties
	ASTUBaseWeaponActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	virtual void Fire();

	void MakeShot();

	APlayerController* GetPlayerController() const;

	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
	
	FVector GetMuzzleWorldLocation() const;

	bool GetTraceDate(FVector& TraceStart, FVector& TraceEnd) const;

	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);

	void MakeDamage(const FHitResult& HitResult);
};