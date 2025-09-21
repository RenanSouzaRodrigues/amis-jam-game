// Made by Dallai Studios - 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DSPlayerCharacter.generated.h"

UCLASS()
class PROJECTCATCH_API ADSPlayerCharacter : public ACharacter {
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category="Actor Components")
	TObjectPtr<UStaticMeshComponent> CatcherHat;

protected:
	UPROPERTY(EditAnywhere, Category="Actor Properties")
	float RunnerMovementSpeed { 600.f };

	UPROPERTY(EditAnywhere, Category="Actor Properties")
	float CatcherMovementSpeed { 680.f };
	
public:
	ADSPlayerCharacter();

protected:
	virtual void BeginPlay() override;

protected:
	UFUNCTION(BlueprintCallable)
	void Move(const float AxisValueX, const float AxisValueY);

	UFUNCTION(BlueprintCallable)
	void Attack();
};
