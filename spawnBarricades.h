/**
 Nick Zayatz, Michele Burns, and Bel LaPointe
 11/1/15
 
 CSC-4360: Tanks
 spawnBarricades.h
 **/

#pragma once

#include "GameFramework/Actor.h"
#include "spawnBarricades.generated.h"

UCLASS()
class TANKS_API AspawnBarricades : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AspawnBarricades();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
