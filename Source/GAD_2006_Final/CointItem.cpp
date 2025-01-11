// Fill out your copyright notice in the Description page of Project Settings.


#include "CointItem.h"
#include "Components/SphereComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BP_Character.h"

// Sets default values
ACointItem::ACointItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	SphereCollider->SetupAttachment(SceneComponent);
	SphereCollider->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));

	CoinMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CoinMesh"));
	CoinMesh->SetupAttachment(SphereCollider);
	CoinMesh->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));

	RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovement"));
	RotatingMovement->RotationRate = FRotator(0, 180, 0);

}

// Called when the game starts or when spawned
void ACointItem::BeginPlay()
{
	Super::BeginPlay();

	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &ACointItem::OnSphereOverlap);
}


void ACointItem::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABP_Character* RunCharacter = Cast<ABP_Character>(OtherActor);

	if (OverlapSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), OverlapSound, GetActorLocation());
	}

	RunCharacter->AddCoin();

	Destroy();
}

// Called every frame


