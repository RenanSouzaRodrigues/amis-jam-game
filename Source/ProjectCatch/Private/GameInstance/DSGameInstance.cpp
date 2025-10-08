// Made by Dallai Studios - 2025

#include "GameInstance/DSGameInstance.h"

#include "Online/OnlineSessionNames.h"
#include "Utils/DSMacros.h"

void UDSGameInstance::Init() {
	Super::Init();

	IOnlineSubsystem* subsystem = IOnlineSubsystem::Get();

	if (!subsystem) {
		DS_LOG_ERROR("Game Instance Error: Online subsystem is invalid");
		return;
	}

	this->OnlineSessionInterfacePointer = subsystem->GetSessionInterface();

	if (!this->OnlineSessionInterfacePointer.IsValid()) {
		DS_LOG_ERROR("Game Instance Error: Online subsystem interface is invalid");
		return;
	}

	this->OnlineSessionInterfacePointer->OnCreateSessionCompleteDelegates.AddUObject(this, &UDSGameInstance::OnCreateSessionComplete);
	this->OnlineSessionInterfacePointer->OnFindSessionsCompleteDelegates.AddUObject(this, &UDSGameInstance::OnFindSessionsComplete);
	this->OnlineSessionInterfacePointer->OnJoinSessionCompleteDelegates.AddUObject(this, &UDSGameInstance::OnJoinSessionComplete);
}

// ==================================================================
// LOBBY CREATION
// ==================================================================
void UDSGameInstance::CreateSession() const {
	if (!this->OnlineSessionInterfacePointer.IsValid()) {
		DS_LOG_ERROR("Game Instance Error: Online subsystem interface is invalid");
		return;
	}

	FOnlineSessionSettings sessionSettings;
	sessionSettings.bIsLANMatch = false;
	sessionSettings.NumPublicConnections = 6;
	sessionSettings.bShouldAdvertise = true;
	sessionSettings.bUsesPresence = true;
	sessionSettings.bAllowJoinInProgress = true;
	sessionSettings.bAllowJoinViaPresence = true;
	sessionSettings.bAllowJoinViaPresenceFriendsOnly = false;
	
	this->OnlineSessionInterfacePointer->CreateSession(0, GAME_SESSION_NAME, sessionSettings);
}

void UDSGameInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful) {
	if (!bWasSuccessful) {
		DS_LOG_ERROR("Game Instance Error: Session Creation Error");
		return;
	}
	
	DS_LOG_SUCCESS(FString::Printf(TEXT("Game Instance Success: New game session created with name %s"), *SessionName.ToString()));
	this->GetWorld()->ServerTravel(this->LobbyLevelName + "?listen");
}


// ====================================================================
// FIND SESSIONS
// ====================================================================
void UDSGameInstance::FindSession() {
	if (!this->OnlineSessionInterfacePointer.IsValid()) return;

	this->SessionSearch = MakeShareable(new FOnlineSessionSearch());
	this->SessionSearch->bIsLanQuery = false;
	this->SessionSearch->MaxSearchResults = 20;
	this->SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);

	this->OnlineSessionInterfacePointer->FindSessions(0, this->SessionSearch.ToSharedRef());
}

void UDSGameInstance::OnFindSessionsComplete(bool bWasSuccessful) {
	if (!bWasSuccessful || !SessionSearch.IsValid()) return;

	for (const FOnlineSessionSearchResult& Result : SessionSearch->SearchResults)
	{
		UE_LOG(LogTemp, Warning, TEXT("Sessão encontrada: %s"), *Result.GetSessionIdStr());
		this->JoinFoundSession(Result);
		return; // entra na primeira encontrada
	}

	UE_LOG(LogTemp, Warning, TEXT("Nenhuma sessão encontrada"));
}


// ====================================================================
// JOIN SESSION
// ====================================================================
void UDSGameInstance::JoinFoundSession(const FOnlineSessionSearchResult& Result) const {
	if (!this->OnlineSessionInterfacePointer.IsValid()) return;
	this->OnlineSessionInterfacePointer->JoinSession(0, GAME_SESSION_NAME, Result);
}

void UDSGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result) {
	if (!this->OnlineSessionInterfacePointer.IsValid()) return;
	FString connectionString;
	if (this->OnlineSessionInterfacePointer->GetResolvedConnectString(SessionName, connectionString)) {
		if (const auto playerController = this->GetFirstLocalPlayerController()) {
			playerController->ClientTravel(connectionString, TRAVEL_Absolute);
		}	
	}
}
