// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "FloorTile.generated.h"

class AObstacle;
class UArrowComponent;
class UStaticMeshComponent;
class USceneComponent;
class UBoxComponent;
class ACointItem;

UCLASS()
class GAD_2006_FINAL_API AFloorTile : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
	TSubclassOf<AObstacle> SmallObstacleClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
	TSubclassOf<AObstacle> BigObstacleClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
	TSubclassOf<ACointItem> CointItemClass;



	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* FloorMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* AttachPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* CenterLane;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* RightLane;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* LeftLane;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* SecondCenterLane;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* SecondRightLane;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* SecondLeftLane;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* ThirdCenterLane;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* ThirdRightLane;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* ThirdLeftLane;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* FourthCenterLane;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* FourthRightLane;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* FourthLeftLane;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* FloorTriggerBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
		float SpawnPercent1 = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
	float SpawnPercent2 = 0.3f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
	float SpawnPercent3 = 0.5f;

	UFUNCTION(BlueprintCallable)
	void SpawnItems();


	// Sets default values for this actor's properties
	AFloorTile();

	FORCEINLINE const FTransform& GetAttachTransform() const
	{
		return AttachPoint->GetComponentTransform();
	}


	

protected:

	UPROPERTY(VisibleInstanceOnly)

	class ABp_GameModeBase* RunGameMode;

	UPROPERTY()
	FTimerHandle DestroyHandle;


	UFUNCTION()
	void OnTriggerBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	void DestroyFloorTile();


	UFUNCTION()
	void SpawnLaneItem(UArrowComponent* Lane, int32& NumBigs);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	

};
