// Made by Dallai Studios - 2025

#include "GameModes/DSCatchGameMode.h"

#include "PlayerStates/DSCatchPlayerState.h"
#include "Utils/DSMacros.h"

void ADSCatchGameMode::BeginPlay() {
	Super::BeginPlay();

	FTimerDelegate onFinishWaitingDelegate;
	onFinishWaitingDelegate.BindUFunction(this, FName("StartGame_EventListener"));
	this->GetWorld()->GetTimerManager().SetTimer(this->WaitPlayersTimeHandle, onFinishWaitingDelegate, this->TimeToWaitToStartGame, false);
}

void ADSCatchGameMode::PostLogin(APlayerController* NewPlayer) {
	Super::PostLogin(NewPlayer);

	const auto playerState = NewPlayer->GetPlayerState<ADSCatchPlayerState>();
	if (!playerState) {
		DS_LOG_ERROR("Catch Game mode Error: Player State is not defined or is not of type DSCatchPlayerState");
		return;
	}

	// TODO: disable player input
}

void ADSCatchGameMode::StartGame_EventListener() {
	// TODO loop all the players and enable the Movement, and select the cursed player;
}

