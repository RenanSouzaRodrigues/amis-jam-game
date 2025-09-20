// Made by Dallai Studios - 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "DSLobbyPlayerState.generated.h"

class ADSLobbyDummy;
class FLifetimeProperty;

UCLASS()
class PROJECTCATCH_API ADSLobbyPlayerState : public APlayerState {
	GENERATED_BODY()

public:
	UPROPERTY(Replicated)
	ADSLobbyDummy* LobbyDummy;

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UFUNCTION()
	void SetLobbyDummy(ADSLobbyDummy* Dummy);
};
