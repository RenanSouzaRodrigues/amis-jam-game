// Made by Dallai Studios - 2025

#include "GameModes/DSLobbyGameMode.h"
#include "Actors/DSLobbyDummy.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerStates/DSLobbyPlayerState.h"
#include "Utils/DSMacros.h"

void ADSLobbyGameMode::PostLogin(APlayerController* NewPlayer) {
	Super::PostLogin(NewPlayer);

	DS_LOG_INFO("Player Connected");
	
	if (!this->PlayerDummyClass) {
		DS_LOG_ERROR("Lobby Game Mode Error: Player Dummy Class is not defined");
		return;
	}
	
	TArray<AActor*> playerStarts;
	UGameplayStatics::GetAllActorsOfClass(this->GetWorld(), APlayerStart::StaticClass(), playerStarts);

	if (playerStarts.Num() > 0) {
		int32 index = this->GameState->PlayerArray.Num() - 1;
		if (index < 0) index = 0;

		const FVector spawnLocation = playerStarts[index]->GetActorLocation();
		const FRotator spawnRotation = playerStarts[index]->GetActorRotation();

		FActorSpawnParameters spawnParams;
		spawnParams.Owner = NewPlayer;

		if (ADSLobbyDummy* dummy = this->GetWorld()->SpawnActor<ADSLobbyDummy>(this->PlayerDummyClass, spawnLocation, spawnRotation, spawnParams)) {
			if (const auto playerState = NewPlayer->GetPlayerState<ADSLobbyPlayerState>()) {
				playerState->SetLobbyDummy(dummy);
			}	
		}
	}
}
