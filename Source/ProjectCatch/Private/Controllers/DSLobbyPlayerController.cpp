// Made by Dallai Studios - 2025

#include "Controllers/DSLobbyPlayerController.h"

#include "Actors/DSLobbyDummy.h"
#include "Blueprint/UserWidget.h"
#include "Utils/DSMacros.h"
#include "Widgets/DSLobbyWidget.h"
#include "PlayerStates/DSLobbyPlayerState.h"

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

	if (this->IsLocalPlayerController() && this->HasAuthority()) {
		this->ConfigureControllerWidget(true);
		
		ADSLobbyPlayerState* playerState = this->GetPlayerState<ADSLobbyPlayerState>();
		playerState->Server_ChangePlayerName(FText::FromString("Host"));
		playerState->Server_CheckPlayerReady();

		this->OnRep_PlayerState();
	} else {
		this->ConfigureControllerWidget(false);
	}
}

void ADSLobbyPlayerController::ConfigureControllerWidget(const bool isHost) const {
	if (!this->LobbyWidgetInstance) {
		DS_LOG_ERROR("Lobby Player Controller Error: Lobby widget instance is invalid. Can't configure controller lobby widget");
		return;
	}
	
	if (isHost) this->LobbyWidgetInstance->SetUIForHost(true);

	this->LobbyWidgetInstance->BuildWidget();

	if (this->IsLocalPlayerController()) {
		this->LobbyWidgetInstance->AddToViewport();	
	}
}

void ADSLobbyPlayerController::OnRep_PlayerState() {
	Super::OnRep_PlayerState();

	if (!this->LobbyWidgetInstance) {
		DS_LOG_ERROR("Lobby Player Controller Error: Lobby widget instance is invalid on player state RepNotify");
		return;
	}

	ADSLobbyPlayerState* playerState = this->GetPlayerState<ADSLobbyPlayerState>();
	if (!playerState) {
		DS_LOG_ERROR("Lobby Player Controller Error: Player Instance is invalid or not of type ADSLobbyPlayerState");
		return;
	}
	
	this->LobbyWidgetInstance->SetPlayerStateReference(playerState);
}

void ADSLobbyPlayerController::RequestLeaveLobby(const FString& MainMenuLevelName) {
	if (this->HasAuthority()) {
		this->DestroyDummyAndLeave();
		this->ClientTravel(MainMenuLevelName, TRAVEL_Absolute);
	} else {
		this->Server_RequestLeaveLobby(MainMenuLevelName);
	}
}

void ADSLobbyPlayerController::Server_RequestLeaveLobby_Implementation(const FString& MainMenuLevelName) {
	this->DestroyDummyAndLeave();
	this->ClientTravel(MainMenuLevelName, TRAVEL_Absolute);
}

void ADSLobbyPlayerController::DestroyDummyAndLeave() const {
	if (ADSLobbyPlayerState* playerState = this->GetPlayerState<ADSLobbyPlayerState>()) {
		if (playerState->LobbyDummy) {
			playerState->LobbyDummy->Destroy();
			playerState->LobbyDummy = nullptr;
		}
	}
}