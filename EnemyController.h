/**
 Nick Zayatz, Michele Burns, and Bel LaPointe
 11/1/15
 
 CSC-4360: Tanks
 EnemyController.h
 **/

#pragma once

#include "AIController.h"
#include "EnemyController.generated.h"

/**
 * 
 */
UCLASS()
class TANKS_API AEnemyController : public AAIController
{
	GENERATED_BODY()
	
public:
    AEnemyController(const class FObjectInitializer& PCIP);
    
    UPROPERTY(transient)
    UBlackboardComponent* BlackboardComp;
    
    UPROPERTY(transient)
    UBehaviorTreeComponent* BehaviorComp;
    
    //give enemies life
    virtual void Possess(class APawn *InPawn);
    
    //handle setting and searching for players
    void SetEnemy(class APawn *InPawn);
    
    UFUNCTION(BlueprintCallable, Category = Behavior)
    void SearchForEnemy();
    
protected:
    uint8 EnemyKeyID;
    uint8 EnemyLocationID;
	
	
};
