/**
 Nick Zayatz, Michele Burns, and Bel LaPointe
 11/1/15
 
 CSC-4360: Tanks
 SceneBarricades.h
 **/

#pragma once

#include "GameFramework/Pawn.h"
#include "SceneBarricades.generated.h"

UCLASS()
class TANKS_API ASceneBarricades : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASceneBarricades();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	int health;
	void onHit(AActor *Self, AActor *neighbor, FVector NormalImpulse, const FHitResult &Hit);

	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ItemBasicMesh;

   UPROPERTY(VisibleDefaultsOnly)
   class USphereComponent* CollisionComp;

};
