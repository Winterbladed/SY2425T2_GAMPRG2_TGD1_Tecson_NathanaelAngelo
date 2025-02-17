#include "EndlessRunnerTile.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"

AEndlessRunnerTile::AEndlessRunnerTile()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("Scene Component");
	SetRootComponent(SceneComponent);

	Arrow = CreateDefaultSubobject<UArrowComponent>("Arrow");
	Arrow->SetupAttachment(RootComponent);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("Box Collision");
}

// void Start
void AEndlessRunnerTile::BeginPlay()
{
	Super::BeginPlay();
}

// void Update
void AEndlessRunnerTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEndlessRunnerTile::OnExitTriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OnTileExited.Broadcast();
	GetWorldTimerManager().SetTimer(DestroyTimerHandle, this, &AEndlessRunnerTile::DestroyTile, 2.0f, false);
}

void AEndlessRunnerTile::DestroyTile()
{
	Destroy();
}