// Made by Dallai Studios - 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "DSLobbyGameMode.generated.h"

class ADSLobbyDummy;

UCLASS()
class PROJECTCATCH_API ADSLobbyGameMode : public AGameMode {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Actor Properties")
	TSubclassOf<ADSLobbyDummy> PlayerDummyClass;
	
public:
	virtual void PostLogin(APlayerController* NewPlayer) override;
};
