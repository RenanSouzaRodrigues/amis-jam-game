// Made by Dallai Studios - 2025

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DSLobbyWidget.generated.h"

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

private:
	UPROPERTY()
	bool IsHost { false };

protected:
	virtual void NativeOnInitialized() override;

private:
	void HideButtons() const;
	void DisplayHostButtons() const;
	void DisplayClientButtons() const;
	
public:
	void SetUIForHost(const bool Value);
	void BuildWidget() const;

protected:
	UFUNCTION()
	void OnStartGame();

	UFUNCTION()
	void OnPlayerReady();

	UFUNCTION()
	void OnCancelSession();

	UFUNCTION()
	void OnReturnToMainMenu();
};
