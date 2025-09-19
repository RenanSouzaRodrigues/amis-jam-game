// Made by Dallai Studios - 2025

#include "Widgets/DSMainMenuWidget.h"
#include "Components/Button.h"
#include "GameInstance/DSGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Utils/DSMacros.h"

void UDSMainMenuWidget::NativeOnInitialized() {
	Super::NativeOnInitialized();

	if (this->HostGameButton) {
		this->HostGameButton->OnClicked.AddDynamic(this, &UDSMainMenuWidget::OnHostGame);
	}

	if (this->JoinGameButton) {
		this->JoinGameButton->OnClicked.AddDynamic(this, &UDSMainMenuWidget::OnJoinGame);
	}

	if (this->QuitButton) {
		this->QuitButton->OnClicked.AddDynamic(this, &UDSMainMenuWidget::OnQuit);
	}
}

void UDSMainMenuWidget::OnHostGame() {
	if (const auto gameInstance = Cast<UDSGameInstance>(this->GetGameInstance())) {
		gameInstance->HostGame();
	} else {
		DS_LOG_ERROR("Host game error: Fail to retrieve game instance in order to host the game. Make sure the default game instance is of type UDSGameInstance");
	}
}

void UDSMainMenuWidget::OnJoinGame() {
	if (const auto gameInstance = Cast<UDSGameInstance>(this->GetGameInstance())) {
		gameInstance->JoinGame("127.0.0.1");
	} else {
		DS_LOG_ERROR("Join game error: Fail to retrieve game instance in order to host the game. Make sure the default game instance is of type UDSGameInstance");
	}
}

void UDSMainMenuWidget::OnQuit() {
	UKismetSystemLibrary::QuitGame(this, this->GetOwningPlayer(), EQuitPreference::Quit, true);
}