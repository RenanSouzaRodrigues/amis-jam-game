// Made by Dallai Studios - 2025

#include "Controllers/DSLobbyPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "PlayerStates/DSLobbyPlayerState.h"
#include "Utils/DSMacros.h"
#include "Widgets/DSLobbyWidget.h"

void ADSLobbyPlayerController::BeginPlay() {
	Super::BeginPlay();

	this->bReplicates = true;
	
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
	
	if (this->HasAuthority()) this->OnRep_PlayerState();
	
	if (this->IsLocalController()) {
		if (this->HasAuthority()) {
			this->ConfigureControllerWidget(true);
		} else {
			this->ConfigureControllerWidget(false);
		}
	}
}

void ADSLobbyPlayerController::ConfigureControllerWidget(const bool isHost) const {
	if (isHost) this->LobbyWidgetInstance->SetUIForHost(true);
	this->LobbyWidgetInstance->BuildWidget();
	this->LobbyWidgetInstance->AddToViewport();
}

void ADSLobbyPlayerController::OnRep_PlayerState() {
	Super::OnRep_PlayerState();

	ADSLobbyPlayerState* playerState = this->GetPlayerState<ADSLobbyPlayerState>();
	if (!playerState) {
		DS_LOG_ERROR("Player State is invalid on the Lobby player controller");
		return;
	}

	if (!this->LobbyWidgetInstance) {
		DS_LOG_ERROR("Lobby Widget Instance is invalid on the player state OnRep function inside Lobby player controller");
		return;
	}

	this->LobbyWidgetInstance->SetPlayerStateReference(playerState);
}
