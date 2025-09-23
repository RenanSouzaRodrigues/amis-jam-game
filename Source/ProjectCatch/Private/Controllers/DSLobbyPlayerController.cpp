// Made by Dallai Studios - 2025

#include "Controllers/DSLobbyPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Utils/DSMacros.h"
#include "Widgets/DSLobbyWidget.h"

void ADSLobbyPlayerController::BeginPlay() {
	Super::BeginPlay();
	
	this->bShowMouseCursor = true;
	this->SetInputMode(FInputModeUIOnly());
	
	if (!this->LobbyWidgetClass) {
		DS_LOG_ERROR("Lobby Player Controller Error: Lobby Widget Class is not defined");
		return;
	}

	this->LobbyWidgetInstance = CreateWidget<UDSLobbyWidget>(this->GetWorld(), this->LobbyWidgetClass);

	if (!this->LobbyWidgetInstance) {
		DS_LOG_ERROR("Lobby Player Controller Error: Lobby Widget instance is invalid");
		return;
	}

	if (this->HasAuthority()) {
		this->ConfigureControllerWidget(true);
	}
}

void ADSLobbyPlayerController::ConfigureControllerWidget(const bool isHost) const {
	if (isHost) this->LobbyWidgetInstance->SetUIForHost(true);

	this->LobbyWidgetInstance->BuildWidget();

	if (this->IsLocalPlayerController()) {
		this->LobbyWidgetInstance->AddToViewport();	
	}
}

void ADSLobbyPlayerController::OnRep_PlayerState() {
	Super::OnRep_PlayerState();
	this->ConfigureControllerWidget(false);
}
