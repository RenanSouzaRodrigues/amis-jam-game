// Made by Dallai Studios - 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "DSGameUserSettings.generated.h"

UCLASS()
class PROJECTCATCH_API UDSGameUserSettings : public UGameUserSettings {
	GENERATED_BODY()

public:
	UPROPERTY(Config)
	float MasterVolume;

	UPROPERTY(Config)
	float MusicVolume;

	UPROPERTY(Config)
	float SfxVolume;

	UPROPERTY(Config)
	int GameFps;

	UPROPERTY(Config)
	bool VSync;

	UFUNCTION()
	FORCEINLINE void SetMasterVolume(const float Volume) { this->MasterVolume = Volume; }

	UFUNCTION()
	FORCEINLINE float GetMasterVolume() const { return this->MasterVolume; };

	UFUNCTION()
	FORCEINLINE void SetMusicVolume(const float Volume) { this->MusicVolume = Volume; }

	UFUNCTION()
	FORCEINLINE float GetMusicVolume() const { return this->MusicVolume; }

	UFUNCTION()
	FORCEINLINE void SetSfxVolume(const float Volume) { this->SfxVolume = Volume; }

	UFUNCTION()
	FORCEINLINE float GetSfxVolume() const { return this->SfxVolume; }

	UFUNCTION()
	FORCEINLINE void SetGameFps(const int Value) { this->GameFps = Value; }

	UFUNCTION()
	FORCEINLINE int GetGameFps() const { return this->GameFps; }

	UFUNCTION()
	FORCEINLINE void SetVSync(const bool value) { this->VSync = value; }

	UFUNCTION()
	FORCEINLINE bool GetVSync() const { return this->VSync; }
};
