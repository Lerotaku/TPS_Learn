// Fill out your copyright notice in the Description page of Project Settings.


#include "STUBaseWeaponActor.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

// Sets default values
ASTUBaseWeaponActor::ASTUBaseWeaponActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WeaponComp = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponComp");
	SetRootComponent(WeaponComp); 
}

// Called when the game starts or when spawned
void ASTUBaseWeaponActor::BeginPlay()
{
	Super::BeginPlay();
	check(WeaponComp);
	
}

void ASTUBaseWeaponActor::StartFire()
{
}

void ASTUBaseWeaponActor::StopFire()
{
}

void ASTUBaseWeaponActor::MakeShot()
{
}

APlayerController* ASTUBaseWeaponActor::GetPlayerController() const{
	const auto Player = Cast<ACharacter>(GetOwner());
	if (!Player) return nullptr;

	return Player->GetController<APlayerController>();

}

bool ASTUBaseWeaponActor::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const 
{
	const auto Controller = GetPlayerController();
	if (!Controller) return false;

	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
	return true;
}

FVector ASTUBaseWeaponActor::GetMuzzleWorldLocation() const
{
	return WeaponComp->GetSocketLocation(MuzzleSocketName);
}

bool ASTUBaseWeaponActor::GetTraceDate(FVector& TraceStart,FVector& TraceEnd) const
{

	FVector ViewLocation;
	FRotator ViewRotation;
	if(!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;


	 TraceStart = ViewLocation;
	const FVector ShootDirection = ViewRotation.Vector(),HalfRad;
	 TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	 return true;
}



void ASTUBaseWeaponActor::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd)
{
	if (!GetWorld()) return;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());

	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility);


}


