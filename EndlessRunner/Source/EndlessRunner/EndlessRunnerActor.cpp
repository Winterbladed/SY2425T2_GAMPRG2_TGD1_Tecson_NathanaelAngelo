#include "EndlessRunnerActor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AEndlessRunnerActor::AEndlessRunnerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
}

// void Start
void AEndlessRunnerActor::BeginPlay()
{
	Super::BeginPlay();
	
	//Randomize Vector Scale
	StaticMesh->SetWorldScale3D(FMath::VRand());

	CurrentHealth = MaxHealth;
}

// void Update
void AEndlessRunnerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}