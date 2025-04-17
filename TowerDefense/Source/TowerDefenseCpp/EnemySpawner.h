#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemySpawnedDeath, int, KillReward);

UCLASS()
class TOWERDEFENSECPP_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnemySpawner();
	UPROPERTY(BlueprintAssignable, Category = "Event Dispatcher")
	FOnEnemySpawnedDeath OnEnemySpawnedDeath;

protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Enemies")
	TArray<TSubclassOf<class AEnemy>> BP_Enemy;
	void SpawnEnemy();
	UFUNCTION(BlueprintCallable)
	void SpawnEnemies();
	UFUNCTION()
	void AddDestroyedEnemyCount(int goldRewarded);

public:	
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void SetWaveParameters(TArray<TSubclassOf<class AEnemy>> enemySet, float spawnDelay, int32 spawnAmount, float spawnInterval, float hpScaling, float goldScaling);
	UFUNCTION()
	void StartWave();

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Waypoints")
	TArray<AActor*> WaypointsHolder;
	int32 CurrentSpawnedEnemiesCount;
	int32 CurrentDestroyedEnemiesCount;
	int32 SpawnAmount; 
	float SpawnDelay;
	float SpawnInterval;
	float HpScaling;
	float GoldScaling;
	FTimerHandle SpawnIntervalHandler;
	FTimerHandle SpawnDelayHandler;
};