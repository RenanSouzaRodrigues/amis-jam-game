// Made by Dallai Studios - 2025

#include "Widgets/DSLobbyWidget.h"
#include "Components/Button.h"

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

	if (this->ReturnButton) {
		this->ReturnButton->OnClicked.AddDynamic(this, &UDSLobbyWidget::OnReturnToMainMenu);
	}
}

void UDSLobbyWidget::HideButtons() const {
	if (this->StartGameButton) this->StartGameButton->SetVisibility(ESlateVisibility::Collapsed);
	if (this->CancelButton) this->CancelButton->SetVisibility(ESlateVisibility::Collapsed);
	if (this->PlayerReadyButton) this->PlayerReadyButton->SetVisibility(ESlateVisibility::Collapsed);
	if (this->ReturnButton) this->ReturnButton->SetVisibility(ESlateVisibility::Collapsed);
}

void UDSLobbyWidget::DisplayHostButtons() const {
	if (this->StartGameButton) this->StartGameButton->SetVisibility(ESlateVisibility::Visible);
	if (this->CancelButton) this->CancelButton->SetVisibility(ESlateVisibility::Visible);
}

void UDSLobbyWidget::DisplayClientButtons() const {
	if (this->PlayerReadyButton) this->PlayerReadyButton->SetVisibility(ESlateVisibility::Visible);
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

void UDSLobbyWidget::OnStartGame() {
	
}

void UDSLobbyWidget::OnCancelSession() {
	
}

void UDSLobbyWidget::OnPlayerReady() {
	
}

void UDSLobbyWidget::OnReturnToMainMenu() {
	
}