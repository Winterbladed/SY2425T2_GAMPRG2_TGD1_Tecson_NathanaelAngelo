// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WaveData.h"
#include "TowerDefenseCppGameModeBase.generated.h"

UCLASS()
class TOWERDEFENSECPP_API ATowerDefenseCppGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATowerDefenseCppGameModeBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TD Game Mode Stats")
	int32 PlayerHp;

	UPROPERTY(BlueprintReadOnly, Category = "TD Game Mode Stats")
	int32 CurrentWaveItr;

	UPROPERTY(BlueprintReadOnly, Category = "TD Game Mode Stats")
	int32 TotalWaveCount;

	UPROPERTY(BlueprintReadOnly, Category = "Player Stats")
	int PlayerGold;

	UFUNCTION(BlueprintCallable)
	void DeductGold(int amount);

	UFUNCTION(BlueprintCallable)
	void AddGold(int amount);

	UFUNCTION(BlueprintCallable)
	void Win();

	bool IsWon;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnCoreHit();

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Waves")
	TArray<UWaveData*> WaveData;

	UFUNCTION()
	void StartNewWave();

	UFUNCTION()
	void UpdateTotalEnemyDestroyed(int goldReward);

private:

	int32 TotalEnemiesSpawned;
	int32 TotalEnemiesDestroyedInWave;

	UPROPERTY(EditAnywhere, Category = "Waves", meta = (AllowPrivateAccess = "true"))
	float WaveDelay; // spawn delay

	TArray <AActor* > PlayerCores;
	TArray <AActor* > EnemySpawners;

	void ReduceHp();

	void QuitGame();
};