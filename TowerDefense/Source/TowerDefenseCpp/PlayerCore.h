// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerCore.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCoreHitSignature);

UCLASS()
class TOWERDEFENSECPP_API APlayerCore : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerCore();

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Event Dispatcher")
	FOnCoreHitSignature OnPlayerCoreHit;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void TakeDamage();

};
