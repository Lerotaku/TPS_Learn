// Fill out your copyright notice in the Description page of Project Settings.


#include "STUBaseWeaponActor.h"
#include"Engine/World.h"
#include"DrawDebugHelpers.h"


DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);

// Sets default values
ASTUBaseWeaponActor::ASTUBaseWeaponActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponComp = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponComp");
	SetRootComponent(WeaponComp); 
}

// Called when the game starts or when spawned
void ASTUBaseWeaponActor::BeginPlay()
{
	Super::BeginPlay();
	check(WeaponComp);
	
}

void ASTUBaseWeaponActor::Fire()
{
	UE_LOG(LogBaseWeapon, Display, TEXT("Fireeeeee!"));
	MakeShot();
}

void ASTUBaseWeaponActor::MakeShot()
{
	if (!GetWorld()) return;

}
