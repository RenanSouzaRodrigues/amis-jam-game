// Made by Dallai Studios - 2025

#pragma once

#include "CoreMinimal.h"
#include "AdvancedFriendsGameInstance.h"
#include "Engine/GameInstance.h"
#include "DSGameInstance.generated.h"

#define GAME_IDENTIFIER FName("PROJECT_CATCH_LEVEL_NAME")

class UDSGameUserSettings;

UCLASS()
class PROJECTCATCH_API UDSGameInstance : public UAdvancedFriendsGameInstance 
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Game Instance Properties")
	FName MainMenuLevelName { FName("Level_MainMenu") };

	UPROPERTY(EditAnywhere, Category="Game Instance Properties")
	FName LobbyLevelName { FName("Level_Lobby") };
	
	UPROPERTY(EditAnywhere, Category="Game Instance Properties")
	FName CatchGameLevelName { FName("Level_CatchGame") };


	// ==================================================================
	// HOST GAME
	// ==================================================================
public:
	UFUNCTION()
    void CreateSession() const;

	UFUNCTION()
	void OnCreateSessionSuccess();

	UFUNCTION()
	void OnCreateSessionFail();
	

	// ==================================================================
	// FIND SESSION
	// ==================================================================
	UFUNCTION()
	void FindSession();

	UFUNCTION()
	void OnFindSessionSuccess(const TArray<FBlueprintSessionResult>& Results);

	UFUNCTION()
	void OnFindSessionFail(const TArray<FBlueprintSessionResult>& Results);
	
	
	// ==================================================================
	// JOIN SESSION
	// ==================================================================
	UFUNCTION()
	void JoinSession(const FBlueprintSessionResult& Session);

	UFUNCTION()
	void OnJoinSessionSuccess();

	UFUNCTION()
	void OnJoinSessionFail();
};
