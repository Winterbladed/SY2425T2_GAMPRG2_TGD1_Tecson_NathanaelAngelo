#include "PlayerCore.h"
#include "Enemy.h"

APlayerCore::APlayerCore()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APlayerCore::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerCore::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCore::TakeDamage()
{
	OnPlayerCoreHit.Broadcast();
}