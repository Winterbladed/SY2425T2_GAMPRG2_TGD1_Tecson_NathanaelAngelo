// Fill out your copyright notice in the Description page of Project Settings.

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
	// Sets default values for this actor's properties
	AEnemySpawner();

	UPROPERTY(BlueprintAssignable, Category = "Event Dispatcher")
	FOnEnemySpawnedDeath OnEnemySpawnedDeath;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Enemies")
	TArray<TSubclassOf<class AEnemy>> BP_Enemy;

	void SpawnEnemy();

	UFUNCTION(BlueprintCallable)
	void SpawnEnemies();

	UFUNCTION()
	void AddDestroyedEnemyCount(int goldRewarded);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SetWaveParameters(TArray<TSubclassOf<class AEnemy>> enemySet, float spawnDelay, int32 spawnAmount, float spawnInterval, float hpScaling, float goldScaling);

	UFUNCTION()
	void StartWave();

private:

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Waypoints")
	TArray<AActor*> WaypointsHolder;	

	//per wave
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
