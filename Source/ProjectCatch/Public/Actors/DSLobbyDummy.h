// Made by Dallai Studios - 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DSLobbyDummy.generated.h"

class UWidgetComponent;
class UCapsuleComponent;

UCLASS()
class PROJECTCATCH_API ADSLobbyDummy : public AActor {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Actor Components")
	TObjectPtr<UCapsuleComponent> DummyCapsule;
	
	UPROPERTY(EditAnywhere, Category="Actor Components")
	TObjectPtr<USkeletalMeshComponent> DummySkeletalMesh;
	
	UPROPERTY(EditAnywhere, Category="Actor Components")
	TObjectPtr<UWidgetComponent> PlayerNameWidget;

	UPROPERTY(EditAnywhere, Category="Actor Components")
	TObjectPtr<UStaticMeshComponent> ConfirmationMesh;
	
public:
	ADSLobbyDummy();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void UpdatePlayerName(const FText& NewName) const;

	UFUNCTION()
	void TogglePlayerConfirmation() const;
};
