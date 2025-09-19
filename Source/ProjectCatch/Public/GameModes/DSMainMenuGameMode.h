// Made by Dallai Studios - 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "DSMainMenuGameMode.generated.h"

class UDSMainMenuWidget;

UCLASS()
class PROJECTCATCH_API ADSMainMenuGameMode : public AGameMode {
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
};
