/**
 Nick Zayatz, Michele Burns, and Bel LaPointe
 11/1/15
 
 CSC-4360: Tanks
 TankCharacter.h
 **/

#pragma once

#include "GameFramework/Character.h"
#include "TankCharacter.generated.h"

UCLASS()
class TANKS_API ATankCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATankCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
    void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
    
  
    
    /** Sound to play each time we fire */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
    class USoundBase* FireSound;
    
    /** Projectile class to spawn */
    UPROPERTY(EditDefaultsOnly, Category=Projectile)
    TSubclassOf<class AProjectile> ProjectileClass;
    
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UserMade")
    bool MainMenuOn;
    
    //user input controls
    void RotateForward(float amount);
    void RotateRight(float amount);
    void MoveForward(float amount);
    void fire();
    void DisplayMainMenu();
    
    //control health and loss
    int health;
    void checkLoss();
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UserMade")
    bool lost;
    
    //rotators for top and bottom of tank
    FRotator currentDirection;
    FRotator topOfTank;
};
