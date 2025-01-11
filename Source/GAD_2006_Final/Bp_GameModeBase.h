// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Bp_GameModeBase.generated.h"

class AFloorTile;
/**
 * 
 */
UCLASS()
class GAD_2006_FINAL_API ABp_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	int32 TotalCoins = 0;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	bool DeadControl = false;

	UPROPERTY(EditAnywhere, Category = "Config")
	TSubclassOf<AFloorTile> FloorTileClass;


	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	FTransform NextSpawnPoint;

	UPROPERTY(EditAnywhere, Category = "Config")
	int32 NumInitialFloorTiles =10;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	TArray<float> LaneSwitchValues; 

	UFUNCTION(BlueprintCallable)
	void CreateInitialFloorTiles();

	
	UFUNCTION(BlueprintCallable)
	AFloorTile* AddFloorTile(const bool bSpawnItems);

	UFUNCTION(BlueprintCallable)
	void AddCoin();




protected:
	virtual void BeginPlay() override;
};
