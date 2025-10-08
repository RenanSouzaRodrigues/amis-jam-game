// Made by Dallai Studios - 2025

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Enums/EEMSJoinSessionCompleteResult.h"
#include "Structs/FEMSOnlineSessionSearchResult.h"
#include "DSGameInstance.generated.h"

#define GAME_SESSION_NAME FString("CURSED_CATCH_MATCH")

class UDSGameUserSettings;

UCLASS()
class PROJECTCATCH_API UDSGameInstance : public UGameInstance 
{
	GENERATED_BODY()

	
	// ==================================================================
	// GAME INSTANCE PROPERTIES
	// ==================================================================
public:
	UPROPERTY(EditAnywhere, Category="Game Instance Properties")
	FString MainMenuLevelName { FString("Levels/Level_MainMenu") };

	UPROPERTY(EditAnywhere, Category="Game Instance Properties")
	FString LobbyLevelName { FString("Levels/Level_Lobby") };
	
	UPROPERTY(EditAnywhere, Category="Game Instance Properties")
	FString CatchGameLevelName { FString("Levels/Level_Catch") };
	
	
	// ==================================================================
	// MULTIPLAYER
	// ==================================================================
private:
	class UDSSessionSubsystem* GetSessionSubsystem() const;
	
public:
    void CreateSession();

private:
	UFUNCTION()
	void OnCreateSessionComplete(bool bWasSuccessful);

public:
	void FindSession();

private:
	UFUNCTION()
	void OnFindSession(const TArray<FEMSOnlineSessionSearchResult>& sessionResult, bool bSuccess);

	UFUNCTION()
	void OnJoinedSession(EEMSJoinSessionCompleteResult joinResult);

public:
	void StartCatchGame();
};
