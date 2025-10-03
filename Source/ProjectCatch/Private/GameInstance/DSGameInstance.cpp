// Fill out your copyright notice in the Description page of Project Settings.

#include "GameInstance/DSGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Utils/DSMacros.h"
#include "OnlineSubsystem.h"
#include "Data/DSGameUserSettings.h"
#include "Interfaces/OnlineSessionInterface.h"

void UDSGameInstance::Init() {
	Super::Init();

	if (!this->GameSoundMixer || !this->MasterSoundClass || !this->MusicSoundClass || !this->SfxSoundClass) {
		DS_LOG_ERROR("Game Instance Error: Sound Config is not defined");
		return;
	}
	
	this->UserSettings = Cast<UDSGameUserSettings>(GEngine->GetGameUserSettings());
	if (!this->UserSettings) {
		DS_LOG_ERROR("Game Instance Error: Game User Settings is not defined or is not of type UDSGameUserSettings");
		return;
	}

	this->UserSettings->LoadSettings();
}

void UDSGameInstance::HostGame() const {
	DS_LOG_INFO("Hosting Game");

	UGameplayStatics::OpenLevel(this->GetWorld(), this->LobbyLevelName, true, "listen");
}

void UDSGameInstance::JoinGame(const FString& ServerAddress) const {
	DS_LOG_INFO(FString::Printf(TEXT("Joining the lobby at address: %s"), *ServerAddress));

	if (APlayerController* localPlayerController = this->GetFirstLocalPlayerController()) {
		localPlayerController->ClientTravel(ServerAddress, ETravelType::TRAVEL_Absolute);
	}
}

void UDSGameInstance::DestroySessionAndReturn() {
	const IOnlineSubsystem* onlineSubsystem = IOnlineSubsystem::Get();
	if (!onlineSubsystem) {
		DS_LOG_ERROR("Game Instance Error: OnlineSubsystem is invalid");
		return;
	}

	const IOnlineSessionPtr sessionInterface = onlineSubsystem->GetSessionInterface();
	if (!sessionInterface.IsValid()) {
		DS_LOG_ERROR("Game Instance Error: Session Interface is invalid");
		return;
	}

	sessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UDSGameInstance::SessionDestructionComplete_EventListener);
	sessionInterface->DestroySession(NAME_GameSession);
	sessionInterface->ClearOnDestroySessionCompleteDelegates(this);
}

void UDSGameInstance::StartCatchGame() const {
	const auto world = this->GetWorld();
	if (!world) {
		DS_LOG_ERROR("Game Instance Error: World reference is invalid when trying to send players to the game level");
		return;
	}

	const FString url = this->CatchGameLevelName.ToString() + TEXT("?listen");
	
	world->ServerTravel(url);
}

UDSGameUserSettings* UDSGameInstance::GetUserSettings() const {
	return this->UserSettings;
}

void UDSGameInstance::SessionDestructionComplete_EventListener(FName SessionName, bool bWasSuccessfull) const {
	UGameplayStatics::OpenLevel(this->GetWorld(), this->MainMenuLevelName);
}
