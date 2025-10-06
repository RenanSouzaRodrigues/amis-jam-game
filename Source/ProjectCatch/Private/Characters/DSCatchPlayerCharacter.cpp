// Made by Dallai Studios - 2025

#include "Characters/DSCatchPlayerCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputSubsystemInterface.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Net/UnrealNetwork.h"
#include "Utils/DSMacros.h"


// =================================================================
// UNREAL LIFECYCLE
// =================================================================
ADSCatchPlayerCharacter::ADSCatchPlayerCharacter() {
	PrimaryActorTick.bCanEverTick = false;

	this->bReplicates = true;
	
	this->CameraSpringArm = this->CreateDefaultSubobject<USpringArmComponent>("Camera Spring Arm");
	this->CameraSpringArm->SetupAttachment(this->GetRootComponent());
	this->CameraSpringArm->bDoCollisionTest = false;

	this->PlayerCamera = this->CreateDefaultSubobject<UCameraComponent>("Player Camera");
	this->PlayerCamera->SetupAttachment(this->CameraSpringArm);

	this->HeadMesh = this->CreateDefaultSubobject<UStaticMeshComponent>("Head Mesh");
	this->HeadMesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
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
		DS_LOG_ERROR("Catcher Player Character Error: Enhanced Input Subsystem is invalid");
		return;
	}

	enhancedSubsystem->ClearAllMappings();

	if (!this->CharacterInputMappingContext) {
		DS_LOG_WARN("Cather Player Character Warning: Default input mapping context is not defined");
		return;
	}

	enhancedSubsystem->AddMappingContext(this->CharacterInputMappingContext, 0);

	UEnhancedInputComponent* inputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (!inputComponent) {
		DS_LOG_ERROR("Cather Player Character Error: input component is not defined");
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
	this->SetMovementSpeed();
	this->SetSkeletalMesh();
}



// =================================================================
// ACTION INPUT EVENTS
// =================================================================
void ADSCatchPlayerCharacter::Move(const FInputActionValue& Value) {
	const auto value = Value.Get<FVector2D>();

	const FRotator yawRotation(0, this->GetControlRotation().Yaw, 0);
	const FVector forwardVector = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
	const FVector rightVector = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
	
	this->AddMovementInput(forwardVector,  value.X);
	this->AddMovementInput(rightVector, value.Y);
}

void ADSCatchPlayerCharacter::Attack(const FInputActionValue& Value) {
	if (!this->IsTheCatcher()) return;
	this->Server_PerformAttack();
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



// =================================================================
// MULTIPLAYER PROPERTIES
// =================================================================
void ADSCatchPlayerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADSCatchPlayerCharacter, IsCatcher);
}

void ADSCatchPlayerCharacter::Server_SetIsCatcher_Implementation(const bool value) {
	this->IsCatcher = value;
	if (this->HasAuthority()) {
		this->OnRep_IsCatcher();
	}
}

void ADSCatchPlayerCharacter::OnRep_IsCatcher() const {
	this->SetMovementSpeed();
	this->SetSkeletalMesh();
}

void ADSCatchPlayerCharacter::Server_PerformAttack_Implementation() {
}



// =================================================================
// ACTOR METHODS
// =================================================================
void ADSCatchPlayerCharacter::SetMovementSpeed() const {
	this->GetCharacterMovement()->MaxWalkSpeed = this->IsCatcher ? this->CatcherMovementSpeed : this->RunnerMovementSpeed;
}

void ADSCatchPlayerCharacter::SetSkeletalMesh() const {
	this->GetMesh()->SetSkeletalMeshAsset(this->IsCatcher ? this->CatcherSkeletalMesh : this->RunnerSkeletalMesh);
	this->HeadMesh->SetStaticMesh(this->IsCatcher ? this->CatcherPumpkin : this->RunnerHair);
	this->HeadMesh->AttachToComponent(this->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, this->HeadSocketName);
	this->HeadMesh->SetRelativeRotation(FRotator(0, 0, -90));
}