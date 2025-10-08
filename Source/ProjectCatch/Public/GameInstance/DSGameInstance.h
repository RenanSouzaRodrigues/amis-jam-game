// Made by Dallai Studios - 2025

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
#include "DSGameInstance.generated.h"

#define GAME_SESSION_NAME TEXT("CURSEDCATCH_GAME_SESSION")

class UDSGameUserSettings;

UCLASS()
class PROJECTCATCH_API UDSGameInstance : public UGameInstance 
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Game Instance Properties")
	FName MainMenuLevelName { FName("Level_MainMenu") };

	UPROPERTY(EditAnywhere, Category="Game Instance Properties")
	FString LobbyLevelName { "Game/Levels/Level_Lobby" };
	
	UPROPERTY(EditAnywhere, Category="Game Instance Properties")
	FName CatchGameLevelName { FName("Level_CatchGame") };


private:
	IOnlineSessionPtr OnlineSessionInterfacePointer;
	TSharedPtr<FOnlineSessionSearch> SessionSearch;

	FORCEINLINE bool IsOnlineSessionInterfaceValid() const { return this->OnlineSessionInterfacePointer.IsValid(); }

	
	// ==================================================================
	// UNREAL LIFECYCLE
	// ==================================================================	
public:
	virtual void Init() override;
	
	// ==================================================================
	// HOST GAME
	// ==================================================================
public:
    void CreateSession() const;

	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	
	
	// ==================================================================
	// FIND SESSION
	// ==================================================================
	void FindSession();

	void OnFindSessionsComplete(bool bWasSuccessful);
	
	
	// ==================================================================
	// JOIN SESSION
	// ==================================================================
	void JoinFoundSession(const FOnlineSessionSearchResult& Session) const;

	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
};
