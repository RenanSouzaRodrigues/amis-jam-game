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

	// =================================================================
	// ACTOR COMPONENTS
	// =================================================================
protected:
	UPROPERTY(EditAnywhere, Category="Actor Components")
	TObjectPtr<USpringArmComponent> CameraSpringArm;

	UPROPERTY(EditAnywhere, Category="Actor Components")
	TObjectPtr<UCameraComponent> PlayerCamera;

	UPROPERTY(EditAnywhere, Category="Actor Components")
	TObjectPtr<UStaticMeshComponent> HeadMesh;

	
	
	// =================================================================
	// ACTOR PROPERTIES
	// =================================================================
protected:
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

	UPROPERTY(EditAnywhere, Category="Actor Properties")
	TObjectPtr<UAnimMontage> AttackAnimationMontage;
	

	
	// =================================================================
	// ACTOR INPUTS
	// =================================================================
protected:
	UPROPERTY(EditAnywhere, Category="Actor Inputs")
	TObjectPtr<UInputMappingContext> CharacterInputMappingContext;

	UPROPERTY(EditAnywhere, Category="Actor Inputs")
	TObjectPtr<UInputAction> MovementInputAction;

	UPROPERTY(EditAnywhere, Category="Actor Inputs")
	TObjectPtr<UInputAction> AttackInputAction;

	

	// =================================================================
	// UNREAL LIFECYCLE
	// =================================================================
public:
	ADSCatchPlayerCharacter();
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
protected:
	virtual void BeginPlay() override;


	
	// =================================================================
	// ACTION INPUT EVENTS
	// =================================================================
protected:
	void Move(const FInputActionValue& Value);
	void Attack(const FInputActionValue& Value);
	

	
	// =================================================================
	// MULTIPLAYER PROPERTIES
	// =================================================================
private:
	FCollisionQueryParams queryParams;
	
	UPROPERTY(ReplicatedUsing=OnRep_IsCatcher)
	bool IsCatcher { false };
	
public:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(Server, Reliable)
	void Server_SetIsCatcher(const bool value);
	void Server_SetIsCatcher_Implementation(const bool value);
	
	UFUNCTION()
	void OnRep_IsCatcher() const;
	
	UFUNCTION(Server, Reliable)
	void Server_PerformAttack();
	void Server_PerformAttack_Implementation();
	

	// =================================================================
	// ACTOR METHODS
	// =================================================================
public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE bool IsTheCatcher() const { return this->IsCatcher; }
	
	UFUNCTION()
	void SetMovementSpeed() const;

	UFUNCTION()
	void SetSkeletalMesh() const;

	UFUNCTION()
	void PerformAttackTracer() const;
};