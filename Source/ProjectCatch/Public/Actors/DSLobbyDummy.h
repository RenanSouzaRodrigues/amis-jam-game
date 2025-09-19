// Made by Dallai Studios - 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DSLobbyDummy.generated.h"

class UCapsuleComponent;

UCLASS()
class PROJECTCATCH_API ADSLobbyDummy : public AActor {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Actor Components")
	TObjectPtr<UCapsuleComponent> DummyCapsule;
	
	UPROPERTY(EditAnywhere, Category="Actor Components")
	TObjectPtr<USkeletalMeshComponent> DummySkeletalMesh;
	
public:
	ADSLobbyDummy();

protected:
	virtual void BeginPlay() override;
};
