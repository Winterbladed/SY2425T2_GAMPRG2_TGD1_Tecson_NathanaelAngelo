#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOWERDEFENSECPP_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* ProjectileMesh;
	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent* ProjectileMovement;
	UFUNCTION()
	void SetProjectileDamage(float damage);
	UFUNCTION()
	void SetSpecialParameter(float value);

protected:
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Projectile Properties")
	float Damage;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Projectile Properties")
	float SpecialValue;

public:	
	virtual void Tick(float DeltaTime) override;

private:
};