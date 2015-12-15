/**
 Nick Zayatz, Michele Burns, and Bel LaPointe
 11/1/15
 
 CSC-4360: Tanks
 Projectile.cpp
 **/

#include "Tanks.h"
#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "TankCharacter.h"
#include "Enemy.h"


// Sets default values
AProjectile::AProjectile()
{
    
    // Use a sphere as a simple collision representation
    CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
    CollisionComp->InitSphereRadius(5.0f);
    CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
    CollisionComp->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);		// set up a notification for when this component hits something blocking
    
    // Players can't walk on it
    CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
    CollisionComp->CanCharacterStepUpOn = ECB_No;
    
    // Set as root component
    RootComponent = CollisionComp;
    
    // Use a ProjectileMovementComponent to govern this projectile's movement
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
    ProjectileMovement->UpdatedComponent = CollisionComp;
    ProjectileMovement->InitialSpeed = 3000.f;
    ProjectileMovement->MaxSpeed = 3000.f;
    ProjectileMovement->bRotationFollowsVelocity = true;
    ProjectileMovement->bShouldBounce = true;
    
    //Die after 3 seconds by default
    InitialLifeSpan = 3.0f;
}


// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
    
}


// Called every frame
void AProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}


/**
 Action triggered when the the projectile hits another object on the screen
 
 - parameter otherActor: a pointer to the actor the projectile hit
 - parameter NormalImpulse: a vector showing the collision direction
 - parameter hit: the hit result
 - returns: void
 */
void AProjectile::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit){
    
    if(OtherActor){
        if (GEngine) {

            //if an enemy is hit, decrement its health and check if it died
            if(OtherActor->GetName().Contains(TEXT("BP_Enemy"))){
                AEnemy *thisEnemy = Cast<AEnemy>(OtherActor);
                if(thisEnemy->health != 0){
                    thisEnemy->health --;
                    thisEnemy->checkLoss();
                }
                Destroy();
            }
            
            //if a player is hit, decrement its health and check if they lost
            if(OtherActor->GetName().Contains(TEXT("TankCharacter"))){
                 ATankCharacter *MyTank = Cast<ATankCharacter>(UGameplayStatics::GetPlayerPawn(this,0));
                if(MyTank->health != 0){
                     MyTank->health --;
                    MyTank->checkLoss();
                }
                Destroy();
            }
               
        }
    }
    
}



