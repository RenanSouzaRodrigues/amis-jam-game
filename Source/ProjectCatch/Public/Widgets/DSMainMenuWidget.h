// Made by Dallai Studios - 2025

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DSMainMenuWidget.generated.h"

class UEditableTextBox;
class UButton;
class USlider;

UCLASS()
class PROJECTCATCH_API UDSMainMenuWidget : public UUserWidget {
	GENERATED_BODY()

public:
	// Main Menu
	UPROPERTY(meta=(BindWidget))
	UButton* HostGameButton;

	UPROPERTY(meta=(BindWidget))
	UButton* JoinGameButton;

	UPROPERTY(meta=(BindWidget))
	UButton* OptionsButton;

	UPROPERTY(meta=(BindWidget))
	UButton* QuitButton;

	// Join Game
	UPROPERTY(meta=(BindWidget))
	UEditableTextBox* HostAddressText;

	UPROPERTY(meta=(BindWidget))
	UButton* ConfirmJoinButton;
	
	// Options Configs;
	UPROPERTY(meta=(BindWidget))
	USlider* MasterVolumeSlider;

	UPROPERTY(meta=(BindWidget))
	USlider* MusicVolumeSlider;

	UPROPERTY(meta=(BindWidget))
	USlider* SfxVolumeSlider;


public:
	virtual void NativeOnInitialized() override;

public:
	UFUNCTION()
	void OnHostGame();

	UFUNCTION()
	void OnJoinGame();

	UFUNCTION()
	void OnQuit();

	UFUNCTION()
	void ChangeMasterVolume();

	UFUNCTION()
	void ChangeMusiceVolume();

	UFUNCTION()
	void ChangeSfxVolume();
};
