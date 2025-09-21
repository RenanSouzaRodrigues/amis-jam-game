// Made by Dallai Studios - 2025

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DSPlayerNameWidget.generated.h"

class UTextBlock;
class UImage;

UCLASS()
class PROJECTCATCH_API UDSPlayerNameWidget : public UUserWidget {
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
	UImage* ConfirmationImage;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* PlayerNameLabel;

public:
	UPROPERTY(EditAnywhere, Category="Actor Properties")
	TObjectPtr<UTexture2D> ReadyItem;

	UPROPERTY(EditAnywhere, Category="Actor Properties")
	TObjectPtr<UTexture2D> NotReadyIcon;

public:
	void ShowConfirmationImage() const;
	void HideConfirmationImage() const;
	void ChangePlayerName(const FText& newName) const;
};
