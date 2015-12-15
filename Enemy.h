/**
 Nick Zayatz, Michele Burns, and Bel LaPointe
 11/1/15
 
 CSC-4360: Tanks
 Enemy.h
 **/

#pragma once

#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class TANKS_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy(const class FObjectInitializer&);
    
    UPROPERTY(EditAnywhere, Category = Behavior)
    class UBehaviorTree* EnemyBehavior;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

    UFUNCTION(BlueprintCallable, Category = "UserMade")
    void fire(float angle);
    
    /** Projectile class to spawn */
    UPROPERTY(EditDefaultsOnly, Category=Projectile)
    TSubclassOf<class AProjectile> ProjectileClass;
    
    
    //handle firing
    FTimerHandle handleClock;
    void readyToFire();
    bool canFire = true;
    
    //handle health and losses
    int health;
    void checkLoss();
	
};
