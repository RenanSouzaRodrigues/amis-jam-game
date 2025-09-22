// Made by Dallai Studios - 2025

#include "Widgets/DSPlayerNameWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UDSPlayerNameWidget::ChangePlayerName(const FText& newName) const {
	this->PlayerNameLabel->SetText(newName);
}