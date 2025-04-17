#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Enemy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyDestroyed, int, GoldReward);

UCLASS()
class TOWERDEFENSECPP_API AEnemy : public APawn
{
	GENERATED_BODY()

public:
	AEnemy();
	UPROPERTY(BlueprintAssignable, Category = "Event Dispatcher")
	FOnEnemyDestroyed OnEnemyDestroyed;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UHealthComponent* EnemyHealthComponent;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void Destroyed() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION()
	void MoveToWayPoints();
	UFUNCTION()
	void SetWayPoints(TArray<AActor*> points);
	UFUNCTION()
	void ScaleHealthPoints(float scale);
	UFUNCTION()
	void ScaleGoldReward(float scale);
	UFUNCTION(BlueprintCallable)
	void SetBonusGoldDrop(float amount);
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy Properties", meta = (AllowPrivateAccess = "true"))
	float MovementSpeed;
	UFUNCTION()
	void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

private:
	UPROPERTY(EditAnywhere, Category = "Enemy Properties", meta = (AllowPrivateAccess = "true"))
	int CurrentWaypoint;
	UPROPERTY(EditAnywhere, Category = "Enemy Properties", meta = (AllowPrivateAccess = "true"))
	int GoldDrop;
	UPROPERTY(EditAnywhere, Category = "Enemy Properties", meta = (AllowPrivateAccess = "true"))
	int BonusGoldDrop;
	UPROPERTY(EditAnywhere, Category = "Enemy Properties",  meta = (AllowPrivateAccess = "true"))
	TArray <AActor*> Waypoints;
};