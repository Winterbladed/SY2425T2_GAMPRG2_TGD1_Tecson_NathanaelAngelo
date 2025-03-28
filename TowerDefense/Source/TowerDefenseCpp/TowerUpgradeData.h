// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TowerUpgradeData.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSECPP_API UTowerUpgradeData : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower Data")
	UStaticMesh* Base;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower Data")
	UStaticMesh* Barrel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower Data")
	int UpgradeCost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower Data")
	int SellCost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower Data")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower Data")
	float FireRate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower Data")
	float SpecialValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower Data")
	float Range = 800;
};
