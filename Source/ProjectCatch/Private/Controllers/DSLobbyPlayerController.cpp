// Made by Dallai Studios - 2025

#include "Controllers/DSLobbyPlayerController.h"

#include "Actors/DSLobbyDummy.h"
#include "Blueprint/UserWidget.h"
#include "PlayerStates/DSLobbyPlayerState.h"
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
		this->ConfigurePlayerStateDummy(true);
	} else {
		this->ConfigureControllerWidget(false);
	}
}

void ADSLobbyPlayerController::ConfigureControllerWidget(const bool isHost) const {
	if (isHost) this->LobbyWidgetInstance->SetUIForHost(true);
	this->LobbyWidgetInstance->BuildWidget();
	this->LobbyWidgetInstance->AddToViewport();
}

void ADSLobbyPlayerController::ConfigurePlayerStateDummy(const bool isHost) const {
	if (isHost) {
		this->GetPlayerState<ADSLobbyPlayerState>()->Server_ChangePlayerName(FText::FromString("Server"));
	} else {
		this->GetPlayerState<ADSLobbyPlayerState>()->Server_ChangePlayerName(FText::FromString("Client"));
	}
	
	if (!this->LobbyWidgetInstance) {
		DS_LOG_ERROR("Lobby Widget Instance is invalid on the player state OnRep function inside Lobby player controller");
		return;
	}

	this->LobbyWidgetInstance->SetPlayerStateReference(this->GetPlayerState<ADSLobbyPlayerState>());
}

void ADSLobbyPlayerController::OnRep_PlayerState() {
	Super::OnRep_PlayerState();
	DS_LOG_ERROR("This is client");
	this->ConfigurePlayerStateDummy(false);
}
