#include "EnemySpawner.h"
#include "Enemy.h"

AEnemySpawner::AEnemySpawner()
{
	PrimaryActorTick.bCanEverTick = true;
	CurrentSpawnedEnemiesCount = 0;
	SpawnDelay = 3.0f;
}

void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemySpawner::SpawnEnemy()
{
	if (BP_Enemy.Num() != 0)
	{
		FVector SpawnLocation = GetActorLocation();
		FRotator SpawnRotation = GetActorRotation();
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		SpawnParameters.Owner = this;
		int32 RandInt = FMath::RandRange(0, BP_Enemy.Num() - 1);
		AEnemy* Enemy = GetWorld()->SpawnActor<AEnemy>(BP_Enemy[RandInt], SpawnLocation, SpawnRotation, SpawnParameters);
		Enemy->ScaleHealthPoints(HpScaling);
		Enemy->ScaleGoldReward(GoldScaling);
		Enemy->OnEnemyDestroyed.AddDynamic(this, &AEnemySpawner::AddDestroyedEnemyCount);
		if (WaypointsHolder.Num() != 0)
		{			
			Enemy->SetWayPoints(WaypointsHolder);
			Enemy->MoveToWayPoints();
		}
		CurrentSpawnedEnemiesCount++;
		if (CurrentSpawnedEnemiesCount < SpawnAmount)
		{
			SpawnEnemies();
		}		
	}
}

void AEnemySpawner::SpawnEnemies()
{	
	GetWorld()->GetTimerManager().SetTimer(SpawnIntervalHandler, this, &AEnemySpawner::SpawnEnemy, SpawnInterval, false);
}

void AEnemySpawner::StartWave()
{
	GetWorld()->GetTimerManager().SetTimer(SpawnDelayHandler, this, &AEnemySpawner::SpawnEnemy, SpawnDelay, false);
	CurrentSpawnedEnemiesCount = 0;
}

void AEnemySpawner::AddDestroyedEnemyCount(int goldRewarded)
{
	UE_LOG(LogTemp, Warning, TEXT("Added Destroyed"));
	OnEnemySpawnedDeath.Broadcast(goldRewarded);	
}

void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemySpawner::SetWaveParameters(TArray<TSubclassOf<class AEnemy>> enemySet, float spawnDelay, int32 spawnAmount, float spawnInterval, float hpScaling, float goldScaling)
{
	SpawnDelay = spawnDelay;
	SpawnAmount = spawnAmount;
	SpawnInterval = spawnInterval;
	HpScaling = hpScaling;
	GoldScaling = goldScaling;
	BP_Enemy.Empty();
	for (TSubclassOf<AEnemy> enemyClass : enemySet)
	{
		if (enemyClass.Get())
		{
			BP_Enemy.Add(enemyClass.Get());
			UE_LOG(LogTemp, Warning, TEXT("BP ENEMY ADDED"));
		}
	}
}