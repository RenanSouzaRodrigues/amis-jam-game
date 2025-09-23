// Made by Dallai Studios - 2025

#include "Actors/DSLobbyDummy.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "Widgets/DSPlayerNameWidget.h"

ADSLobbyDummy::ADSLobbyDummy() {
	PrimaryActorTick.bCanEverTick = false;

	this->bReplicates = true;
	
	this->DummyCapsule = this->CreateDefaultSubobject<UCapsuleComponent>("Dummy Capsule");
	this->SetRootComponent(this->DummyCapsule);
	
	this->DummySkeletalMesh = this->CreateDefaultSubobject<USkeletalMeshComponent>("Dummy Mesh");
	this->DummySkeletalMesh->SetupAttachment(this->DummyCapsule);

	this->PlayerNameWidget = this->CreateDefaultSubobject<UWidgetComponent>("Player Name and Confirmation");
	this->PlayerNameWidget->SetupAttachment(this->DummyCapsule);

	this->ConfirmationMesh = this->CreateDefaultSubobject<UStaticMeshComponent>("Player Confirmation Mesh");
	this->ConfirmationMesh->SetIsReplicated(true);
	this->ConfirmationMesh->SetupAttachment(this->DummyCapsule);
	this->ConfirmationMesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	this->ConfirmationMesh->SetEnableGravity(false);
}

void ADSLobbyDummy::BeginPlay() {
	Super::BeginPlay();

	if (this->ConfirmationMesh) this->ConfirmationMesh->SetHiddenInGame(true);
}

void ADSLobbyDummy::UpdatePlayerName(const FText& NewName) const {
	if (const UDSPlayerNameWidget* widget = Cast<UDSPlayerNameWidget>(this->PlayerNameWidget->GetWidget())) {
		widget->ChangePlayerName(NewName);
	}
}

void ADSLobbyDummy::TogglePlayerConfirmation(const bool value) const {
	if (this->ConfirmationMesh) {
		this->ConfirmationMesh->SetHiddenInGame(!value);
	}
}
