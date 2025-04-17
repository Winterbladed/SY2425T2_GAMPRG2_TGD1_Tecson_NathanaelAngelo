#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSECPP_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();
	UFUNCTION()
	void ScaleHp(float scaling);
	UFUNCTION(BlueprintCallable)
	float GetCurrentHp();
	UFUNCTION(BlueprintCallable)
	float GetMaxHp();
	UFUNCTION(BlueprintCallable)
	void TakeDamage(float damage);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Projectile Properties")
	float MaxHp;
	float CurrentHp;
};