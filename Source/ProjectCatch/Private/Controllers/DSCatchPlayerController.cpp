// Made by Dallai Studios - 2025

#include "Controllers/DSCatchPlayerController.h"

void ADSCatchPlayerController::BeginPlay() {
	Super::BeginPlay();

	this->SetInputMode(FInputModeGameAndUI());
	this->bShowMouseCursor = false;
}
