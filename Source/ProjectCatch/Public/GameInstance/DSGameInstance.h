// Made by Dallai Studios - 2025

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DSGameInstance.generated.h"

UCLASS()
class PROJECTCATCH_API UDSGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Game Instance Properties")
	FName LobbyLevelName { FName("Level_Lobby") };
	
public:
    UFUNCTION(BlueprintCallable, Category="Online Features")
    void HostGame() const;
    
    UFUNCTION(BlueprintCallable, Category="Online Feaures")
    void JoinGame(const FString& ServerAddress) const;
};
