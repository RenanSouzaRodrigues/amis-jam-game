// Made by Dallai Studios - 2025

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DSGameInstance.generated.h"

class UDSGameUserSettings;

UCLASS()
class PROJECTCATCH_API UDSGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Game Instance Properties")
	FName LobbyLevelName { FName("Level_Lobby") };

	UPROPERTY(EditAnywhere, Category="Game Instance Properties")
	FName MainMenuLevelName { FName("Level_MainMenu") };

	UPROPERTY(EditAnywhere, Category="Game Instance Properties")
	TObjectPtr<USoundMix> GameSoundMixer;

	UPROPERTY(EditAnywhere, Category="Game Instance Properties")
	TObjectPtr<USoundClass> MasterSoundClass;

	UPROPERTY(EditAnywhere, Category="Game Instance Properties")
	TObjectPtr<USoundClass> MusicSoundClass;

	UPROPERTY(EditAnywhere, Category="Game Instance Properties")
	TObjectPtr<USoundClass> SfxSoundClass;
	
private:
	UPROPERTY()
	UDSGameUserSettings* UserSettings;

public:
	virtual void Init() override;
	
public:
    UFUNCTION(BlueprintCallable, Category="Online Features")
    void HostGame() const;
    
    UFUNCTION(BlueprintCallable, Category="Online Feaures")
    void JoinGame(const FString& ServerAddress) const;

	UFUNCTION(BlueprintCallable, Category="Online Feature")
	void DestroySessionAndReturn();

	UFUNCTION()
	UDSGameUserSettings* GetUserSettings() const;
	
private:
	void SessionDestructionComplete_EventListener(FName SessionName, bool bWasSuccessfull) const;
};
