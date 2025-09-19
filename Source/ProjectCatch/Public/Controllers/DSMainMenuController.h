// Made by Dallai Studios - 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DSMainMenuController.generated.h"

class UDSMainMenuWidget;

UCLASS()
class PROJECTCATCH_API ADSMainMenuController : public APlayerController {
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category="Actor Properties")
	TSubclassOf<UUserWidget> MainMenuWidgetClass;

	UPROPERTY()
	UDSMainMenuWidget* MainMenuWidgetInstance;
	
public:
	virtual void BeginPlay() override;
};
