// Made by Dallai Studios - 2025

#include "Widgets/DSMainMenuWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "GameInstance/DSGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Utils/DSMacros.h"

void UDSMainMenuWidget::NativeOnInitialized() {
	Super::NativeOnInitialized();
	
	// Main Menu Buttons. -Dallai
	if (this->HostGameButton && this->JoinGameButton && this->OptionsButton && this->QuitButton) {
		this->HostGameButton->OnClicked.AddDynamic(this, &UDSMainMenuWidget::OnHostGame);
		this->JoinGameButton->OnClicked.AddDynamic(this, &UDSMainMenuWidget::OnJoinGame);
		this->OptionsButton->OnClicked.AddDynamic(this, &UDSMainMenuWidget::OnOptions);
		this->QuitButton->OnClicked.AddDynamic(this, &UDSMainMenuWidget::OnQuit);
	}

	this->HideAllElements();
	this->ShowMainMenu();
}

void UDSMainMenuWidget::OnHostGame() {
	const auto gameInstance = Cast<UDSGameInstance>(this->GetGameInstance());

	if (!gameInstance) {
		DS_LOG_ERROR("Host game error: Fail to retrieve game instance in order to host the game. Make sure the default game instance is of type UDSGameInstance");
		return;
	}

	gameInstance->CreateSession();
}

void UDSMainMenuWidget::OnJoinGame() {
	const auto gameInstance = Cast<UDSGameInstance>(this->GetGameInstance());

	if (!gameInstance) {
		DS_LOG_ERROR("Host game error: Fail to retrieve game instance in order to host the game. Make sure the default game instance is of type UDSGameInstance");
		return;
	}

	gameInstance->FindSession();
}

void UDSMainMenuWidget::OnOptions() {
	// this->HideAllElements();
	// this->ShowOptionsMenu();
}

void UDSMainMenuWidget::OnQuit() {
	UKismetSystemLibrary::QuitGame(this, this->GetOwningPlayer(), EQuitPreference::Quit, true);
}

void UDSMainMenuWidget::HideAllElements() const {
	// Disable all the Main Menu Elements first. -Dallai
	this->FirstPumpkinImage->SetVisibility(ESlateVisibility::Collapsed);
	this->SecondPumpkinImage->SetVisibility(ESlateVisibility::Collapsed);
	this->FirstTitleLabel->SetVisibility(ESlateVisibility::Collapsed);
	this->SecondTitleLabel->SetVisibility(ESlateVisibility::Collapsed);
	this->SecondTitleShadowLabel->SetVisibility(ESlateVisibility::Collapsed);
	this->MainMenuButtonsContainer->SetVisibility(ESlateVisibility::Collapsed);
}

void UDSMainMenuWidget::ShowMainMenu() const {
	this->FirstPumpkinImage->SetVisibility(ESlateVisibility::Visible);
	this->SecondPumpkinImage->SetVisibility(ESlateVisibility::Visible);
	this->FirstTitleLabel->SetVisibility(ESlateVisibility::Visible);
	this->SecondTitleLabel->SetVisibility(ESlateVisibility::Visible);
	this->SecondTitleShadowLabel->SetVisibility(ESlateVisibility::Visible);
	this->MainMenuButtonsContainer->SetVisibility(ESlateVisibility::Visible);
}

void UDSMainMenuWidget::ShowOptionsMenu() const {
	// this->OptionsBackgroundImage->SetVisibility(ESlateVisibility::Visible);
	// this->OptionsTextLabel->SetVisibility(ESlateVisibility::Visible);
	// this->OptionsMenuSettingsContainer->SetVisibility(ESlateVisibility::Visible);
}
