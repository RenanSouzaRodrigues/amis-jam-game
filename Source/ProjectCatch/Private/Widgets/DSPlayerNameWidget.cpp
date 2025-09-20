// Made by Dallai Studios - 2025

#include "Widgets/DSPlayerNameWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UDSPlayerNameWidget::ShowConfirmationImage() const {
	this->ConfirmationImage->SetVisibility(ESlateVisibility::Visible);
}

void UDSPlayerNameWidget::HideConfirmationImage() const {
	this->ConfirmationImage->SetVisibility(ESlateVisibility::Collapsed);
}

void UDSPlayerNameWidget::ChangePlayerName(const FText& newName) const {
	this->PlayerNameLabel->SetText(newName);
}