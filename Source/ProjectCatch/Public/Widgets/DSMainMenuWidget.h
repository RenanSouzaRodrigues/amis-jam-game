// Made by Dallai Studios - 2025

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "DSMainMenuWidget.generated.h"

class UTextBlock;
class UVerticalBox;
class UEditableTextBox;
class UButton;
class USlider;

UCLASS()
class PROJECTCATCH_API UDSMainMenuWidget : public UUserWidget {
	GENERATED_BODY()

public:
	// Game Title. -Dallai
	UPROPERTY(meta=(BindWidget))
	UImage* FirstPumpkinImage;

	UPROPERTY(meta=(BindWidget))
	UImage* SecondPumpkinImage;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* FirstTitleLabel;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* SecondTitleLabel;

	// Main Menu Buttons. -Dallai
	UPROPERTY(meta=(BindWidget))
	UVerticalBox* MainMenuButtonsContainer;
	
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
	UImage* JoinGameBackgroundImage;

	UPROPERTY(meta=(BindWidget))
	UImage* JoinGameBackgroundShadowImage;

	UPROPERTY(meta=(BindWidget))
	UImage* FirstJoinGamePumpkin;

	UPROPERTY(meta=(BindWidget))
	UImage* SecondJoinGamePumpkin;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* JoinGameAddressMessage;
	
	UPROPERTY(meta=(BindWidget))
	UEditableTextBox* HostAddressText;

	UPROPERTY(meta=(BindWidget))
	UButton* ConfirmJoinButton;
	
	// Options Configs;
	UPROPERTY(meta=(BindWidget))
	UImage* OptionsBackgroundImage;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* OptionsTextLabel;
	
	UPROPERTY(meta=(BindWidget))
	UVerticalBox* OptionsMenuSettingsContainer;
	
	UPROPERTY(meta=(BindWidget))
	USlider* MasterVolumeSlider;

	UPROPERTY(meta=(BindWidget))
	USlider* MusicVolumeSlider;

	UPROPERTY(meta=(BindWidget))
	USlider* SfxVolumeSlider;

	UPROPERTY(meta=(BindWidget))
	UButton* ApplySettingsButton;

	UPROPERTY(meta=(BindWidget))
	UButton* ReturnFromOptionsButton;

public:
	virtual void NativeOnInitialized() override;

public:
	UFUNCTION()
	void OnHostGame();

	UFUNCTION()
	void OpenJoinGameMenu();
	
	UFUNCTION()
	void OnJoinGame();

	UFUNCTION()
	void OnOptions();
	
	UFUNCTION()
	void OnQuit();

	UFUNCTION()
	void ChangeMasterVolume(const float Value);

	UFUNCTION()
	void ChangeMusicVolume(const float Value);

	UFUNCTION()
	void ChangeSfxVolume(const float Value);

	UFUNCTION()
	void ChangeScreenResolution();

	UFUNCTION()
	void ToggleVSync();

	UFUNCTION()
	void ChangeFrameRate();

	UFUNCTION()
	void ChangeVideoQuality();

	UFUNCTION()
	void ApplySettings();

	UFUNCTION()
	void ReturnToMainMenu();

private:
	void HideAllElements() const;
	void ShowMainMenu() const;
	void ShowJoinGameMenu() const;
	void ShowOptionsMenu() const;
};