#include "Tower.h"
#include "Components/SphereComponent.h"
#include "Enemy.h"
#include <Kismet/KismetMathLibrary.h>
#include "Components/ArrowComponent.h"
#include "Projectile.h"

ATower::ATower()
{
	PrimaryActorTick.bCanEverTick = true;
	Tower = CreateDefaultSubobject<UArrowComponent>("Tower");
	Tower->SetupAttachment(RootComponent);
	Base = CreateDefaultSubobject<UStaticMeshComponent>("Tower Base");
	Base->SetupAttachment(Tower);
	BarrelMesh = CreateDefaultSubobject<UStaticMeshComponent>("Barrel Mesh");
	BarrelMesh->SetupAttachment(Tower);
	Bore = CreateDefaultSubobject<UArrowComponent>("Bore");
	Bore->SetupAttachment(BarrelMesh);	
	RangeDetector = CreateDefaultSubobject<USphereComponent>("Range Hitbox");
	RangeDetector->SetupAttachment(Tower);
	CurrentLevel = 0;
}

void ATower::BeginPlay()
{
	Super::BeginPlay();
	UpgradeTower();
}

void ATower::FindTargetWithinRange()
{
	TArray<AActor* > Targets;
	RangeDetector->GetOverlappingActors(Targets, AEnemy::StaticClass());
	float ClosestDistance = MAX_FLT;
	for (AActor* EnemyActor : Targets)
	{
		AEnemy* Target = Cast<AEnemy>(EnemyActor);
		if (Target)
		{
			float Distance = FVector::Distance(Target->GetActorLocation(), GetActorLocation());
			if (Distance < ClosestDistance)
			{
				ClosestDistance = Distance;
				CurrentTarget = Target;
			}
		}
	}	
	if (Targets.Num() == 0)
	{
		CurrentTarget = nullptr;
	}
}

void ATower::SetTarget(AActor* target)
{
	CurrentTarget = target;
}

void ATower::LookAtTarget()
{
	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), CurrentTarget->GetActorLocation());
	float YawRotation = LookAtRotation.Yaw;
	float PitchRotation = LookAtRotation.Pitch;
	FRotator HorizontalRotation(0.0f, YawRotation, 0.0f);
	FRotator VerticalRotation(PitchRotation, -90.0f, 0.0f);
	SetActorRotation(HorizontalRotation);
	BarrelMesh->SetRelativeRotation(VerticalRotation);
	if (!GetWorldTimerManager().IsTimerActive(FireRateHandler))
	{
		Shoot();
		GetWorld()->GetTimerManager().SetTimer(FireRateHandler, this, &ATower::Shoot, FireRate, true);
	}	
}

void ATower::Shoot()
{
	if (Projectile)
	{
		AProjectile* Bullet = GetWorld()->SpawnActor<AProjectile>(Projectile, Bore->GetComponentLocation(), Bore->GetComponentRotation());
		Bullet->SetProjectileDamage(Damage);
		Bullet->SetSpecialParameter(SpecialValue);
		UE_LOG(LogTemp, Warning, TEXT("Shooting"));
	}
}

bool ATower::IsCurrentTargetWithinRange()
{
	if (CurrentTarget && RangeDetector)
	{
		float Distance = FVector::Distance(CurrentTarget->GetActorLocation(), GetActorLocation());
		return Distance <= RangeDetector->GetScaledSphereRadius();
	}
	return false;
}

void ATower::SetSpecialValue(float value)
{
	SpecialValue = value;
}

float ATower::GetSpecialValue()
{
	return SpecialValue;
}

int ATower::GetCurrentUpgradeCost()
{
	return UpgradeCost;
}

int ATower::GetSellCost()
{
	return SellCost;
}

void ATower::UpgradeTower()
{
	CurrentLevel++;
	if (CurrentLevel >= 3)
	{
		CurrentLevel = 3;
	}
	int levelItr = CurrentLevel - 1;
	Base->SetStaticMesh(UpgradeData[levelItr]->Base);
	BarrelMesh->SetStaticMesh(UpgradeData[levelItr]->Barrel);
	Damage = UpgradeData[levelItr]->Damage;
	UpgradeCost = UpgradeData[levelItr]->UpgradeCost;
	SellCost = UpgradeData[levelItr]->SellCost;
	FireRate = UpgradeData[levelItr]->FireRate;
	SpecialValue = UpgradeData[levelItr]->SpecialValue;
	RangeDetector->SetSphereRadius(UpgradeData[levelItr]->Range);
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!CurrentTarget || !IsCurrentTargetWithinRange() || !CurrentTarget->IsValidLowLevel())
	{
		FindTargetWithinRange();
		GetWorld()->GetTimerManager().ClearTimer(FireRateHandler);
	} 
	else if(IsAttackingTower && CurrentTarget && CurrentTarget->IsValidLowLevel())
	{
		if (IsValid(CurrentTarget))
		{
			LookAtTarget();
		}
		else
		{
			CurrentTarget = nullptr;
			GetWorld()->GetTimerManager().ClearTimer(FireRateHandler);
		}
	}
}

void ATower::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATower::SetDamage(float damage)
{
	Damage = damage;
}

void ATower::SetFireRate(float rate)
{
	FireRate = rate;
}

float ATower::GetFireRate()
{
	return FireRate;
}