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

public:	
	// Sets default values for this actor's properties
	ASTUBaseWeaponActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

<<<<<<< HEAD
<<<<<<< HEAD
	virtual void Fire();

	void MakeShot();

=======
>>>>>>> parent of 91241d6 (射击功能)
=======
>>>>>>> parent of 91241d6 (射击功能)
};
