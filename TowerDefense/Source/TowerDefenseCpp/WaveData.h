#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Enemy.h"
#include "WaveData.generated.h"

UCLASS()
class TOWERDEFENSECPP_API UWaveData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave Data")
	float SpawnInterval;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave Data")
	int WaveGoldReward;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy Data")
	TArray<TSubclassOf<class AEnemy>> BP_Enemy;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy Data ")
	int SpawnAmount;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy Data ")
	float HpScaling = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy Data ")
	float GoldRewardScaling = 1.f;
};