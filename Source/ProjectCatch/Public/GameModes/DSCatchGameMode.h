// Made by Dallai Studios - 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "DSCatchGameMode.generated.h"

UCLASS()
class PROJECTCATCH_API ADSCatchGameMode : public AGameMode {
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category="Game Mode Properties")
	float TimeToWaitToStartGame { 10.f };
	
private:
	FTimerHandle WaitPlayersTimeHandle;

protected:
	virtual void BeginPlay() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;

	UFUNCTION()
	void StartGame_EventListener();
};