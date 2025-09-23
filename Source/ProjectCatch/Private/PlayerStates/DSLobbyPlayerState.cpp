// Made by Dallai Studios - 2025

#include "PlayerStates/DSLobbyPlayerState.h"
#include "Actors/DSLobbyDummy.h"
#include "Net/UnrealNetwork.h"

// ====================================================================
// Unreal Lifecycle Methods
// ====================================================================
ADSLobbyPlayerState::ADSLobbyPlayerState() {
	this->bReplicates = true;
	this->PlayerIsReady = false;
}

void ADSLobbyPlayerState::BeginPlay() {
	Super::BeginPlay();
}

void ADSLobbyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Define every property  that needs to be replicated; -Dallai
	DOREPLIFETIME(ADSLobbyPlayerState, LobbyDummy)
	DOREPLIFETIME(ADSLobbyPlayerState, PlayerName);
}



// ====================================================================
// Player Lobby Dummy
// ====================================================================
void ADSLobbyPlayerState::SetLobbyDummy(ADSLobbyDummy* Dummy) {
	this->LobbyDummy = Dummy;
}



// ====================================================================
// Player Name
// ====================================================================
void ADSLobbyPlayerState::Server_ChangePlayerName_Implementation(const FText& newName) {
	this->PlayerName = newName;
	if (this->HasAuthority()) this->OnRep_ChangePlayerName();
}

void ADSLobbyPlayerState::OnRep_ChangePlayerName() const {
	if (this->LobbyDummy) {
		this->LobbyDummy->UpdatePlayerName(this->PlayerName);
	}
}



// ====================================================================
// Player Confirmation
// ====================================================================
void ADSLobbyPlayerState::Server_TogglePlayerReady_Implementation(const bool value) {
	this->PlayerIsReady = value;
	if (this->HasAuthority()) {
		this->OnRep_TogglePlayerReady();
	}
}

void ADSLobbyPlayerState::OnRep_TogglePlayerReady() const {
	if (this->LobbyDummy) {
		this->LobbyDummy->TogglePlayerConfirmation(this->PlayerIsReady);
	}
}
