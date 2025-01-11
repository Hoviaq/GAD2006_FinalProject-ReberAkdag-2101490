// Fill out your copyright notice in the Description page of Project Settings.


#include "Bp_GameModeBase.h"
#include "FloorTile.h"


void ABp_GameModeBase::BeginPlay()
{
	CreateInitialFloorTiles();
	;
}

void ABp_GameModeBase::CreateInitialFloorTiles()
{
	AFloorTile* Tile = AddFloorTile(false);
	if (Tile)
	{
		LaneSwitchValues.Add(Tile->LeftLane->GetComponentLocation().Y);
		LaneSwitchValues.Add(Tile->CenterLane->GetComponentLocation().Y);
		LaneSwitchValues.Add(Tile->RightLane->GetComponentLocation().Y);
	}

	AddFloorTile(false);
	AddFloorTile(false);

	for (int i = 0; i < NumInitialFloorTiles; i++)
	{
		AddFloorTile(true);
	}
}




AFloorTile* ABp_GameModeBase::AddFloorTile(const bool bSpawnItems)
{    
	UWorld* World = GetWorld();

	if (World)
	{
		AFloorTile* Tile = World->SpawnActor<AFloorTile>(FloorTileClass,NextSpawnPoint);

		if (Tile)
		{
			if (bSpawnItems)
			{
				Tile->SpawnItems();
			}

			NextSpawnPoint = Tile->GetAttachTransform();
		}

		return Tile;
		
	}

	return nullptr;
}

void ABp_GameModeBase::AddCoin()
{
	{
		TotalCoins += 1;
	}

}






