// Fill out your copyright notice in the Description page of Project Settings.

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
	// Sets default values for this pawn's properties
	AEnemy();

	UPROPERTY(BlueprintAssignable, Category = "Event Dispatcher")
	FOnEnemyDestroyed OnEnemyDestroyed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UHealthComponent* EnemyHealthComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Destroyed() override;


	// Called to bind functionality to input
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
