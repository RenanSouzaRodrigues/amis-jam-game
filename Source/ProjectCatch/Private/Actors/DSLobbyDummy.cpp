// Made by Dallai Studios - 2025

#include "Actors/DSLobbyDummy.h"

#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"

ADSLobbyDummy::ADSLobbyDummy() {
	PrimaryActorTick.bCanEverTick = false;

	this->bReplicates = true;
	
	this->DummyCapsule = this->CreateDefaultSubobject<UCapsuleComponent>("Dummy Capsule");
	this->SetRootComponent(this->DummyCapsule);
	
	this->DummySkeletalMesh = this->CreateDefaultSubobject<USkeletalMeshComponent>("Dummy Mesh");
	this->DummySkeletalMesh->SetupAttachment(this->DummyCapsule);

	this->PlayerNameAndConfirmationWidget = this->CreateDefaultSubobject<UWidgetComponent>("Player Name and Confirmation");
	this->PlayerNameAndConfirmationWidget->SetupAttachment(this->DummyCapsule);
}

void ADSLobbyDummy::BeginPlay() {
	Super::BeginPlay();
}