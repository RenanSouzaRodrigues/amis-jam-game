// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/DSGameInstance.h"

#include "Kismet/GameplayStatics.h"
#include "Utils/DSMacros.h"

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