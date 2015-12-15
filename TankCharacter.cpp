/**
 Nick Zayatz, Michele Burns, and Bel LaPointe
 11/1/15
 
 CSC-4360: Tanks
 TankCharacter.cpp
 **/

#include "Tanks.h"
#include "TankCharacter.h"
#include "Projectile.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/InputSettings.h"


// Sets default values
ATankCharacter::ATankCharacter()
{
    
    topOfTank = FRotator(0, 0, 0);
    
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    
    currentDirection = FVector(0, -1, 0).Rotation();
    
    MainMenuOn=false;
    lost = false;
    health=25;
  
    
}


// Called when the game starts or when spawned
void ATankCharacter::BeginPlay()
{
    Super::BeginPlay();
    
}


// Called every frame
void ATankCharacter::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
    
    TArray<UActorComponent*> me = GetComponents();
    
    //loop through all components of the tank
    for(int i = 0; i < me.Num(); i++){
        UStaticMeshComponent *thisComp = Cast<UStaticMeshComponent>(me[i]);
        if (thisComp && thisComp->GetName() == "turret") {
            
            //if the turrent is found, set the direction the tank is facing to that direction
            topOfTank = thisComp->GetComponentRotation();
            
        }
    }
    
}


// Called to bind functionality to input
void ATankCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
    check(InputComponent);
    InputComponent->BindAxis("RotateForward", this, &ATankCharacter::RotateForward);
    InputComponent->BindAxis("RotateStrafe", this, &ATankCharacter::RotateRight);
    InputComponent->BindAxis("MoveForward", this, &ATankCharacter::MoveForward);
    InputComponent->BindAction("Fire", IE_Pressed, this, &ATankCharacter::fire);
    InputComponent->BindAction("Pause", IE_Pressed, this, &ATankCharacter::DisplayMainMenu);
}


/**
 Function called to toggle the boolean of whether or not the main menu is showing
 
 - parameter void:
 - returns: void
 */
void ATankCharacter::DisplayMainMenu()
{
    MainMenuOn = !MainMenuOn;
}


/**
 Function triggered when W or S is pressed to rotate the character forward or backward
 
 - parameter amount: the amount to rotate the tank
 - returns: void
 */
void ATankCharacter::RotateForward(float amount)
{
    
    //only permit movement if the user hasn't lost
    if (!lost) {
        if(Controller && amount)
        {
            FVector fwd = GetActorRightVector();
            
            TArray<UActorComponent*> me = GetComponents();
            
            //loop through all components of the tank
            for(int i = 0; i < me.Num(); i++){
                UStaticMeshComponent *thisComp = Cast<UStaticMeshComponent>(me[i]);
                if (thisComp) {
                    
                    //if the turrent is found, set the direction the tank is facing to that direction
                    if(thisComp->GetName() == "turret"){
                        fwd = thisComp->GetForwardVector();
                        fwd = fwd * (-1);
                        
                        if (amount < 0){
                            currentDirection = (thisComp->GetComponentRotation().Vector() * -1).Rotation();
                        }else if (amount > 0){
                            currentDirection = thisComp->GetComponentRotation();
                        }
                        
                        //if the rotation of the bottom is happening, rotate all of the bottom pieces
                    }else if (thisComp->GetName() == "body" || thisComp->GetName() == "sideL" ||thisComp->GetName() == "sideR" ||thisComp->GetName() == "treadL" ||thisComp->GetName() == "treadR") {
                        
                        int direction;
                        FRotator newRot = thisComp->GetComponentRotation();
                        
                        
                        //find the direction of the shortest rotation to get the bottom of the tank facing the correct angle
                        if ((currentDirection.Yaw - newRot.Yaw) > 0 && (currentDirection.Yaw - newRot.Yaw) < 360 - (currentDirection.Yaw - newRot.Yaw)){
                            direction = 5;
                        }else if ((currentDirection.Yaw - newRot.Yaw) > 0 && (currentDirection.Yaw - newRot.Yaw) > 360 - (currentDirection.Yaw - newRot.Yaw)) {
                            direction = -5;
                        }else if ((currentDirection.Yaw - newRot.Yaw) < 0 && FMath::Abs(currentDirection.Yaw - newRot.Yaw) < 360 - FMath::Abs(currentDirection.Yaw - newRot.Yaw)) {
                            direction = -5;
                        }else if ((currentDirection.Yaw - newRot.Yaw) < 0 && FMath::Abs(currentDirection.Yaw - newRot.Yaw) > 360 - FMath::Abs(currentDirection.Yaw - newRot.Yaw)) {
                            direction = 5;
                        }
                        
                        
                        //if the bottom of the tank is not already facing that direction, rotate it by the ABS(amount) in the calculated direction
                        if (!currentDirection.Equals(newRot, 5)){
                            thisComp->AddLocalRotation(FRotator(0, FMath::Abs(amount)*direction, 0));
                        }
                    }
                    
                }
            }
        }
    }
}


/**
 Function triggered when A or D is pressed to rotate the character right or left
 
 - parameter amount: the amount to rotate the tank
 - returns: void
 */
