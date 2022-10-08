// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STUCharacter.generated.h"


class UCameraComponent;
class USpringArmComponent;
class USTUHealthComponent;
class UTextRenderComponent;

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

	UFUNCTION(BlueprintCallable,Category = "Movement")
	float GetMovementDirection() const;

	void OnDeath();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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


	void OnHealthChanged(float Health);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
};
