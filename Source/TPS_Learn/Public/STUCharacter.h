// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STUCharacter.generated.h"


class UCameraComponent;
class USpringArmComponent;
class USTUHealthComponent;
class UTextRenderComponent;
class ASTUBaseWeaponActor;

UCLASS()
class TPS_LEARN_API ASTUCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASTUCharacter();

	void MoveForward(float Value);

	void MoveRight(float Value);

	void Sprint();

	void StopSprint();

	void OnDeath();

	void OnHealthChanged(float Health);

	void SpawnWeapon();

	UFUNCTION(BlueprintCallable,Category = "Movement")
	float GetMovementDirection() const;

	UFUNCTION()
	void OnGroundLanded(const FHitResult& Hit);





protected:

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="CharacterSpeed")
	float NormalWalkSpeed = 450;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterSpeed")
	float NormalSprintSpeed = 900;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USTUHealthComponent* HealthComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UTextRenderComponent* HealthTextComp;

	UPROPERTY(EditDefaultsOnly,Category = "Animations")
	UAnimMontage* DefaultAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Weapons")
	TSubclassOf<ASTUBaseWeaponActor> WeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	FVector2D LandDamageVelocity = FVector2D(900.0f, 1200.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	FVector2D LandDamage = FVector2D(10.0f, 100.0f);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
