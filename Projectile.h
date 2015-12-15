/**
 Nick Zayatz, Michele Burns, and Bel LaPointe
 11/1/15
 
 CSC-4360: Tanks
 Projectile.h
 **/

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TANKS_API AProjectile : public AActor
{
    GENERATED_BODY()
    
    /** Sphere collision component */
    UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
    class USphereComponent* CollisionComp;
    
    /** Projectile movement component */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
    class UProjectileMovementComponent* ProjectileMovement;
	
public:	
	// Sets default values for this actor's properties
	AProjectile();
    
    /** Pointer to orange material used on active blocks */
    UPROPERTY()
    class UMaterialInstance* ProjectileMaterial;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
    
    //check for hits
    UFUNCTION()
    void OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
public:

    /** Returns CollisionComp subobject **/
    FORCEINLINE class USphereComponent* GetCollisionComp() const { return CollisionComp; }
    /** Returns ProjectileMovement subobject **/
    FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
};
