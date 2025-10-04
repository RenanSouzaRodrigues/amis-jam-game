// Made by Dallai Studios - 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "DSCatchPlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class PROJECTCATCH_API ADSCatchPlayerCharacter : public ACharacter {
	GENERATED_BODY()

	// Actor Components
public:
	UPROPERTY(EditAnywhere, Category="Actor Components")
	TObjectPtr<USpringArmComponent> CameraSpringArm;

	UPROPERTY(EditAnywhere, Category="Actor Components")
	TObjectPtr<UCameraComponent> PlayerCamera;

	UPROPERTY(EditAnywhere, Category="Actor Components")
	TObjectPtr<UStaticMeshComponent> HeadMesh;

	
	// Actor Properties
public:
	UPROPERTY(EditAnywhere, Category="Actor Properties")
	TObjectPtr<USkeletalMesh> RunnerSkeletalMesh;

	UPROPERTY(EditAnywhere, Category="Actor Properties")
	TObjectPtr<USkeletalMesh> CatcherSkeletalMesh;

	UPROPERTY(EditAnywhere, Category="Actor Properties")
	FName HeadSocketName;
	
	UPROPERTY(EditAnywhere, Category="Actor Properties")
	TObjectPtr<UStaticMesh> RunnerHair;

	UPROPERTY(EditAnywhere, Category="Actor Properties")
	TObjectPtr<UStaticMesh> CatcherPumpkin;

	UPROPERTY(EditAnywhere, Category="Actor Properties")
	float RunnerMovementSpeed { 600 };

	UPROPERTY(EditAnywhere, Category="Actor Properties")
	float CatcherMovementSpeed { 680 };

	UPROPERTY(EditAnywhere, Category="Actor Properties")
	float CatcherDetectionDistance { 60 };

	UPROPERTY(EditAnywhere, Category="Actor Properties")
	float DetectionSphereRadius { 50 };

private:
	FCollisionQueryParams queryParams;

	UPROPERTY(EditAnywhere, Category="Actor Properties")
	bool IsCatcher { false };
	
	// Actor Inputs 
public:
	UPROPERTY(EditAnywhere, Category="Actor Inputs")
	TObjectPtr<UInputMappingContext> CharacterInputMappingContext;

	UPROPERTY(EditAnywhere, Category="Actor Inputs")
	TObjectPtr<UInputAction> MovementInputAction;

	UPROPERTY(EditAnywhere, Category="Actor Inputs")
	TObjectPtr<UInputAction> AttackInputAction;
	
	
	// Unreal Engine Lifecycle
public:
	ADSCatchPlayerCharacter();
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;	

protected:
	virtual void BeginPlay() override;


	// Movement
public:
	void Move(const FInputActionValue& Value);

	
	// Attack
public:
	void Attack(const FInputActionValue& Value);
	void PerformAttackTracer() const;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsTheCatcher() const;

	UFUNCTION()
	void SetMovementSpeed() const;

	UFUNCTION()
	void SetSkeletalMesh() const;
};
