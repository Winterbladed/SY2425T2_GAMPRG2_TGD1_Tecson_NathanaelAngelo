#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TowerUpgradeData.h"
#include "Tower.generated.h"

UCLASS()
class TOWERDEFENSECPP_API ATower : public APawn
{
	GENERATED_BODY()

public:
	ATower();

protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
	class UArrowComponent* Tower;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Base;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* BarrelMesh;
	UPROPERTY(EditAnywhere)
	class UArrowComponent* Bore;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USphereComponent* RangeDetector;	
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Tower Properties")
	class TSubclassOf<class AProjectile> Projectile;
	UFUNCTION(BlueprintCallable)
	void SetSpecialValue(float value);
	UFUNCTION(BlueprintCallable)
	float GetSpecialValue();
	UFUNCTION(BlueprintCallable)
	int GetCurrentUpgradeCost();
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Upgrades")
	TArray<UTowerUpgradeData*> UpgradeData;
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Tower Properties")
	int CurrentLevel;
	UFUNCTION(BlueprintCallable)
	int GetSellCost();
	UFUNCTION(BlueprintCallable)
	void UpgradeTower();

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION(BlueprintCallable)
	void SetDamage(float damage);
	UFUNCTION(BlueprintCallable)
	void SetFireRate(float rate);
	UFUNCTION(BlueprintCallable)
	float GetFireRate();

private:
	void FindTargetWithinRange();
	void SetTarget(AActor* target);
	void LookAtTarget();
	void Shoot();
	bool IsCurrentTargetWithinRange();
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Tower Properties")
	bool IsAttackingTower;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Tower Properties")
	float FireRate;	
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Tower Properties")
	float Damage;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Tower Properties")
	float SpecialValue;
	int UpgradeCost;
	UPROPERTY()
	int SellCost;
	AActor* CurrentTarget;
	FTimerHandle FireRateHandler;
};