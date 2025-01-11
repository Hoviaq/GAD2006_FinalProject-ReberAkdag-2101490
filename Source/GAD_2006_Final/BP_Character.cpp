// Fill out your copyright notice in the Description page of Project Settings.
#include "BP_Character.h"
#include "Bp_GameModeBase.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"




// Sets default values
ABP_Character::ABP_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->TargetArmLength = 350.f;
	CameraArm->SocketOffset = FVector(0.f, 0.f, 100.f);
	CameraArm->bUsePawnControlRotation = true;
	CameraArm->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bUsePawnControlRotation = false;
	Camera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);
}



// Called when the game starts or when spawned
void ABP_Character::BeginPlay()
{
	Super::BeginPlay();

	RunGameMode = Cast<ABp_GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	check(RunGameMode);
	
	GetWorld()->GetTimerManager().SetTimer(SpeedIncreaseTimerHandle,this, &ABP_Character::IncreaseSpeed,1.0f,true);
}

// Called every frame
void ABP_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator ControlRot = GetControlRotation();
	ControlRot.Roll = 0.f;
	ControlRot.Pitch = 0.f;

	AddMovementInput(ControlRot.Vector());

	GetCharacterMovement()->MaxWalkSpeed = Speed;
}


void ABP_Character::ChangeLaneUpdate(float Value)
{
	FVector Location = GetCapsuleComponent()->GetComponentLocation();
	Location.Y = FMath::Lerp(RunGameMode->LaneSwitchValues[CurrentLane], RunGameMode->LaneSwitchValues[NextLane], Value);
	SetActorLocation(Location);
}

void ABP_Character::ChangeLaneFinished()
{
	CurrentLane = NextLane;
}




void ABP_Character::MoveLeft()
{
	NextLane = FMath::Clamp(CurrentLane - 1, 0, 2);
	ChangeLane();
}

void ABP_Character::MoveRight()
{
	NextLane = FMath::Clamp(CurrentLane + 1, 0, 2);
	ChangeLane();
}

void ABP_Character::MoveDown()
{
	static FVector Impulse = FVector(0, 0, MoveDownImpulse);
	GetCharacterMovement()->AddImpulse(Impulse, true);
}

void ABP_Character::AddCoin()
{
	RunGameMode->AddCoin();
}


void ABP_Character::OnDeath()
{
	if (RestartTimerHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(RestartTimerHandle);
	}


}


void ABP_Character::Death()
{
	
	
	if (!bIsDead)
	{
		const FVector Location = GetActorLocation();

		UWorld* World = GetWorld();


		if (World)
		{
			bIsDead = true;
			
			DisableInput(nullptr);


			if (DeathParticleSystem)
			{
				UGameplayStatics::SpawnEmitterAtLocation(World, DeathParticleSystem, Location);
				RunGameMode->DeadControl = true;

			}

			if (DeathSound)
			{
				UGameplayStatics::PlaySoundAtLocation(World, DeathSound, Location);
			}

			GetMesh()->SetVisibility(false);

			World->GetTimerManager().SetTimer(RestartTimerHandle, this, &ABP_Character::OnDeath, 1.f);
		}
	}

}

void ABP_Character::IncreaseSpeed()
{
	if (Speed >= MaxSpeed)
	{
		
		GetWorld()->GetTimerManager().ClearTimer(SpeedIncreaseTimerHandle);
		UE_LOG(LogTemp, Warning, TEXT("Hız maksimum seviyeye ulaştı: %f"), Speed);
		return;
	}

	
	Speed += 9.0f;
	UE_LOG(LogTemp, Warning, TEXT("Hız artırıldı: %f"), Speed);
}


// Called to bind functionality to input
void ABP_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABP_Character::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ABP_Character::StopJumping);

	PlayerInputComponent->BindAction("MoveLeft", IE_Pressed, this, &ABP_Character::MoveLeft);
	PlayerInputComponent->BindAction("MoveRight", IE_Pressed, this, &ABP_Character::MoveRight);
	PlayerInputComponent->BindAction("MoveDown", IE_Pressed, this, &ABP_Character::MoveDown);


}

