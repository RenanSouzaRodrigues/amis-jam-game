// Made by Dallai Studios - 2025

#include "Characters/DSCatchPlayerCharacter.h"

ADSCatchPlayerCharacter::ADSCatchPlayerCharacter() {
	PrimaryActorTick.bCanEverTick = false;
}

void ADSCatchPlayerCharacter::BeginPlay() {
	Super::BeginPlay();
}

bool ADSCatchPlayerCharacter::IsTheCatcher() const {
	return false;
}