#include "EndlessRunnerTile.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "EndlessRunnerActor.h"
#include "Kismet/KismetMathLibrary.h"

AEndlessRunnerTile::AEndlessRunnerTile()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("Scene Component Root");
	SetRootComponent(SceneComponent);

	Arrow = CreateDefaultSubobject<UArrowComponent>("Arrow");
	Arrow->SetupAttachment(RootComponent);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("Box Collision");

	ObstacleSpawnArea = CreateDefaultSubobject<UBoxComponent>("Obstacle Spawn Area");
}

void AEndlessRunnerTile::BeginPlay()
{
	Super::BeginPlay();
	SpawnObstacle();
}

void AEndlessRunnerTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEndlessRunnerTile::OnExitTriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OnTileExited.Broadcast();
	GetWorldTimerManager().SetTimer(DestroyTimerHandle, this, &AEndlessRunnerTile::DestroyTile, 2.0f, false);
}

void AEndlessRunnerTile::SpawnObstacle()
{
	if (ObstacleTypes.Num() > 0)
	{
		FVector SpawnLocation = UKismetMathLibrary::RandomPointInBoundingBox(GetActorLocation(), ObstacleSpawnArea->GetScaledBoxExtent());
		int32 RandomIndex = FMath::RandRange(0, ObstacleTypes.Num() - 1);
		AEndlessRunnerActor* SpawnedObstacle = GetWorld()->SpawnActor<AEndlessRunnerActor>(ObstacleTypes[RandomIndex], SpawnLocation, FRotator::ZeroRotator);
		SpawnedObstacle->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	}
}

void AEndlessRunnerTile::DestroyTile()
{
	Destroy();
}