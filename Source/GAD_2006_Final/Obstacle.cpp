// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle.h"

#include "BP_Character.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"




// Sets default values
AObstacle::AObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = SceneComponent;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(SceneComponent);


	StaticMesh->OnComponentHit.AddDynamic(this, &AObstacle::OnObstacleHit);


}


void AObstacle::OnObstacleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	

	ABP_Character* RunCharacter = Cast<ABP_Character>(OtherActor);

	if (RunCharacter)
	{
		RunCharacter->Death();

	}
}
