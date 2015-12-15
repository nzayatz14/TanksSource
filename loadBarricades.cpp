/**
 Nick Zayatz, Michele Burns, and Bel LaPointe
 11/1/15
 
 CSC-4360: Tanks
 loadBarricades.cpp
 **/

#include "Tanks.h"
#include "loadBarricades.h"


// Sets default values for this component's properties
UloadBarricades::UloadBarricades()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UloadBarricades::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UloadBarricades::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

