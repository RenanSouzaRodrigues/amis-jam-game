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
	
	// ====================================================================
	// Unreal Lifecycle Methods
	// ====================================================================
public:
	ADSLobbyPlayerState();
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


	
	// ====================================================================
	// Player Lobby Dummy
	// ====================================================================
public:
	UPROPERTY(Replicated)
	ADSLobbyDummy* LobbyDummy { nullptr };
	
	UFUNCTION()
	void SetLobbyDummy(ADSLobbyDummy* Dummy);
	

	
	// ====================================================================
	// Player Name
	// ====================================================================
public:
	UPROPERTY(ReplicatedUsing=OnRep_ChangePlayerName)
	FText PlayerName { FText::FromString("Player Name") };

	UFUNCTION(Server, Reliable)
	void Server_ChangePlayerName(const FText& newName);
	void Server_ChangePlayerName_Implementation(const FText& newName);

	UFUNCTION()
	void OnRep_ChangePlayerName() const;

	
	// ====================================================================
	// Player Confirmation
	// ====================================================================
public:
	UPROPERTY(ReplicatedUsing=OnRep_TogglePlayerReady)
	bool PlayerIsReady;

	UFUNCTION(Server, Reliable)
	void Server_TogglePlayerReady(const bool value);
	void Server_TogglePlayerReady_Implementation(const bool value);
	
	UFUNCTION()
	void OnRep_TogglePlayerReady() const;
};