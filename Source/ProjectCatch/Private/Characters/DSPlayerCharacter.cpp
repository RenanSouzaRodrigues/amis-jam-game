// Made by Dallai Studios - 2025

#include "Characters/DSPlayerCharacter.h"

ADSPlayerCharacter::ADSPlayerCharacter() {
	this->PrimaryActorTick.bCanEverTick = false;
	this->bReplicates = true;

	this->CatcherHat = this->CreateDefaultSubobject<UStaticMeshComponent>("Catcher Hat");
	this->CatcherHat->SetupAttachment(this->GetMesh());
	this->CatcherHat->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
}

void ADSPlayerCharacter::BeginPlay() {
	Super::BeginPlay();
	
}

void ADSPlayerCharacter::Move(const float AxisValueX, const float AxisValueY) {
	if (AxisValueX == 0.f && AxisValueY == 0.f) return;
	this->AddMovementInput(this->GetActorForwardVector(), AxisValueX);
	this->AddMovementInput(this->GetActorRightVector(), AxisValueY);
}

void ADSPlayerCharacter::Attack() {
	
}