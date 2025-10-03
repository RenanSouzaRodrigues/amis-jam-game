// Made by Dallai Studios - 2025

#include "Characters/DSCatchPlayerCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputSubsystemInterface.h"
#include "EnhancedInputComponent.h"
#include "Utils/DSMacros.h"

ADSCatchPlayerCharacter::ADSCatchPlayerCharacter() {
	PrimaryActorTick.bCanEverTick = false;
}

void ADSCatchPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	const APlayerController* playerController = this->GetController<APlayerController>();

	if (!playerController) {
		DS_LOG_ERROR("Catcher Player Character error: player controller is invalid when trying to bind input mapping context");
		return;
	}

	const ULocalPlayer* localPlayer = playerController->GetLocalPlayer();

	if (!localPlayer) {
		DS_LOG_ERROR("Catcher Player Character error: Local player is invalid when trying to bind input mapping context");
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* enhancedSubsystem = localPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

	if (!enhancedSubsystem) {
		DS_LOG_ERROR("Boomer Shooter Character Error: Enhanced Input Subsystem is invalid");
		return;
	}

	enhancedSubsystem->ClearAllMappings();

	if (!this->CharacterInputMappingContext) {
		DS_LOG_WARN("Warning: Default input mapping context is not defined");
		return;
	}

	enhancedSubsystem->AddMappingContext(this->CharacterInputMappingContext, 0);

	UEnhancedInputComponent* inputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (!inputComponent) {
		DS_LOG_ERROR("Boomer Shooter Character Error: input component is not defined");
		return;
	}

	// Movement Input Action. -Dallai
	if (this->MovementInputAction) {
		inputComponent->BindAction(this->MovementInputAction, ETriggerEvent::Triggered, this, &ADSCatchPlayerCharacter::Move);
	}

	// Attack Input Action. -Dallai
	if (this->AttackInputAction) {
		inputComponent->BindAction(this->AttackInputAction, ETriggerEvent::Started, this, &ADSCatchPlayerCharacter::Attack);
	}
}

void ADSCatchPlayerCharacter::BeginPlay() {
	Super::BeginPlay();

	this->queryParams.AddIgnoredActor(this);
}

bool ADSCatchPlayerCharacter::IsTheCatcher() const {
	return false;
}

void ADSCatchPlayerCharacter::Move(const FInputActionValue& Value) {
	const auto value = Value.Get<FVector2D>();
	this->AddMovementInput(this->GetActorForwardVector(), value.X);
	this->AddMovementInput(this->GetActorRightVector(), value.Y);
}

void ADSCatchPlayerCharacter::Attack(const FInputActionValue& Value) {
	if (!this->IsTheCatcher()) return;
	this->PerformAttackTracer();
}

void ADSCatchPlayerCharacter::PerformAttackTracer() const {
	const FVector startLocation = GetActorLocation();
	const FVector endLocation = startLocation + (this->GetActorForwardVector() * this->CatcherDetectionDistance);
    
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this); 
    
	FHitResult HitResult;
	const bool bHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		startLocation,
		endLocation,
		FQuat::Identity,
		ECC_Pawn,
		FCollisionShape::MakeSphere(this->DetectionSphereRadius),
		QueryParams
	);
    
	if (bHit) {
		DrawDebugSphere(GetWorld(), HitResult.Location, this->DetectionSphereRadius, 12, FColor::Red, false, 2.0f);
	} else {
		DrawDebugSphere(GetWorld(), endLocation, this->DetectionSphereRadius, 12, FColor::Green, false, 2.0f);
	}
    
	if (bHit) {
		if (const auto actor = HitResult.GetActor()) {
			DS_LOG_INFO("HIT ACTOR");
		}
	}
}
