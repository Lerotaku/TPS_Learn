// Fill out your copyright notice in the Description page of Project Settings.


#include "STUWeaponComponent.h"
#include <STUBaseWeaponActor.h>
#include <GameFramework/Character.h>

// Sets default values for this component's properties
USTUWeaponComponent::USTUWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}



// Called when the game starts
void USTUWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();
	
}

void USTUWeaponComponent::SpawnWeapon()
{
	if (!GetWorld()) return;

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	CurrentWeapon = GetWorld()->SpawnActor<ASTUBaseWeaponActor>(WeaponClass);
	if (!CurrentWeapon) return;

	FAttachmentTransformRules AttachMentRules(EAttachmentRule::SnapToTarget, false);
	CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachMentRules, WeaponSocketName);
	CurrentWeapon->SetOwner(Character);

	
}

void USTUWeaponComponent::Fire()
{
	if (!CurrentWeapon) return;
	CurrentWeapon->Fire();
}
