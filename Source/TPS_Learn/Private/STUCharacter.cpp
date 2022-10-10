// Fill out your copyright notice in the Description page of Project Settings.


#include "STUCharacter.h"
#include"Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include"STUHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Controller.h"
#include"STUBaseWeaponActor.h"
// Sets default values
ASTUCharacter::ASTUCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = 1;
	SpringArmComp->TargetArmLength = 275.0f;
	SpringArmComp->SocketOffset = FVector(0, 75, 50);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	this->bUseControllerRotationPitch = 0;
	this->bUseControllerRotationRoll = 0;
	this->bUseControllerRotationYaw = 0;

	GetCharacterMovement()->bOrientRotationToMovement = 1;
	GetCharacterMovement()->MaxWalkSpeed = NormalWalkSpeed;

	HealthComp = CreateDefaultSubobject<USTUHealthComponent>("HealthComp");

	HealthTextComp = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComp");
	HealthTextComp->SetupAttachment(RootComponent);
	HealthTextComp->SetOwnerNoSee(1);

}

void ASTUCharacter::MoveForward(float Value)
{
	if (Value == 0) return;
	FRotator YawDirection = FRotator(0, GetControlRotation().Yaw, 0);
	FVector Direction = FRotationMatrix(YawDirection).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void ASTUCharacter::MoveRight(float Value)
{
	if (Value == 0) return;
	FRotator YawDirection = FRotator(0, GetControlRotation().Yaw, 0);
	FVector Direction = FRotationMatrix(YawDirection).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void ASTUCharacter::Sprint()
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = NormalSprintSpeed;
	}
}

void ASTUCharacter::StopSprint()
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = NormalWalkSpeed;
	}
}

float ASTUCharacter::GetMovementDirection() const
{
	if (GetVelocity().IsZero()) return 0.0f;
	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
	const auto Degree = FMath::RadiansToDegrees(AngleBetween);
	return CrossProduct.IsZero()?Degree:Degree * FMath::Sign(CrossProduct.Z);
}

void ASTUCharacter::OnGroundLanded(const FHitResult& Hit)
{
	const auto FallVelocityZ = -GetCharacterMovement()->Velocity.Z;
	UE_LOG(LogTemp, Error, TEXT("On Landed:%f"), FallVelocityZ);

	if (FallVelocityZ < LandDamageVelocity.X)
	{
		return;
	}

	const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandDamageVelocity, LandDamage, FallVelocityZ);
	UE_LOG(LogTemp, Error, TEXT("FinalDamage:%f"), FinalDamage);
	TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);
}

void ASTUCharacter::OnDeath()
{
	PlayAnimMontage(DefaultAnimMontage);
	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(5.0f);

	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
}




// Called when the game starts or when spawned
void ASTUCharacter::BeginPlay()
{
	Super::BeginPlay();
	check(HealthComp);
	check(HealthTextComp);
	check(GetCharacterMovement());

	OnHealthChanged(HealthComp->GetHealth());
	HealthComp->OnDeath.AddUObject(this, &ASTUCharacter::OnDeath);
	HealthComp->OnHealthChanged.AddUObject(this, &ASTUCharacter::OnHealthChanged);
	
	SpawnWeapon();


	LandedDelegate.AddDynamic(this, &ASTUCharacter::OnGroundLanded);

 }

void ASTUCharacter::OnHealthChanged(float Health)
{
		HealthTextComp->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));

}

void ASTUCharacter::SpawnWeapon()
{
	if (!GetWorld()) return;
	const auto Weapon = GetWorld()->SpawnActor<ASTUBaseWeaponActor>(WeaponClass);

	if (Weapon)
	{
		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, 0);
		Weapon->AttachToComponent(GetMesh(), AttachmentRules, "Weapon");
	}
}




// Called every frame
void ASTUCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASTUCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (PlayerInputComponent)
	{
		PlayerInputComponent->BindAxis("MoveForward", this, &ASTUCharacter::MoveForward);
		PlayerInputComponent->BindAxis("MoveRight", this, &ASTUCharacter::MoveRight);
		PlayerInputComponent->BindAxis("LookUp", this, &ASTUCharacter::AddControllerPitchInput);
		PlayerInputComponent->BindAxis("TurnRight", this, &ASTUCharacter::AddControllerYawInput);

		PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASTUCharacter::Jump);
		PlayerInputComponent->BindAction("Jump", IE_Released, this, &ASTUCharacter::StopJumping);

		PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ASTUCharacter::Sprint);
		PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ASTUCharacter::StopSprint);
	}
	
}





