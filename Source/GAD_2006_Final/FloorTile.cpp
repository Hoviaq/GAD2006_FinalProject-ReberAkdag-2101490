// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorTile.h"
#include "Bp_GameModeBase.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "BP_Character.h"
#include "Obstacle.h"
#include "CointItem.h"



// Sets default values
AFloorTile::AFloorTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = SceneComponent;

	FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorMesh"));
	FloorMesh->SetupAttachment(SceneComponent);

	AttachPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Attach Point"));
	AttachPoint->SetupAttachment(SceneComponent);

	CenterLane = CreateDefaultSubobject<UArrowComponent>(TEXT("Center Lane"));
	CenterLane->SetupAttachment(SceneComponent);

	RightLane = CreateDefaultSubobject<UArrowComponent>(TEXT("Right Lane"));
	RightLane->SetupAttachment(SceneComponent);

	LeftLane = CreateDefaultSubobject<UArrowComponent>(TEXT("Left Lane"));
	LeftLane->SetupAttachment(SceneComponent);

	SecondCenterLane = CreateDefaultSubobject<UArrowComponent>(TEXT("Second Center Lane"));
	SecondCenterLane->SetupAttachment(SceneComponent);

	SecondRightLane = CreateDefaultSubobject<UArrowComponent>(TEXT("Second Right Lane"));
	SecondRightLane->SetupAttachment(SceneComponent);

	SecondLeftLane = CreateDefaultSubobject<UArrowComponent>(TEXT("Second Left Lane"));
	SecondLeftLane->SetupAttachment(SceneComponent);

	ThirdCenterLane = CreateDefaultSubobject<UArrowComponent>(TEXT("Third Center Lane"));
	ThirdCenterLane->SetupAttachment(SceneComponent);

	ThirdRightLane = CreateDefaultSubobject<UArrowComponent>(TEXT("Third Right Lane"));
	ThirdRightLane->SetupAttachment(SceneComponent);

	ThirdLeftLane = CreateDefaultSubobject<UArrowComponent>(TEXT("Third Left Lane"));
	ThirdLeftLane->SetupAttachment(SceneComponent);

	FourthCenterLane = CreateDefaultSubobject<UArrowComponent>(TEXT("Fourth Center Lane"));
	FourthCenterLane->SetupAttachment(SceneComponent);

	FourthRightLane = CreateDefaultSubobject<UArrowComponent>(TEXT("Fourth Right Lane"));
	FourthRightLane->SetupAttachment(SceneComponent);

	FourthLeftLane = CreateDefaultSubobject<UArrowComponent>(TEXT("Fourth Left Lane"));
	FourthLeftLane->SetupAttachment(SceneComponent);


	FloorTriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("FloorTriggerBox"));
	FloorTriggerBox->SetupAttachment(SceneComponent);
	FloorTriggerBox->SetBoxExtent(FVector(32.f, 500.f, 200.f));
	FloorTriggerBox->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));

}

// Called when the game starts or when spawned
void AFloorTile::BeginPlay()
{
	RunGameMode = Cast<ABp_GameModeBase>(UGameplayStatics:: GetGameMode(GetWorld()));
	Super::BeginPlay();
	check(RunGameMode);

	FloorTriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AFloorTile::OnTriggerBoxOverlap);

}






void AFloorTile::OnTriggerBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABP_Character* BP_Character = Cast<ABP_Character>(OtherActor);
	if (BP_Character)
	{
		RunGameMode->AddFloorTile(true);

		GetWorldTimerManager().SetTimer(DestroyHandle, this, &AFloorTile::DestroyFloorTile, 2.f, false);

		
	}

	

}

void AFloorTile::SpawnItems()
{

	if (IsValid(SmallObstacleClass) && IsValid(BigObstacleClass) && IsValid(CointItemClass))
	{
		int32 NumBigs = 0;

		SpawnLaneItem(CenterLane,  NumBigs);
		SpawnLaneItem(LeftLane, NumBigs);
		SpawnLaneItem(RightLane, NumBigs);
		SpawnLaneItem(SecondCenterLane,NumBigs);
		SpawnLaneItem(SecondLeftLane, NumBigs);
		SpawnLaneItem(SecondRightLane, NumBigs);
		SpawnLaneItem(ThirdCenterLane, NumBigs);
		SpawnLaneItem(ThirdLeftLane, NumBigs);
		SpawnLaneItem(ThirdRightLane, NumBigs);
		SpawnLaneItem(FourthCenterLane, NumBigs);
		SpawnLaneItem(FourthLeftLane, NumBigs);
		SpawnLaneItem(FourthRightLane, NumBigs);
	}
	

}



void AFloorTile::SpawnLaneItem(UArrowComponent* Lane, int32& NumBigs)
{
	
	const float RandVal = FMath::FRandRange(0.f, 1.f);
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	const FTransform& SpawnLocation = Lane->GetComponentTransform();

	if (UKismetMathLibrary::InRange_FloatFloat(RandVal, SpawnPercent1, SpawnPercent2, true, true))
	{
		AObstacle* Obstacle = GetWorld()->SpawnActor<AObstacle>(SmallObstacleClass, SpawnLocation, SpawnParameters);
	}
	else if (UKismetMathLibrary::InRange_FloatFloat(RandVal, SpawnPercent2, SpawnPercent3, true, true))
	{
		if (NumBigs <= 2)
		{
			AObstacle* Obstacle = GetWorld()->SpawnActor<AObstacle>(BigObstacleClass, SpawnLocation, SpawnParameters);

			if (Obstacle)
			{
				NumBigs += 1;
			}

			
		}
		else
		{
			AObstacle* Obstacle = GetWorld()->SpawnActor<AObstacle>(SmallObstacleClass, SpawnLocation, SpawnParameters);
		
		}
	}

	else if (UKismetMathLibrary::InRange_FloatFloat(RandVal, SpawnPercent3, 1.f, true, true))
	{
		ACointItem* Obstacle = GetWorld()->SpawnActor<ACointItem>(CointItemClass, SpawnLocation, SpawnParameters);
	}
}


void AFloorTile::DestroyFloorTile()
{
	if (DestroyHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(DestroyHandle);
	}

	this->Destroy();
}







