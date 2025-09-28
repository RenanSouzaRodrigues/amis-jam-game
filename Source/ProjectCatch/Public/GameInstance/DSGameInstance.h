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

	UPROPERTY(EditAnywhere, Category="Game Instance Properties")
	FName MainMenuLevelName { FName("Level_MainMenu") };

public:
    UFUNCTION(BlueprintCallable, Category="Online Features")
    void HostGame() const;
    
    UFUNCTION(BlueprintCallable, Category="Online Feaures")
    void JoinGame(const FString& ServerAddress) const;

	UFUNCTION(BlueprintCallable, Category="Online Feature")
	void DestroySessionAndReturn();

private:
	void SessionDestructionComplete_EventListener(FName SessionName, bool bWasSuccessfull) const;
};
