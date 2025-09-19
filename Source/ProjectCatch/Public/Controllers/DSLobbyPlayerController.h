// Made by Dallai Studios - 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DSLobbyPlayerController.generated.h"

class UDSLobbyWidget;

UCLASS()
class PROJECTCATCH_API ADSLobbyPlayerController : public APlayerController {
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category="Actor Properties")
	TSubclassOf<UUserWidget> LobbyWidgetClass;

	UPROPERTY()
	UDSLobbyWidget* LobbyWidgetInstance;
	
public:
	virtual void BeginPlay() override;
};
