// Made by Dallai Studios - 2025

#include "GameInstance/DSGameInstance.h"
#include "Subsystems/DSSessionSubsystem.h"
#include "Utils/DSMacros.h"

UDSSessionSubsystem* UDSGameInstance::GetSessionSubsystem() const {
	UDSSessionSubsystem* subsystem = this->GetSubsystem<UDSSessionSubsystem>();
	if (!subsystem) {
		DS_LOG_ERROR("Game Instance Error: Session Subsystem is invalid");
		return nullptr;
	}
	return subsystem;
}

// ==================================================================
// MULTIPLAYER
// ==================================================================
void UDSGameInstance::CreateSession() {
	if (UDSSessionSubsystem* subsystem = this->GetSessionSubsystem()) {
		subsystem->OnSessionCreatedEvent.AddDynamic(this, &UDSGameInstance::OnCreateSessionComplete);
		subsystem->CreateSession(6, GAME_SESSION_NAME);
	}	
}

void UDSGameInstance::OnCreateSessionComplete(const bool bWasSuccessful) {
	if (!bWasSuccessful) {
		DS_LOG_ERROR("Game Instance Error: Session Creation Error");
		return;
	}

	if (UDSSessionSubsystem* subsytem = this->GetSessionSubsystem()) {
		subsytem->OpenGameLevelAsHostServer(this->LobbyLevelName);
	}
}

void UDSGameInstance::FindSession() {
	if (UDSSessionSubsystem* subsystem = this->GetSessionSubsystem()) {
		subsystem->OnSessionFoundEvent.AddDynamic(this, &UDSGameInstance::OnFindSession);
		subsystem->FindSession(10, 120);
	}
	
}

void UDSGameInstance::OnFindSession(const TArray<FEMSOnlineSessionSearchResult>& sessionResult, bool bSuccess) {
	if (!bSuccess) {
		DS_LOG_ERROR("No Session found");
		return;
	}

	if (UDSSessionSubsystem* subsystem = this->GetSessionSubsystem()) {
		for (auto session : sessionResult) {
			if (session.MatchType == GAME_SESSION_NAME) {
				subsystem->OnSessionJoinedEvent.AddDynamic(this, &UDSGameInstance::OnJoinedSession);
				subsystem->JoinSession(session);
			}
		}	
	}
}

void UDSGameInstance::OnJoinedSession(EEMSJoinSessionCompleteResult joinResult) {
	switch (joinResult) {
		case (EEMSJoinSessionCompleteResult::UnknownError): DS_LOG_ERROR("Error trying to join session: Unknow reason"); return;
		case (EEMSJoinSessionCompleteResult::AlreadyInSession): DS_LOG_INFO("Already in session"); return;
		case (EEMSJoinSessionCompleteResult::CouldNotRetrieveAddress): DS_LOG_ERROR("Error trying to join session: Could not retrieve address"); return;
		case (EEMSJoinSessionCompleteResult::SessionDoesNotExist): DS_LOG_ERROR("Error trying to join session: Session does not exists"); return;
		case (EEMSJoinSessionCompleteResult::SessionIsFull): DS_LOG_ERROR("Error trying to join session: Session is full"); return;
		case (EEMSJoinSessionCompleteResult::Success): {
			if (UDSSessionSubsystem* subsystem = this->GetSessionSubsystem()) {
				subsystem->ConnectToJoinedSession();
				return;
			}
		}
		default: DS_LOG_ERROR("Error trying to join session: undefined");
	}
}

void UDSGameInstance::StartCatchGame() {
	if (UDSSessionSubsystem* subsystem = this->GetSessionSubsystem()) {
		subsystem->StartSession();
		subsystem->OpenGameLevelAsHostServer(this->CatchGameLevelName);
	}
}
