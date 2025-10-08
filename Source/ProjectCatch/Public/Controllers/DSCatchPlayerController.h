// Made by Dallai Studios - 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DSCatchPlayerController.generated.h"

UCLASS()
class PROJECTCATCH_API ADSCatchPlayerController : public APlayerController {
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
};
