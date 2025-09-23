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

	DS_LOG_INFO(FString::Printf(TEXT("Game Mode Log: New player connected. Player name: %s"), *NewPlayer->GetName()));
	
	if (!this->PlayerDummyClass) {
		DS_LOG_ERROR("Game Mode Error: Player Dummy Class is not defined, make sure it is defined as a game mode dependency");
		return;
	}
	
	TArray<AActor*> playerStarts;
	UGameplayStatics::GetAllActorsOfClass(this->GetWorld(), APlayerStart::StaticClass(), playerStarts);

	if (playerStarts.Num() == 0) {
		DS_LOG_ERROR("Game Mode Error: There is no Player Start Actor on the level. Make sure to add at least 2 Player Start Actor on the level.");
		return;
	}
	
	if (playerStarts.Num() > 0) {
		const int32 index = this->GameState->PlayerArray.Num() - 1;

		const FVector spawnLocation = playerStarts[index]->GetActorLocation();
		const FRotator spawnRotation = playerStarts[index]->GetActorRotation();
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = NewPlayer;
		spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		ADSLobbyDummy* dummy = this->GetWorld()->SpawnActor<ADSLobbyDummy>(this->PlayerDummyClass, spawnLocation, spawnRotation, spawnParams);

		if (!dummy) {
			DS_LOG_ERROR("Game Mode Error: Could not spawn player dummy for the logged controller. Unknown error");
			return;
		}
		
		ADSLobbyPlayerState* playerState = NewPlayer->GetPlayerState<ADSLobbyPlayerState>();
		
		if (!playerState) {
			DS_LOG_ERROR("Game Mode Error: Player state is invalid or is not of type ADSLobbyPlayerState. Make sure to provide the correct Player State Class");
			dummy->Destroy();
			return;
		}

		playerState->SetLobbyDummy(dummy);
	}
}
