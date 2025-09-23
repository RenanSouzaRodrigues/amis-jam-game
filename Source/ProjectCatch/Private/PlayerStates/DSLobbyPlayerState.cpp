// Made by Dallai Studios - 2025

#include "PlayerStates/DSLobbyPlayerState.h"
#include "Actors/DSLobbyDummy.h"
#include "Net/UnrealNetwork.h"

ADSLobbyPlayerState::ADSLobbyPlayerState() {
	this->bReplicates = true;
	this->PlayerIsReady = false;
	this->LobbyDummy = nullptr;
}

void ADSLobbyPlayerState::BeginPlay() {
	Super::BeginPlay();
}

void ADSLobbyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Define every property that needs to be replicated; -Dallai
	DOREPLIFETIME(ADSLobbyPlayerState, LobbyDummy)
	DOREPLIFETIME(ADSLobbyPlayerState, PlayerName)
	DOREPLIFETIME(ADSLobbyPlayerState, PlayerIsReady)
}

// Player Dummy
void ADSLobbyPlayerState::SetLobbyDummy(ADSLobbyDummy* Dummy) {
	this->LobbyDummy = Dummy;

	if (this->HasAuthority()) {
		// No servidor, podemos alterar as propriedades diretamente
		this->PlayerName = FText::FromString("Host");
		this->PlayerIsReady = true;
        
		// Não esqueça de chamar os OnRep manualmente no servidor
		OnRep_ChangePlayerName();
		OnRep_PlayerIsReady();
	} else {
		// No cliente, fazemos as chamadas RPC
		this->Server_ChangePlayerName(FText::FromString("Client"));
		this->Server_UncheckPlayerReady();
	}
}


// Player Name
void ADSLobbyPlayerState::Server_ChangePlayerName_Implementation(const FText& newName) {
	this->PlayerName = newName;
	if (this->HasAuthority()) this->OnRep_ChangePlayerName();
}

void ADSLobbyPlayerState::OnRep_ChangePlayerName() const {
	if (this->LobbyDummy) {
		this->LobbyDummy->UpdatePlayerName(this->PlayerName);
	}
}


// Player Confirmation
void ADSLobbyPlayerState::Server_CheckPlayerReady_Implementation() {
	this->PlayerIsReady = true;
	if (this->HasAuthority()) this->OnRep_PlayerIsReady();
}

void ADSLobbyPlayerState::Server_UncheckPlayerReady_Implementation() {
	this->PlayerIsReady = false;
	if (this->HasAuthority()) this->OnRep_PlayerIsReady();
}

void ADSLobbyPlayerState::OnRep_PlayerIsReady() const {
	if (this->LobbyDummy) {
		if (this->PlayerIsReady) this->LobbyDummy->SetIsReady(); else this->LobbyDummy->SetIsNotReady();
	}
}