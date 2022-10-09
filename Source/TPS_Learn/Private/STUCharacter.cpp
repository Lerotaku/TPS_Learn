// Fill out your copyright notice in the Description page of Project Settings.


#include "STUCharacter.h"
#include"Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include"STUHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Controller.h"
// Sets default values
ASTUCharacter::ASTUCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = 1;

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
	
 }

void ASTUCharacter::OnHealthChanged(float Health)
{
		HealthTextComp->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));

}




// Called every frame
void ASTUCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const auto Health = HealthComp->GetHealth();



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





