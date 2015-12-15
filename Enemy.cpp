/**
 Nick Zayatz, Michele Burns, and Bel LaPointe
 11/1/15
 
 CSC-4360: Tanks
 Enemy.cpp
 **/

#include "Tanks.h"
#include "Enemy.h"
#include "EnemyController.h"
#include "Projectile.h"


// Sets default values
AEnemy::AEnemy(const class FObjectInitializer&)
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    health = 15;
    PrimaryActorTick.bCanEverTick = true;
    
    AIControllerClass = AEnemyController::StaticClass();
    
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
    Super::BeginPlay();
    
}

// Called every frame
void AEnemy::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
    
}


/**
 Function triggered when the space bar is pressed to fire a projectile
 
 - parameter angle: the angle of the barrel to fire the bullet in
 - returns: void
 */
void AEnemy::fire(float angle){
    
    //get initial values of the start location, velocity, and rotation of the bullet
    FVector start = GetActorLocation();
    FVector vel = GetActorForwardVector();
    FRotator rot = GetActorRotation();
    
    TArray<UActorComponent*> me = GetComponents();
    
    //search for the barrel to set the bullets velocity, direction, and start point
    for(int i = 0; i < me.Num(); i++){
        UStaticMeshComponent *thisComp = Cast<UStaticMeshComponent>(me[i]);
        if (GEngine && thisComp) {
            
            //if the barrel is found, give the bullet the position, rotation, and direction vector of the barrel
            if(thisComp->GetName() == "barrel"){
                thisComp->SetRelativeRotation(FRotator(0, 0, angle));
                vel = thisComp->GetRightVector();
                rot = thisComp->GetComponentRotation();
                start = thisComp->GetComponentLocation() + rot.RotateVector(FVector(OFFSET_BARREL_X, OFFSET_BARREL_Y, OFFSET_BARREL_Z));
            }
        }
    }
    
    //only allow the computer to fire once per second
    if (canFire) {
        
        //try and fire a projectile
        if (ProjectileClass != NULL)
        {
            
            //convert velocity to a rotator
            const FRotator SpawnRotation = vel.Rotation();
            
            UWorld* const World = GetWorld();
            if (World != NULL)
            {
                // spawn the projectile at the muzzle
                World->SpawnActor<AProjectile>(ProjectileClass, start, SpawnRotation);
            }
        }
        
        //start timer where the computer cannot fire
        GetWorld()->GetTimerManager().SetTimer(handleClock, this, &AEnemy::readyToFire, 1.0f, true);
        canFire = false;
    }
}


/**
 Function to make the computer ready to fire
 
 - parameter void:
 - returns: void
*/
void AEnemy::readyToFire(){
    
    //clear timer and make computer ready to fire
    GetWorld()->GetTimerManager().ClearTimer(handleClock);
    canFire = true;
}


/**
 Function to check whether or not the computer has died.
 
 - parameter void:
 - returns: void
*/
void AEnemy::checkLoss(){
    if (health == 0) {
        Destroy();
    }
}

