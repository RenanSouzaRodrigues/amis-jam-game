// Made by Dallai Studios - 2025

#include "PlayerStates/DSLobbyPlayerState.h"
#include "Actors/DSLobbyDummy.h"
#include "Net/UnrealNetwork.h"
#include "Utils/DSMacros.h"

// ====================================================================
// Unreal Lifecycle Methods
// ====================================================================
ADSLobbyPlayerState::ADSLobbyPlayerState() {
	this->bReplicates = true;
}

void ADSLobbyPlayerState::BeginPlay() {
	Super::BeginPlay();
	if (this->LobbyDummy) {
		this->Server_ChangePlayerName(FText::FromString("Player Name"));
	}
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
}

void ADSLobbyPlayerState::OnRep_ChangePlayerName() const {
	if (this->GetPlayerController()->IsLocalController()) {
		DS_LOG_SUCCESS("Player name changed");
		if (this->LobbyDummy) {
			this->LobbyDummy->UpdatePlayerName(this->PlayerName);
		}
	}
}