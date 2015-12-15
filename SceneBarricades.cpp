/**
 Nick Zayatz, Michele Burns, and Bel LaPointe
 11/1/15
 
 CSC-4360: Tanks
 SceneBarricades.cpp
 **/

#include "Tanks.h"
#include "SceneBarricades.h"


// Sets default values
ASceneBarricades::ASceneBarricades()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

   struct FConstructorStatics
   {
      ConstructorHelpers::FObjectFinderOptional<UStaticMesh> barricadeShape;
      ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> barricadeMaterial;
      FConstructorStatics()
         : barricadeShape(TEXT("/Game/MapProps/blockade.blockade"))
         , barricadeMaterial(TEXT("Material'/Game/MapProps/cementLight.cementLight'"))
      {
      }
   };
   static FConstructorStatics ConstructorStatics;

   // Create dummy root scene component
   //DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
   //RootComponent = DummyRoot;

   ItemBasicMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("item_shape"));
   // Create random mesh component
   ItemBasicMesh->SetStaticMesh(ConstructorStatics.barricadeShape.Get());
   ItemBasicMesh->SetMaterial(0, ConstructorStatics.barricadeMaterial.Get());
   ItemBasicMesh->SetRelativeScale3D(FVector(0.2f,0.2f,0.2f));
   ItemBasicMesh->SetRelativeLocation(FVector(0.f,0.f,0.f));
   ItemBasicMesh->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
   //ItemBasicMesh->AttachTo(DummyRoot);

   health = 3;

   this->OnActorHit.AddDynamic(this, &ASceneBarricades::onHit);
}

// Called when the game starts or when spawned
void ASceneBarricades::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASceneBarricades::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ASceneBarricades::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void ASceneBarricades::onHit(AActor *Self, AActor *neighbor, FVector NormalImpulse, const FHitResult &Hit)
{
   //GEngine->AddOnScreenDebugMessage(5,1.f,FColor::White,FString("Barricade hit by ")+neighbor->GetName());
   if( (neighbor->GetName()).Contains("Projectile", ESearchCase::IgnoreCase, ESearchDir::FromStart) ){
      health--;
      if(health<=0)
         this->K2_DestroyActor();
   }
}

