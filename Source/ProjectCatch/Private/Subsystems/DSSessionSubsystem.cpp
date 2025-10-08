// Made by Dallai Studios - 2025


#include "Subsystems/DSSessionSubsystem.h"

#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "Online/OnlineSessionNames.h"
#include "Utils/DSMacros.h"

// This session plugin is ready to be tested but, still need to do somethings.
// TODO: Create a way to Invite Steam Friends.
// TODO: Create a way to enter on a friend session.
// I dont know if this can be done automatically when the game has a proper Steam ID. -Renan

// ===================================================
// Unreal Methods
// ===================================================
UDSSessionSubsystem::UDSSessionSubsystem():
	// I'm using this approach because these especific delegates have their own way to be initialized and binded to events.
	// This way I can call the construction methods of all of then and start bind my subsystem events the way I need.
	// Makes the code a little harder to read but, there's nothing much I can do. -Renan
	OnCreateSessionEvent(FOnCreateSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnCreateSessionEventListenerCallback)),
	OnFindSessionEvent(FOnFindSessionsCompleteDelegate::CreateUObject(this, &ThisClass::OnFindSessionEventListenerCallback)),
	OnJoinSessionEvent(FOnJoinSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnJoinSessionEventListenerCallback)),
	OnStartSessionEvent(FOnStartSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnStartSessionEventListenerCallback)),
	OnDestroySessionEvent(FOnDestroySessionCompleteDelegate::CreateUObject(this, &ThisClass::OnDestroySessionEventListenerCallback))

// The constructor function starts here. -Renan
{
	IOnlineSubsystem* onlineSubsystemReference = IOnlineSubsystem::Get();

	this->SessionCreationSettingsOverride = nullptr;

	// Validates the online subsystem to make sure the project has it. It will be a little bit hard to make a online game without the
	// online subsystem. -Renan
	if (!onlineSubsystemReference) {
		DS_LOG_ERROR("Unable to get the Online Subsystem Reference from the engine source. Make sure the subsystem is available and try again");
		return;
	}

	// This is a debug message to help visualize what is the subsystem used for the online sessions.
	// Usually, playing in the editor, the subsystem will always be NULL. This is not a value but a subsystem name
	// When the developer has the steam installed, it will try to grab the steam subsystem and use it.
	// If the engine can grab the Steam subsystem, it will be used as the default. This debug log will show this on screen. -Renan
	const FString onlineSubsystemName = onlineSubsystemReference->GetSubsystemName().ToString();

	DS_LOG_INFO(FString::Printf(TEXT("Current online subsystem: %s"), *onlineSubsystemName));
	
	this->OnlineSubsystemSessionInterface = onlineSubsystemReference->GetSessionInterface();
}



// ===================================================
// Online Subsystem
// ===================================================
bool UDSSessionSubsystem::IsOnlineSubsystemInterfaceValid() const {
	if (!this->OnlineSubsystemSessionInterface.IsValid()) {
		DS_LOG_ERROR("Online subsystem session interface is invalid, something went wrong on the engine lifecycle");
		return false;
	}
	return true;
}



// ===================================================
// Create Session
// ===================================================
void UDSSessionSubsystem::OverrideSessionCreationSettings(UEMSSessionCreationSettingsPDA* settingsToOverride) {
	this->SessionCreationSettingsOverride = settingsToOverride;
}

