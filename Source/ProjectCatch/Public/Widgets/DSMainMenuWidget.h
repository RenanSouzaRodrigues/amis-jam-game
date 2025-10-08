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

	UPROPERTY(meta=(BindWidget))
	UTextBlock* SecondTitleShadowLabel;

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

public:
	virtual void NativeOnInitialized() override;

public:
	UFUNCTION()
	void OnHostGame();

	UFUNCTION()
	void OnJoinGame();
	
	UFUNCTION()
	void OnOptions();
	
	UFUNCTION()
	void OnQuit();

private:
	void HideAllElements() const;
	void ShowMainMenu() const;
	void ShowOptionsMenu() const;
};