// Made by Dallai Studios - 2025

#include "Widgets/DSLobbyWidget.h"

#include "Actors/DSLobbyDummy.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Controllers/DSLobbyPlayerController.h"
#include "PlayerStates/DSLobbyPlayerState.h"
#include "Utils/DSMacros.h"

void UDSLobbyWidget::NativeOnInitialized() {
	Super::NativeOnInitialized();

	if (this->StartGameButton) {
		this->StartGameButton->OnClicked.AddDynamic(this, &UDSLobbyWidget::OnStartGame);
	}

	if (this->CancelButton) {
		this->CancelButton->OnClicked.AddDynamic(this, &UDSLobbyWidget::OnCancelSession);
	}

	if (this->PlayerReadyButton) {
		this->PlayerReadyButton->OnClicked.AddDynamic(this, &UDSLobbyWidget::OnPlayerReady);
	}

	if (this->PlayerNotReadyButton) {
		this->PlayerNotReadyButton->OnClicked.AddDynamic(this, &UDSLobbyWidget::OnPlayerNotReady);
	}
	
	if (this->ReturnButton) {
		this->ReturnButton->OnClicked.AddDynamic(this, &UDSLobbyWidget::OnReturnToMainMenu);
	}

	if (this->ChangeNameButton) {
		this->ChangeNameButton->OnClicked.AddDynamic(this, &UDSLobbyWidget::OnChangePlayerName);
	}
}

void UDSLobbyWidget::HideButtons() const {
	if (this->StartGameButton) this->StartGameButton->SetVisibility(ESlateVisibility::Collapsed);
	if (this->CancelButton) this->CancelButton->SetVisibility(ESlateVisibility::Collapsed);
	if (this->PlayerReadyButton) this->PlayerReadyButton->SetVisibility(ESlateVisibility::Collapsed);
	if (this->PlayerNotReadyButton) this->PlayerNotReadyButton->SetVisibility(ESlateVisibility::Collapsed);
	if (this->ReturnButton) this->ReturnButton->SetVisibility(ESlateVisibility::Collapsed);
}

void UDSLobbyWidget::DisplayHostButtons() const {
	if (this->StartGameButton) this->StartGameButton->SetVisibility(ESlateVisibility::Visible);
	if (this->CancelButton) this->CancelButton->SetVisibility(ESlateVisibility::Visible);
}

void UDSLobbyWidget::DisplayClientButtons() const {
	if (this->PlayerNotReadyButton) this->PlayerNotReadyButton->SetVisibility(ESlateVisibility::Visible);
	if (this->ReturnButton) this->ReturnButton->SetVisibility(ESlateVisibility::Visible);
}

void UDSLobbyWidget::SetUIForHost(const bool Value) {
	this->IsHost = Value;
}

void UDSLobbyWidget::BuildWidget() const {
	this->HideButtons();
	
	if (this->IsHost) {
		this->DisplayHostButtons();
		return;
	}

	this->DisplayClientButtons();
}

void UDSLobbyWidget::SetPlayerStateReference(ADSLobbyPlayerState* PlayerState) {
	this->LobbyPlayerStateReference = PlayerState;
}

void UDSLobbyWidget::OnStartGame() {
	DS_LOG_SUCCESS("Server Start Game");
}

void UDSLobbyWidget::OnCancelSession() {
	DS_LOG_SUCCESS("Server Cancel Game");
}

void UDSLobbyWidget::OnPlayerReady() {
	DS_LOG_SUCCESS("Client Ready to Play");
	if (this->LobbyPlayerStateReference) {
		this->LobbyPlayerStateReference->Server_CheckPlayerReady();
		if (this->PlayerReadyButton) this->PlayerReadyButton->SetVisibility(ESlateVisibility::Collapsed);
		if (this->PlayerNotReadyButton) this->PlayerNotReadyButton->SetVisibility(ESlateVisibility::Visible);
	}
}

void UDSLobbyWidget::OnPlayerNotReady() {
	DS_LOG_INFO("Client not ready to play");
	if (this->LobbyPlayerStateReference) {
		this->LobbyPlayerStateReference->Server_UncheckPlayerReady();
		if (this->PlayerNotReadyButton) this->PlayerNotReadyButton->SetVisibility(ESlateVisibility::Collapsed);
		if (this->PlayerReadyButton) this->PlayerReadyButton->SetVisibility(ESlateVisibility::Visible);
	}
}

void UDSLobbyWidget::OnReturnToMainMenu() {
	DS_LOG_INFO("Client return to Main Menu");

	if (const ADSLobbyPlayerController* playerController = Cast<ADSLobbyPlayerController>(this->GetOwningPlayer())) {
		playerController->DestroyDummyAndLeave();
	}
}

void UDSLobbyWidget::OnChangePlayerName() {
	if (!this->PlayerNameTextBox) {
		DS_LOG_ERROR("Player name Text box is not defined");
		return;
	}

	if (!this->LobbyPlayerStateReference) {
		DS_LOG_ERROR("Lobby player state refence is null on lobby widget");
		return;
	}
	
	this->LobbyPlayerStateReference->Server_ChangePlayerName(this->PlayerNameTextBox->GetText());
}