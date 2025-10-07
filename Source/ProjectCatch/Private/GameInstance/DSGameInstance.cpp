// Fill out your copyright notice in the Description page of Project Settings.

#include "GameInstance/DSGameInstance.h"

#include "AdvancedSessionsLibrary.h"
#include "CreateSessionCallbackProxyAdvanced.h"
#include "FindSessionsCallbackProxyAdvanced.h"
#include "Kismet/GameplayStatics.h"
#include "Utils/DSMacros.h"
#include "OnlineSubsystem.h"
#include "Data/DSGameUserSettings.h"
#include "Interfaces/OnlineSessionInterface.h"

// ==================================================================
// LOBBY CREATION
// ==================================================================
void UDSGameInstance::CreateSession() const {
	APlayerController* playerController = this->GetFirstLocalPlayerController();

	if (!playerController) {
		DS_LOG_ERROR("Game Instance Error: Player Controller is invalid");
		return;
	}
	
	FSessionPropertyKeyPair mapPropertyKeyPair;
	mapPropertyKeyPair.Key = GAME_IDENTIFIER;
	mapPropertyKeyPair.Data.SetValue(this->LobbyLevelName.ToString());

	TArray<FSessionPropertyKeyPair> sessionExtraSettings;
	sessionExtraSettings.Add(mapPropertyKeyPair);
	
	const auto session = UCreateSessionCallbackProxyAdvanced::CreateAdvancedSession(this->GetWorld(), sessionExtraSettings, playerController);

	if (!session) {
		DS_LOG_ERROR("Game Instance Error: Fail to create session proxy");
		return;
	}
	
	session->OnSuccess.AddDynamic(this, &ThisClass::OnCreateSessionSuccess);
	session->OnFailure.AddDynamic(this, &ThisClass::OnCreateSessionFail);
}

void UDSGameInstance::OnCreateSessionSuccess() {
	UGameplayStatics::OpenLevel(this->GetWorld(), this->LobbyLevelName, true, "listen");
	DS_LOG_SUCCESS("Game Instance Success: Game Session is now Created");
}

void UDSGameInstance::OnCreateSessionFail() {
	DS_LOG_ERROR("Game Instance Error: Error trying to create a session and host a new game");
}


// ====================================================================
// FIND SESSIONS
// ====================================================================
void UDSGameInstance::FindSession() {
	APlayerController* playerController = GetFirstLocalPlayerController();
	
	if (!playerController) {
		DS_LOG_ERROR("Game Instance Error: player controller is invalid. cant find sessions");
		return;
	}

	TArray<FSessionsSearchSetting> filters;
	
	const auto findSessionResult = UFindSessionsCallbackProxyAdvanced::FindSessionsAdvanced(
		this->GetWorld(),
		playerController,
		10,
		false,
		EBPServerPresenceSearchType::ClientServersOnly,
		filters
	);

	if (!findSessionResult) {
		DS_LOG_ERROR("Game Instance Error: Fail to create find session proxy");
		return;
	}

	findSessionResult->OnSuccess.AddDynamic(this, &ThisClass::OnFindSessionSuccess);
	findSessionResult->OnFailure.AddDynamic(this, &ThisClass::OnFindSessionFail);
}

void UDSGameInstance::OnFindSessionSuccess(const TArray<FBlueprintSessionResult>& Results) {
	for (int32 index = 0; index < Results.Num(); ++index) {
		FString SessionName;
		Results[index].OnlineResult.Session.SessionSettings.Get(GAME_IDENTIFIER, SessionName);
		if (SessionName == this->LobbyLevelName.ToString()) {
			this->JoinSession(Results[index]);
			return;
		}
	}
}

void UDSGameInstance::OnFindSessionFail(const TArray<FBlueprintSessionResult>& Results) {
	UE_LOG(LogTemp, Error, TEXT("FindGames: No sessions found."));
}


// ====================================================================
// JOIN SESSION
// ====================================================================
void UDSGameInstance::JoinSession(const FBlueprintSessionResult& Session) {
	
}
