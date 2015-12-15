/**
 Nick Zayatz, Michele Burns, and Bel LaPointe
 11/1/15
 
 CSC-4360: Tanks
 loadBarricades.h
 **/

#pragma once

#include "Components/SceneComponent.h"
#include "loadBarricades.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKS_API UloadBarricades : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UloadBarricades();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

		
	
};
