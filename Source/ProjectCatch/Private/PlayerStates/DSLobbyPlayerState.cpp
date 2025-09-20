// Made by Dallai Studios - 2025

#include "PlayerStates/DSLobbyPlayerState.h"
#include "Net/UnrealNetwork.h"

void ADSLobbyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADSLobbyPlayerState, LobbyDummy)
}

void ADSLobbyPlayerState::SetLobbyDummy(ADSLobbyDummy* Dummy) {
	this->LobbyDummy = Dummy;
}