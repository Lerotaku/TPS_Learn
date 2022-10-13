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

void ASTUBaseWeaponActor::Fire()
{

	MakeShot();

}

void ASTUBaseWeaponActor::MakeShot()
{
	const auto Player = Cast<ACharacter>(GetOwner());
	if (!Player) return;

	const auto Controller = Player->GetController<APlayerController>();
	if (!Controller) return;

	FVector ViewLocation;
	FRotator ViewRotation;
	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);

	if (!GetWorld()) return;
	const FTransform SocketTransform = WeaponComp->GetSocketTransform(MuzzleSocketName);

	const FVector TraceStart = ViewLocation; /*SocketTransform.GetLocation();*/
	const FVector ShootDirection = ViewRotation.Vector();/*SocketTransform.GetRotation().GetForwardVector();*/
	const FVector TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;


	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility);

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());

	if (HitResult.bBlockingHit)
	{

		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 3.0f, 0, 3.0f);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Red, 0, 5.0f);

	}
	else
	{
		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 3.0f, 0, 3.0f);
	}

}

//APlayerController* ASTUBaseWeaponActor::GetPlayerController() const {
//


	//const auto Controller = Player->

