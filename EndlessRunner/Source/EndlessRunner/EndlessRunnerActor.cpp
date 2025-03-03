#include "EndlessRunnerActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "RunCharacter.h"

AEndlessRunnerActor::AEndlessRunnerActor()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
}

void AEndlessRunnerActor::BeginPlay()
{
	Super::BeginPlay();
	
	StaticMesh->SetWorldScale3D(FMath::VRand());

	CurrentHealth = MaxHealth;
}

void AEndlessRunnerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEndlessRunnerActor::OnTrigger()
{

}

void AEndlessRunnerActor::HandleCollision(AActor* OverlappedActor, AActor* OtherActor)
{
	ARunCharacter* Character = Cast<ARunCharacter>(OtherActor);
	if (Character)
	{
		OnTrigger(); // Call Blueprint event
	}
}