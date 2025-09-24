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
	ADSLobbyPlayerState();
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	// Player Dummy Replication
public:
	UPROPERTY(Replicated)
	ADSLobbyDummy* LobbyDummy;
	
	UFUNCTION()
	void SetLobbyDummy(ADSLobbyDummy* Dummy);
	
	// Player Name Replication
public:
	UPROPERTY(ReplicatedUsing=OnRep_ChangePlayerName)
	FText PlayerName;
	
	UFUNCTION(Server, Reliable)
	void Server_ChangePlayerName(const FText& newName);
	void Server_ChangePlayerName_Implementation(const FText& newName);

	UFUNCTION()
	void OnRep_ChangePlayerName() const;

	
	// Player Confirmation Replication
public:
	UPROPERTY(ReplicatedUsing=OnRep_PlayerIsReady)
	bool PlayerIsReady;

	UFUNCTION(Server, Reliable)
	void Server_CheckPlayerReady();
	void Server_CheckPlayerReady_Implementation();

	UFUNCTION(Server, Reliable)
	void Server_UncheckPlayerReady();
	void Server_UncheckPlayerReady_Implementation();
	
	UFUNCTION()
	void OnRep_PlayerIsReady() const;
};