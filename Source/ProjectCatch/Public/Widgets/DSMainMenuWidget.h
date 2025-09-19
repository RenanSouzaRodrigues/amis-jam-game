// Made by Dallai Studios - 2025

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DSMainMenuWidget.generated.h"

class UButton;

UCLASS()
class PROJECTCATCH_API UDSMainMenuWidget : public UUserWidget {
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
	UButton* HostGameButton;

	UPROPERTY(meta=(BindWidget))
	UButton* JoinGameButton;

	UPROPERTY(meta=(BindWidget))
	UButton* OptionsButton;

	UPROPERTY(meta=(BindWidget))
	UButton* QuitButton;

public:
	virtual void NativeOnInitialized() override;

public:
	UFUNCTION()
	void OnHostGame();

	UFUNCTION()
	void OnJoinGame();

	UFUNCTION()
	void OnQuit();
};
