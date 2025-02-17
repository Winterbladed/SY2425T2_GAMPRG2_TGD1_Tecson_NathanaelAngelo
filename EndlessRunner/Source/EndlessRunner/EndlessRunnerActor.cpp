#include "EndlessRunnerActor.h"
#include "Components/StaticMeshComponent.h"

AEndlessRunnerActor::AEndlessRunnerActor()
{
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