void ATankCharacter::RotateRight(float amount)
{
    
    //only permit movement if the user hasn't lost
    if (!lost) {
        if(Controller && amount)
        {
            FVector fwd = GetActorRightVector();
            
            TArray<UActorComponent*> me = GetComponents();
            
            //loop through all components of the tank
            for(int i = 0; i < me.Num(); i++){
                UStaticMeshComponent *thisComp = Cast<UStaticMeshComponent>(me[i]);
                if (thisComp) {
                    
                    //if the turrent is found, set the direction the tank is facing to that direction
                    if(thisComp->GetName() == "turret"){
                        fwd = thisComp->GetForwardVector();
                        fwd = fwd * (-1);
                        
                        if (amount < 0){
                            currentDirection = (thisComp->GetComponentRotation().Vector() * -1).Rotation() + FRotator(0, 90, 0);
                        }else if (amount > 0){
                            currentDirection = thisComp->GetComponentRotation() + FRotator(0, 90, 0);
                        }
                        
                        //if the rotation of the bottom is happening, rotate all of the bottom pieces
                    }else if (thisComp->GetName() == "body" || thisComp->GetName() == "sideL" ||thisComp->GetName() == "sideR" ||thisComp->GetName() == "treadL" ||thisComp->GetName() == "treadR") {
                        
                        int direction;
                        FRotator newRot = thisComp->GetComponentRotation();
                        
                        
                        //find the direction of the shortest rotation to get the bottom of the tank facing the correct angle
                        if ((currentDirection.Yaw - newRot.Yaw) > 0 && (currentDirection.Yaw - newRot.Yaw) < 360 - (currentDirection.Yaw - newRot.Yaw)){
                            direction = 5;
                        }else if ((currentDirection.Yaw - newRot.Yaw) > 0 && (currentDirection.Yaw - newRot.Yaw) > 360 - (currentDirection.Yaw - newRot.Yaw)) {
                            direction = -5;
                        }else if ((currentDirection.Yaw - newRot.Yaw) < 0 && FMath::Abs(currentDirection.Yaw - newRot.Yaw) < 360 - FMath::Abs(currentDirection.Yaw - newRot.Yaw)) {
                            direction = -5;
                        }else if ((currentDirection.Yaw - newRot.Yaw) < 0 && FMath::Abs(currentDirection.Yaw - newRot.Yaw) > 360 - FMath::Abs(currentDirection.Yaw - newRot.Yaw)) {
                            direction = 5;
                        }
                        
                        
                        //if the bottom of the tank is not already facing that direction, rotate it by the ABS(amount) in the calculated direction
                        if (!currentDirection.Equals(newRot, 5)){
                            thisComp->AddLocalRotation(FRotator(0, FMath::Abs(amount)*direction, 0));
                        }
                    }
                    
                }
            }
        }
    }
}


/**
 Function triggered when Space or Left Shift is pressed to move the character forward or backward
 
 - parameter amount: the amount to rotate the tank
 - returns: void
 */
void ATankCharacter::MoveForward(float amount)
{
    
    //only permit movement if the user hasn't lost
    if (!lost) {
        if(Controller && amount)
        {
            FVector fwd = GetActorRightVector();
            
            TArray<UActorComponent*> me = GetComponents();
            
            //find the direction of the body to move the tank in
            for(int i = 0; i < me.Num(); i++){
                UStaticMeshComponent *thisComp = Cast<UStaticMeshComponent>(me[i]);
                if (thisComp) {
                    
                    //if the body is found, get its direction to move the tank forward or backward in that direction
                    if(thisComp->GetName() == "body"){
                        fwd = thisComp->GetRightVector();
                    }
                }
            }
            AddMovementInput (fwd, amount);
        }
    }
}


/**
 Function triggered when the space bar is pressed to fire a projectile
 
 - parameter void:
 - returns: void
 */
void ATankCharacter::fire(){
    
    //only permit firing if the user hasn't lost
    if (!lost) {
        
        //get initial values of the start location, velocity, and rotation of the bullet
        FVector start = GetActorLocation();
        FVector vel = GetActorForwardVector();
        FRotator rot = GetActorRotation();
        
        TArray<UActorComponent*> me = GetComponents();
        
        //loop through all parts of the tank
        for(int i = 0; i < me.Num(); i++){
            UStaticMeshComponent *thisComp = Cast<UStaticMeshComponent>(me[i]);
            
            if (GEngine && thisComp) {
                
                //if the barrel is found, set starting position and velocity
                if(thisComp->GetName() == "barrel"){
                    vel = thisComp->GetRightVector();
                    rot = thisComp->GetComponentRotation();
                    start = thisComp->GetComponentLocation() + rot.RotateVector(FVector(OFFSET_BARREL_X, OFFSET_BARREL_Y, OFFSET_BARREL_Z));
                }
            }
        }
        
        //play the fire sound
        if(FireSound !=NULL)
        {
            UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
        }
        
        // try and fire a projectile
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
    }
}


/**
 Check to see if the user has lost
 
 - parameter void:
 - returns: void
 */
void ATankCharacter::checkLoss(){
    if (health == 0) {
        lost = true;
    }
}


