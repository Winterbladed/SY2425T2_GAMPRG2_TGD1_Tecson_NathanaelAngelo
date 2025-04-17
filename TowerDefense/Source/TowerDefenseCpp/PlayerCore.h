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
	APlayerCore();
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Event Dispatcher")
	FOnCoreHitSignature OnPlayerCoreHit;
	
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void TakeDamage();
};