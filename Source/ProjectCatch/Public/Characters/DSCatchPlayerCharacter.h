// Made by Dallai Studios - 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DSCatchPlayerCharacter.generated.h"

UCLASS()
class PROJECTCATCH_API ADSCatchPlayerCharacter : public ACharacter {
	GENERATED_BODY()

public:
	ADSCatchPlayerCharacter();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsTheCatcher() const;
};
