// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "EnemyController.h"
#include "Waypoint.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/BoxComponent.h"
#include "HealthComponent.h"
#include "PlayerCore.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
    EnemyHealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
    OnActorHit.AddDynamic(this, &AEnemy::OnHit);
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AEnemy::Destroyed()
{
    Super::Destroyed();

    if (EnemyHealthComponent->GetCurrentHp() <= 0)
    {
        OnEnemyDestroyed.Broadcast(GoldDrop + BonusGoldDrop);
    }
    else
    {
        OnEnemyDestroyed.Broadcast(0);
    }
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::MoveToWayPoints()
{
    if (Waypoints.Num() != 0)
    {
        AEnemyController* EnemyController = Cast<AEnemyController>(GetController());

        if (EnemyController && CurrentWaypoint < Waypoints.Num())
        {
            AWaypoint* WaypointItr = Cast<AWaypoint>(Waypoints[CurrentWaypoint]);

            if (WaypointItr)
            {
                EnemyController->MoveToActor(WaypointItr, 5.0f, false);

                FVector Direction = (WaypointItr->GetActorLocation() - GetActorLocation()).GetSafeNormal();
                FRotator NewRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
                SetActorRotation(NewRotation);               

                CurrentWaypoint++;
            }
        }
    }
}

void AEnemy::SetWayPoints(TArray<AActor*> points)
{
    for (AActor* Waypoint : points)
    {
        Waypoints.Add(Waypoint);
    }
}

void AEnemy::ScaleHealthPoints(float scale)
{
    EnemyHealthComponent->ScaleHp(scale);
}

void AEnemy::ScaleGoldReward(float scale)
{
    GoldDrop = FMath::CeilToInt(GoldDrop * scale);
}

void AEnemy::SetBonusGoldDrop(float amount)
{
    BonusGoldDrop = amount;
}

void AEnemy::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
    if (APlayerCore* playerCore = Cast<APlayerCore>(OtherActor))
    {
        this->Destroy();
        playerCore->TakeDamage();
    }
}
