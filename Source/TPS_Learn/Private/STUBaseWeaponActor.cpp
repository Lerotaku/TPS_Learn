// Fill out your copyright notice in the Description page of Project Settings.


#include "STUBaseWeaponActor.h"

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

<<<<<<< HEAD
<<<<<<< HEAD
void ASTUBaseWeaponActor::Fire()
{
	UE_LOG(LogBaseWeapon, Display, TEXT("Fireeeeee!"));

	MakeShot();

}

void ASTUBaseWeaponActor::MakeShot()
{
	if (!GetWorld()) return;
	const FTransform SocketTransform = WeaponComp->GetSocketTransform(MuzzleSocketName);

	const FVector TraceStart = SocketTransform.GetLocation();
	const FVector ShootDirection = SocketTransform.GetRotation().GetForwardVector();
	const FVector TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 3.0f, 0, 3.0f);

}
=======


>>>>>>> parent of 91241d6 (射击功能)
=======


>>>>>>> parent of 91241d6 (射击功能)
