// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BP_Character.generated.h"

UCLASS()
class GAD_2006_FINAL_API ABP_Character : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	UPROPERTY(VisibleInstanceOnly)
	class ABp_GameModeBase* RunGameMode;

public:

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	float Speed= 1500;

	// Maksimum hız
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	float MaxSpeed= 3000;

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Assets")
	class UParticleSystem* DeathParticleSystem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Assets")
	class USoundBase* DeathSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveDownImpulse = -1000.f;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	int32 CurrentLane = 1;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	int32 NextLane = 0;
	UFUNCTION(BlueprintImplementableEvent, Category = "Lane")
	void ChangeLane();

	UFUNCTION(BlueprintCallable, Category = "Lane")
	void ChangeLaneUpdate(float Value);

	UFUNCTION(BlueprintCallable, Category = "Lane")
	void ChangeLaneFinished();

	UFUNCTION(BlueprintCallable)
	void Death();

	void IncreaseSpeed();
	// Sets default values for this character's properties
	ABP_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	UFUNCTION()
	void OnDeath();
	
	UFUNCTION()
	void MoveLeft();

	UFUNCTION()
	void MoveRight();

	UFUNCTION()
	void MoveDown();

	UPROPERTY()
	FTimerHandle RestartTimerHandle;


	UPROPERTY()
	bool bIsDead = false;

	FTimerHandle SpeedIncreaseTimerHandle;

	


public:

	UFUNCTION()
	void AddCoin();

	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
