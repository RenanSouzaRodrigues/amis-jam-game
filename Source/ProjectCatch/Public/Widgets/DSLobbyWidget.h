// Made by Dallai Studios - 2025

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DSLobbyWidget.generated.h"

class ADSLobbyPlayerState;
class UEditableTextBox;
class UButton;

UCLASS()
class PROJECTCATCH_API UDSLobbyWidget : public UUserWidget {
	GENERATED_BODY()

protected:
	UPROPERTY(meta=(BindWidget))
	UButton* StartGameButton;

	UPROPERTY(meta=(BindWidget))
	UButton* CancelButton;
	
	UPROPERTY(meta=(BindWidget))
	UButton* PlayerReadyButton;

	UPROPERTY(meta=(BindWidget))
	UButton* ReturnButton;

	UPROPERTY(meta=(BindWidget))
	UEditableTextBox* PlayerNameTextBox;

	UPROPERTY(meta=(BindWidget))
	UButton* ChangeNameButton;
	

private:
	UPROPERTY()
	bool IsHost { false };

	UPROPERTY()
	ADSLobbyPlayerState* LobbyPlayerStateReference;

protected:
	virtual void NativeOnInitialized() override;

private:
	void HideButtons() const;
	void DisplayHostButtons() const;
	void DisplayClientButtons() const;
	
public:
	void SetUIForHost(const bool Value);
	void BuildWidget() const;

public:
	UFUNCTION()
	void SetPlayerStateReference(ADSLobbyPlayerState* PlayerState);

protected:
	UFUNCTION()
	void OnStartGame();

	UFUNCTION()
	void OnPlayerReady();

	UFUNCTION()
	void OnCancelSession();

	UFUNCTION()
	void OnReturnToMainMenu();

	UFUNCTION()
	void OnChangePlayerName();
};