void UDSSessionSubsystem::CreateSession(int32 numberOfPublicConnections, FString matchTypeName) {
	// Check if the online subsystem session interface I have is valid. If not, I'm simply returning void and
	// broadcasting the event with false value. -Renan
	if (!this->IsOnlineSubsystemInterfaceValid()) {
		this->OnSessionCreatedEvent.Broadcast(false);
		return;
	}
	
	// Clear the cached data when calling this function. -Renan
	this->CachedNumberOfPublicPlayers = 0;
	this->CachedMatchTypeName = FString("");
	
	// If there is a valid online game session already, it means that I need to destroy it to be able to create a new session.
	// This validation exists only to ensure that we have only one valid online game session. -Renan
	DS_LOG_INFO("Validating existing session");
	FNamedOnlineSession* existingSession = this->OnlineSubsystemSessionInterface->GetNamedSession(NAME_GameSession);
	if (existingSession != nullptr) {
		DS_LOG_WARN("There is a previous session created. Destroying previous session");
		this->bCreateSessionAfterDestroy = true;
		this->CachedNumberOfPublicPlayers = numberOfPublicConnections;
		this->CachedMatchTypeName = matchTypeName;
		this->DestroySession();
		return;
	}

	// I will store this into this delegate handle, so this way I can 'unbind' this later. -Renan
	this->CreateSessionDelegateHandle = this->OnlineSubsystemSessionInterface->AddOnCreateSessionCompleteDelegate_Handle(this->OnCreateSessionEvent);

	// This settings will define the session creation. I think is a good ideia to convert all this information later in a data asset that can override
	// these basic configurations. This way I can define at any moment how these settings are defined. -Renan
	this->OnlineSessionSettings = MakeShareable(new FOnlineSessionSettings());
	
	this->OnlineSessionSettings->bAllowJoinInProgress = true;
	this->OnlineSessionSettings->bAllowJoinViaPresence = true;
	this->OnlineSessionSettings->bAllowInvites = true;
	this->OnlineSessionSettings->bAllowJoinViaPresenceFriendsOnly = false;
	this->OnlineSessionSettings->bShouldAdvertise = true;
	this->OnlineSessionSettings->bUsesPresence = true;
	this->OnlineSessionSettings->bUseLobbiesIfAvailable = true;
	this->OnlineSessionSettings->BuildUniqueId = 1;

	this->OnlineSessionSettings->NumPublicConnections = numberOfPublicConnections;
	this->OnlineSessionSettings->bIsLANMatch = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL";
	this->OnlineSessionSettings->Set(FName("MatchType"), matchTypeName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	
	// With the ULocalPlayer reference I can grab the preferred unique net id. It is required to create a new online session.
	// without a local player controller, it is impossible to track who is the owner of the session. -Renan
	const ULocalPlayer* hostPlayer = this->GetWorld()->GetFirstLocalPlayerFromController();
	if (!hostPlayer) {
		DS_LOG_ERROR("No local player controller found. Aborting Session creation. A Local Player Controller is required in order to create a new Session");
	}

	// I also validate the local player net id. If this Id is invalid, steam is not started. Renan
	const FUniqueNetIdRepl& hostPlayerNetId = hostPlayer->GetPreferredUniqueNetId();
	if (!hostPlayerNetId.IsValid()) {
		DS_LOG_ERROR("Local Player UniqueNetId is invalid. Are you logged on Steam? Aborting session creation process.");
		this->OnSessionCreatedEvent.Broadcast(false);
		return;
	}

	// If the session is not created, then is probably a problem with the engine lifecycle.
	// I think this is a very impossible scenario, but we never know. Better safe then sorry. -Renan
	DS_LOG_INFO("Trying to create a new session");
	if (!this->OnlineSubsystemSessionInterface->CreateSession(*hostPlayerNetId, NAME_GameSession, *this->OnlineSessionSettings)) {
		DS_LOG_ERROR("Session was not created, aborting process and started cleaning delegates");
		this->OnlineSubsystemSessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(this->CreateSessionDelegateHandle);
		this->OnSessionCreatedEvent.Broadcast(false);
	}
}

void UDSSessionSubsystem::OnCreateSessionEventListenerCallback(FName createdSessionName, bool bWasSuccessfullCreated) {
	if (!this->IsOnlineSubsystemInterfaceValid()) {
		this->OnSessionCreatedEvent.Broadcast(false);
		return;
	}
	
	this->OnlineSubsystemSessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(this->CreateSessionDelegateHandle);

	this->OnSessionCreatedEvent.Broadcast(bWasSuccessfullCreated);
	DS_LOG_SUCCESS("Session created successfully");
}

void UDSSessionSubsystem::OpenGameLevelAsHostServer(FString pathToLobby) {
	if (!this->IsOnlineSubsystemInterfaceValid()) {
		DS_LOG_ERROR("Unable to open game level as host. Aborting process.");
		return;
	}

	FNamedOnlineSession* existingSession = this->OnlineSubsystemSessionInterface->GetNamedSession(NAME_GameSession);
	if (existingSession == nullptr) {
		DS_LOG_ERROR("Error: There is no created session. Unable to open game level as host. Aborting process");
		return;
	}
	
	UWorld* world = this->GetWorld();
	if (!world) {
		DS_LOG_ERROR("Unable to retrive world information to open lobby level. Aborting process");
		return;
	}

	const FString finalPathName = FString::Printf(TEXT("/Game/%s?listen"), *pathToLobby);
	world->ServerTravel(finalPathName);
}



// ===================================================
// Find Session
// ===================================================
void UDSSessionSubsystem::FindSession(int32 maxOnlineSessionsSearchResult, float timeoutInSeconds) {
	// Online subsystem session interface validation. It is good to aways be sure. -Renan
	if (!this->IsOnlineSubsystemInterfaceValid()) {
		TArray<FEMSOnlineSessionSearchResult> emptySearchResult = TArray<FEMSOnlineSessionSearchResult>();
		this->OnSessionFoundEvent.Broadcast(emptySearchResult, false);
		return;
	}

	// Same as the create session method. -Renan
	this->FindSessionDelegateHandle = this->OnlineSubsystemSessionInterface->AddOnFindSessionsCompleteDelegate_Handle(this->OnFindSessionEvent);

	this->OnlineSessionSearch = MakeShareable(new FOnlineSessionSearch);
	this->OnlineSessionSearch->bIsLanQuery = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL";
	this->OnlineSessionSearch->MaxSearchResults = maxOnlineSessionsSearchResult;
	this->OnlineSessionSearch->TimeoutInSeconds = timeoutInSeconds;
	// TODO: Study the documentation and make more tests to see what else I can pass here
	this->OnlineSessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
	
	const ULocalPlayer* localPlayer = this->GetWorld()->GetFirstLocalPlayerFromController();

	// Same for the creation method. I need the local player controller here to be able to join sessions on the future. -Renan
	if (!localPlayer) {
		DS_LOG_ERROR("No local player controller found. Aborting Find Session Process. A Local Player Controller is required in order search for sessions");
		this->OnlineSubsystemSessionInterface->ClearOnFindSessionsCompleteDelegate_Handle(this->FindSessionDelegateHandle);
		TArray<FEMSOnlineSessionSearchResult> emptySearchResult = TArray<FEMSOnlineSessionSearchResult>();
		this->OnSessionFoundEvent.Broadcast(emptySearchResult, false);
		return;
	}
	
	const FUniqueNetIdRepl& localPlayerNetId = localPlayer->GetPreferredUniqueNetId();
	if (!localPlayerNetId.IsValid()) {
		DS_LOG_ERROR("Local Player UniqueNetId is invalid. Are you logged on Steam? Aborting session finding process.");
		TArray<FEMSOnlineSessionSearchResult> emptySearchResult = TArray<FEMSOnlineSessionSearchResult>();
		this->OnSessionFoundEvent.Broadcast(emptySearchResult, false);
		return;
	}
	
	// If there is any error when the subsystem tries to retrieve the list of sessions to join, I simple send a log and broadcast a false response. -Renan
	if (!this->OnlineSubsystemSessionInterface->FindSessions(*localPlayerNetId, this->OnlineSessionSearch.ToSharedRef())) {
		DS_LOG_ERROR("Unable to find sessions. Aborting Process.");
		this->OnlineSubsystemSessionInterface->ClearOnFindSessionsCompleteDelegate_Handle(this->FindSessionDelegateHandle);
		TArray<FEMSOnlineSessionSearchResult> emptySearchResult = TArray<FEMSOnlineSessionSearchResult>();
		this->OnSessionFoundEvent.Broadcast(emptySearchResult, false);
	}
}

void UDSSessionSubsystem::OnFindSessionEventListenerCallback(bool bWasSuccessfull) {
	if (!this->IsOnlineSubsystemInterfaceValid()) {
		TArray<FEMSOnlineSessionSearchResult> emptySearchResult = TArray<FEMSOnlineSessionSearchResult>();
		this->OnSessionFoundEvent.Broadcast(emptySearchResult, false);
		return;
	}

	this->OnlineSubsystemSessionInterface->ClearOnFindSessionsCompleteDelegate_Handle(this->FindSessionDelegateHandle);
	
	// In case there is no session results but the process still returns a success, broadcast the event with no success because there is no list
	// of sessions to join. I don't know if broadcasting a false value is a good choice. But at this point, I think is enough. -Renan
	if (this->OnlineSessionSearch->SearchResults.Num() == 0) {
		TArray<FEMSOnlineSessionSearchResult> emptySearchResult = TArray<FEMSOnlineSessionSearchResult>();
		this->OnSessionFoundEvent.Broadcast(emptySearchResult, false);
	}

	for (auto session : this->OnlineSessionSearch->SearchResults) {
		UEMSUtils::ShowDebugMessage(FString::Printf(TEXT("Found Session: %s Line 334"), *session.GetSessionIdStr()), FColor::Blue);
	}

	// This is a conversion to enable the plugins users to see this result using blueprint API.
	// When this translation is done, this is what the delegate sends to the blueprint reflections system;
	// BUG: There is probably a bug here. I dont know if all the values are been translated correctly.
	TArray<FEMSOnlineSessionSearchResult> results;
	for (auto searchResult : this->OnlineSessionSearch->SearchResults) {
		results.Add(this->ConvertSessionResult(searchResult));
	}
	
	this->OnSessionFoundEvent.Broadcast(results, bWasSuccessfull);
	UEMSUtils::ShowDebugMessage(TEXT("Find Session Results returned successfully!"), FColor::Green);
}

bool UDSSessionSubsystem::FilterSessionResultsByMatchType(const TArray<FEMSOnlineSessionSearchResult>& Results, const FString& MatchTypeName, FEMSOnlineSessionSearchResult& OutResult) {
	for (const auto& Result : Results) {
		if (Result.MatchType == MatchTypeName) {
			OutResult = Result;
			return true;
		}
	}
	return false;
}

// This function exists to translate the session result into something that can use the blueprint reflection system.
// With this, I can aways look on the array of all the results and filter it and join the correct session result data. -Renan
FEMSOnlineSessionSearchResult UDSSessionSubsystem::ConvertSessionResult(FOnlineSessionSearchResult sessionResult) {
	// The result data is just converted to a FStruct that can be exposed to blueprints API. -Renan
	FString matchTypeName;
	sessionResult.Session.SessionSettings.Get(FName("MatchType"), matchTypeName);

	FEMSOnlineSessionSearchResult result;
	result.MatchType = matchTypeName;
	result.SessionId = sessionResult.GetSessionIdStr();
	result.PingInMs = sessionResult.PingInMs;
	result.NumberOfPublicConnections = sessionResult.Session.NumOpenPublicConnections;
	result.NumberOfPrivateConnections = sessionResult.Session.NumOpenPrivateConnections;
	result.OriginalSearchResult = sessionResult;
	
	return result;
}



// ===================================================
// Join Session
// ===================================================
void UDSSessionSubsystem::JoinSession(const FEMSOnlineSessionSearchResult& onlineSessionSearchResult) {
	// I first validate the session search result because, if this is null or invalid there is no reason to try join this session. -Renan
	if (!onlineSessionSearchResult.IsValid()) {
		UEMSUtils::ShowDebugMessage(TEXT("Unable to Join Session, the search result provided is invalid"));
		this->OnSessionJoinedEvent.Broadcast(this->ConvertJoinResult(EOnJoinSessionCompleteResult::UnknownError));
		return;
	}

	// Simple Validation. -Renan
	if (!this->IsOnlineSubsystemInterfaceValid()) {
		// I think I can use this EOnJoinSessionCompleteResult::UnknownError for any generic error. Just like this one. -Renan
		this->OnSessionJoinedEvent.Broadcast(this->ConvertJoinResult(EOnJoinSessionCompleteResult::UnknownError));
		return;
	};

	// TODO: Validate if the session is full;
	// TODO: Validate if the session is private;
	// TODO: Validate if the session has password;
	
	this->JoinSessionDelegateHandle = this->OnlineSubsystemSessionInterface->AddOnJoinSessionCompleteDelegate_Handle(this->OnJoinSessionEvent);

	const ULocalPlayer* localPlayer = this->GetWorld()->GetFirstLocalPlayerFromController();
	if (!localPlayer) {
		UEMSUtils::ShowDebugMessage(TEXT("No local player controller found. Aborting Join Session Process. A Local Player Controller is required in order to join a session"), FColor::Red);
		this->OnlineSubsystemSessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(this->JoinSessionDelegateHandle);
		this->OnSessionJoinedEvent.Broadcast(this->ConvertJoinResult(EOnJoinSessionCompleteResult::UnknownError));
		return;
	}

	const FUniqueNetIdRepl& localPlayerNetId = localPlayer->GetPreferredUniqueNetId();
	if (!localPlayerNetId.IsValid()) {
		UEMSUtils::ShowDebugMessage(TEXT("Local Player UniqueNetId is invalid. Are you logged on Steam? Aborting session joining process."), FColor::Red);
		this->OnSessionJoinedEvent.Broadcast(this->ConvertJoinResult(EOnJoinSessionCompleteResult::UnknownError));
		return;
	}
	
	if (!this->OnlineSubsystemSessionInterface->JoinSession(*localPlayerNetId, NAME_GameSession, onlineSessionSearchResult.OriginalSearchResult)) {
		UEMSUtils::ShowDebugMessage(TEXT("Unable to join session for some error. Aborting process: Line 211"), FColor::Red);
		this->OnlineSubsystemSessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(this->JoinSessionDelegateHandle);
		this->OnSessionJoinedEvent.Broadcast(this->ConvertJoinResult(EOnJoinSessionCompleteResult::UnknownError));
		return;
	}
}

void UDSSessionSubsystem::OnJoinSessionEventListenerCallback(FName joinedSessionName, EOnJoinSessionCompleteResult::Type joinResultType) {
	if (!this->IsOnlineSubsystemInterfaceValid()) {
		this->OnSessionJoinedEvent.Broadcast(this->ConvertJoinResult(joinResultType));
		return;
	};
	
	this->OnlineSubsystemSessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(this->JoinSessionDelegateHandle);
	
	this->OnSessionJoinedEvent.Broadcast(this->ConvertJoinResult(joinResultType));
	if (joinResultType == EOnJoinSessionCompleteResult::Success) DS_LOG_SUCCESS("Session Joined Successfully!");
}

// Same thing here. I can use this function to make use of the blueprint reflection system. -Renan
EEMSJoinSessionCompleteResult UDSSessionSubsystem::ConvertJoinResult(const EOnJoinSessionCompleteResult::Type joinResultType) {
	// In this case is just a simple Enum translation. -Renan
	switch (joinResultType) {
	case EOnJoinSessionCompleteResult::Success: return EEMSJoinSessionCompleteResult::Success;
	case EOnJoinSessionCompleteResult::UnknownError: return EEMSJoinSessionCompleteResult::UnknownError;
	case EOnJoinSessionCompleteResult::AlreadyInSession: return EEMSJoinSessionCompleteResult::AlreadyInSession;
	case EOnJoinSessionCompleteResult::SessionIsFull: return EEMSJoinSessionCompleteResult::SessionIsFull;
	case EOnJoinSessionCompleteResult::CouldNotRetrieveAddress: return EEMSJoinSessionCompleteResult::CouldNotRetrieveAddress;
	case EOnJoinSessionCompleteResult::SessionDoesNotExist: return EEMSJoinSessionCompleteResult::SessionDoesNotExist;
	default: return EEMSJoinSessionCompleteResult::UnknownError;
	}
}

void UDSSessionSubsystem::ConnectToJoinedSession() {
	if (!this->IsOnlineSubsystemInterfaceValid()) {
		DS_LOG_ERROR("Unable to connect to session. Aborting process.");
		return;
	}

	// The online subsystem holds the reference to the joined session. This way I can grab the connection string address
	// at any point in time. -Renan
	FString connectionAddress;
	this->OnlineSubsystemSessionInterface->GetResolvedConnectString(NAME_GameSession, connectionAddress);

	// I validate the connection string so the user can't even try to connect to the empty address. -Renan
	if (connectionAddress.IsEmpty()) {
		DS_LOG_ERROR("Unable to connect to joined session. Could not retrieve the session connection string address.");
		return;
	}
	
	if (APlayerController* playerController = this->GetGameInstance()->GetFirstLocalPlayerController()) {
		playerController->ClientTravel(connectionAddress, ETravelType::TRAVEL_Absolute);
	}
}



// ===================================================
// Start Session
// ===================================================
void UDSSessionSubsystem::StartSession() {
	// simple validation. -Renan
	if (!this->IsOnlineSubsystemInterfaceValid()) {
		this->OnSessionStartedEvent.Broadcast(false);
		return;
	}

	// Delegate handle binding. -Renan
	this->StartSessionDelegateHandle = this->OnlineSubsystemSessionInterface->AddOnStartSessionCompleteDelegate_Handle(this->OnStartSessionEvent);

	if (!this->OnlineSubsystemSessionInterface->StartSession(NAME_GameSession)) {
		DS_LOG_ERROR("Unable to start the session, aborting process and cleaning delegates");
		this->OnlineSubsystemSessionInterface->ClearOnStartSessionCompleteDelegate_Handle(this->StartSessionDelegateHandle);
		this->OnSessionStartedEvent.Broadcast(false);
	}
}

void UDSSessionSubsystem::OnStartSessionEventListenerCallback(FName sessionName, bool bWasSuccessful) {
	if (!this->IsOnlineSubsystemInterfaceValid()) {
		this->OnSessionStartedEvent.Broadcast(false);
		return;
	}
	
	this->OnlineSubsystemSessionInterface->ClearOnStartSessionCompleteDelegate_Handle(this->StartSessionDelegateHandle);

	this->OnSessionStartedEvent.Broadcast(bWasSuccessful);
	if (bWasSuccessful) DS_LOG_SUCCESS("Session Started successfully!");
}



// ===================================================
// Destroy Session
// ===================================================
void UDSSessionSubsystem::DestroySession() {
	// Simple validation. -Renan
	if (!this->IsOnlineSubsystemInterfaceValid()) {
		this->OnSessionDestroyedEvent.Broadcast(false);
		return;
	}

	// delegate handle binding. -Renan
	this->DestroySessionDelegateHandle = this->OnlineSubsystemSessionInterface->AddOnDestroySessionCompleteDelegate_Handle(this->OnDestroySessionEvent);
	
	if (!this->OnlineSubsystemSessionInterface->DestroySession(NAME_GameSession)) {
		DS_LOG_ERROR("Unable to destroy session, aborting process and cleaning delegates");
		this->OnlineSubsystemSessionInterface->ClearOnDestroySessionCompleteDelegate_Handle(this->DestroySessionDelegateHandle);
		this->OnSessionDestroyedEvent.Broadcast(false);
	}
}

void UDSSessionSubsystem::OnDestroySessionEventListenerCallback(FName sessionName, bool bWasSuccessful) {
	if (!this->IsOnlineSubsystemInterfaceValid()) {
		this->OnSessionDestroyedEvent.Broadcast(false);
		return;
	}
	
	this->OnlineSubsystemSessionInterface->ClearOnDestroySessionCompleteDelegate_Handle(this->DestroySessionDelegateHandle);

	this->OnSessionDestroyedEvent.Broadcast(bWasSuccessful);

	if (this->bCreateSessionAfterDestroy && bWasSuccessful) {
		this->bCreateSessionAfterDestroy = false;
		DS_LOG_INFO("Previous Session destroyed. Ready to create a new session.");
		this->CreateSession(this->CachedNumberOfPublicPlayers, this->CachedMatchTypeName);
		return;
	}
	
	if (bWasSuccessful) DS_LOG_SUCCESS("Session Destroyed Successfully!");
}