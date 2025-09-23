// Made by Dallai Studios - 2025

#include "Actors/DSLobbyDummy.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "Utils/DSMacros.h"
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
	this->ConfirmationMesh->SetupAttachment(this->DummyCapsule);
	this->ConfirmationMesh->SetHiddenInGame(true);
}

void ADSLobbyDummy::BeginPlay() {
	Super::BeginPlay();
}

void ADSLobbyDummy::UpdatePlayerName(const FText& NewName) const {
	if (const UDSPlayerNameWidget* widget = Cast<UDSPlayerNameWidget>(this->PlayerNameWidget->GetWidget())) {
		widget->ChangePlayerName(NewName);
	} else {
		DS_LOG_ERROR("Player Name Widget is not defined on the Lobby Dummy");
	}
}

void ADSLobbyDummy::TogglePlayerConfirmation() {
	if (this->ConfirmationMesh) {
		this->ConfirmationMesh->SetHiddenInGame(!this->ConfirmationMesh->bHiddenInGame);
	}
}
