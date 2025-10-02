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

	this->HideAllElements();
	
	// Main Menu Buttons. -Dallai
	if (this->HostGameButton && this->JoinGameButton && this->OptionsButton && this->QuitButton) {
		this->HostGameButton->OnClicked.AddDynamic(this, &UDSMainMenuWidget::OnHostGame);
		this->JoinGameButton->OnClicked.AddDynamic(this, &UDSMainMenuWidget::OpenJoinGameMenu);
		this->OptionsButton->OnClicked.AddDynamic(this, &UDSMainMenuWidget::OnOptions);
		this->QuitButton->OnClicked.AddDynamic(this, &UDSMainMenuWidget::OnQuit);
	}

	// Join Game Confirm Button. -Dallai
	if (this->ConfirmJoinButton) {
		this->ConfirmJoinButton->OnClicked.AddDynamic(this, &ThisClass::UDSMainMenuWidget::OnJoinGame);
	}
	
	// Volume Options. -Dallai;
	if (this->MasterVolumeSlider && this->MusicVolumeSlider && this->SfxVolumeSlider) {
		this->MusicVolumeSlider->OnValueChanged.AddDynamic(this, &ThisClass::UDSMainMenuWidget::ChangeMusicVolume);
		this->MasterVolumeSlider->OnValueChanged.AddDynamic(this, &ThisClass::ChangeMasterVolume);
		this->SfxVolumeSlider->OnValueChanged.AddDynamic(this, &ThisClass::ChangeSfxVolume);
	}

	if (this->ApplySettingsButton && this->ReturnFromOptionsButton) {
		this->ApplySettingsButton->OnClicked.AddDynamic(this, &ThisClass::ApplySettings);
		this->ReturnFromOptionsButton->OnClicked.AddDynamic(this, &ThisClass::ReturnToMainMenu);
	}
	
	this->ShowMainMenu();
}

void UDSMainMenuWidget::OnHostGame() {
	if (const auto gameInstance = Cast<UDSGameInstance>(this->GetGameInstance())) {
		gameInstance->HostGame();
	} else {
		DS_LOG_ERROR("Host game error: Fail to retrieve game instance in order to host the game. Make sure the default game instance is of type UDSGameInstance");
	}
}

void UDSMainMenuWidget::OpenJoinGameMenu() {
	this->HideAllElements();
	this->ShowJoinGameMenu();
}

void UDSMainMenuWidget::OnJoinGame() {
	if (const auto gameInstance = Cast<UDSGameInstance>(this->GetGameInstance())) {
		gameInstance->JoinGame("127.0.0.1");
	} else {
		DS_LOG_ERROR("Join game error: Fail to retrieve game instance in order to host the game. Make sure the default game instance is of type UDSGameInstance");
	}
}

void UDSMainMenuWidget::OnOptions() {
	this->HideAllElements();
	this->ShowOptionsMenu();
}

void UDSMainMenuWidget::OnQuit() {
	UKismetSystemLibrary::QuitGame(this, this->GetOwningPlayer(), EQuitPreference::Quit, true);
}

void UDSMainMenuWidget::ChangeMasterVolume(const float Value) { }

void UDSMainMenuWidget::ChangeMusicVolume(const float Value) { }

void UDSMainMenuWidget::ChangeSfxVolume(const float Value) { }

void UDSMainMenuWidget::ChangeScreenResolution() { }

void UDSMainMenuWidget::ChangeFrameRate() { }

void UDSMainMenuWidget::ToggleVSync() { }

void UDSMainMenuWidget::ChangeVideoQuality() { }

void UDSMainMenuWidget::ApplySettings() { }

void UDSMainMenuWidget::ReturnToMainMenu() {
	this->HideAllElements();
	this->ShowMainMenu();
}


void UDSMainMenuWidget::HideAllElements() const {
	// Disable all the Main Menu Elements first. -Dallai
	this->FirstPumpkinImage->SetVisibility(ESlateVisibility::Collapsed);
	this->SecondPumpkinImage->SetVisibility(ESlateVisibility::Collapsed);
	this->FirstTitleLabel->SetVisibility(ESlateVisibility::Collapsed);
	this->SecondTitleLabel->SetVisibility(ESlateVisibility::Collapsed);
	this->SecondTitleShadowLabel->SetVisibility(ESlateVisibility::Collapsed);
	this->MainMenuButtonsContainer->SetVisibility(ESlateVisibility::Collapsed);

	// Disable all the Join Game Screen. -Dallai
	this->JoinGameBackgroundImage->SetVisibility(ESlateVisibility::Collapsed);
	this->JoinGameBackgroundShadowImage->SetVisibility(ESlateVisibility::Collapsed);
	this->FirstJoinGamePumpkin->SetVisibility(ESlateVisibility::Collapsed);
	this->SecondJoinGamePumpkin->SetVisibility(ESlateVisibility::Collapsed);
	this->JoinGameAddressMessage->SetVisibility(ESlateVisibility::Collapsed);
	this->HostAddressText->SetVisibility(ESlateVisibility::Collapsed);
	this->ConfirmJoinButton->SetVisibility(ESlateVisibility::Collapsed);
	
	// Disable the options elements. -Dallai
	this->OptionsBackgroundImage->SetVisibility(ESlateVisibility::Collapsed);
	this->OptionsTextLabel->SetVisibility(ESlateVisibility::Collapsed);
	this->OptionsMenuSettingsContainer->SetVisibility(ESlateVisibility::Collapsed);
}

void UDSMainMenuWidget::ShowMainMenu() const {
	this->FirstPumpkinImage->SetVisibility(ESlateVisibility::Visible);
	this->SecondPumpkinImage->SetVisibility(ESlateVisibility::Visible);
	this->FirstTitleLabel->SetVisibility(ESlateVisibility::Visible);
	this->SecondTitleLabel->SetVisibility(ESlateVisibility::Visible);
	this->SecondTitleShadowLabel->SetVisibility(ESlateVisibility::Visible);
	this->MainMenuButtonsContainer->SetVisibility(ESlateVisibility::Visible);
}

void UDSMainMenuWidget::ShowJoinGameMenu() const {
	this->JoinGameBackgroundImage->SetVisibility(ESlateVisibility::Visible);
	this->JoinGameBackgroundShadowImage->SetVisibility(ESlateVisibility::Visible);
	this->FirstJoinGamePumpkin->SetVisibility(ESlateVisibility::Visible);
	this->SecondJoinGamePumpkin->SetVisibility(ESlateVisibility::Visible);
	this->JoinGameAddressMessage->SetVisibility(ESlateVisibility::Visible);
	this->HostAddressText->SetVisibility(ESlateVisibility::Visible);
	this->ConfirmJoinButton->SetVisibility(ESlateVisibility::Visible);
}

void UDSMainMenuWidget::ShowOptionsMenu() const {
	this->OptionsBackgroundImage->SetVisibility(ESlateVisibility::Visible);
	this->OptionsTextLabel->SetVisibility(ESlateVisibility::Visible);
	this->OptionsMenuSettingsContainer->SetVisibility(ESlateVisibility::Visible);
}
