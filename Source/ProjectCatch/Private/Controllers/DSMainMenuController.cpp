// Made by Dallai Studios - 2025

#include "Controllers/DSMainMenuController.h"

#include "Blueprint/UserWidget.h"
#include "Utils/DSMacros.h"
#include "Widgets/DSMainMenuWidget.h"

void ADSMainMenuController::BeginPlay() {
	if (!this->MainMenuWidgetClass) {
		DS_LOG_ERROR("Main Menu Controller Error: Main Menu Widget Class is not defined.");
		return;
	}

	this->MainMenuWidgetInstance = CreateWidget<UDSMainMenuWidget>(this->GetWorld(), this->MainMenuWidgetClass);

	if (this->MainMenuWidgetInstance) {
		this->MainMenuWidgetInstance->AddToViewport();
	}

	this->bShowMouseCursor = true;
	this->SetInputMode(FInputModeUIOnly());
}
