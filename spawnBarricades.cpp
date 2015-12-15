/**
 Nick Zayatz, Michele Burns, and Bel LaPointe
 11/1/15
 
 CSC-4360: Tanks
 spawnBarricades.cpp
 **/

#include "Tanks.h"
#include "spawnBarricades.h"
#include "SceneBarricades.h"


// Sets default values
AspawnBarricades::AspawnBarricades()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AspawnBarricades::BeginPlay()
{
	Super::BeginPlay();
	/*
   ASceneBarricades* newItem;
   newItem = GetWorld()->SpawnActor<ASceneBarricades>( 
      FVector(-450, -1030, 102),
      FRotator(0,135,0) );
      //FRotator(0,0,135));
   newItem = GetWorld()->SpawnActor<ASceneBarricades>( 
      FVector(-890, -1030, 102),
      FRotator(0,45,0) );
      //FRotator(0,0,45));
   newItem = GetWorld()->SpawnActor<ASceneBarricades>( 
      FVector(-890, -610, 102),
      FRotator(0,-45,0) );
      //FRotator(0,0,-45));
   newItem = GetWorld()->SpawnActor<ASceneBarricades>( 
      FVector(-470, -590, 102),
      FRotator(0,-135,0) );
      //FRotator(0,0,-135));
      */
}

// Called every frame
void AspawnBarricades::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

