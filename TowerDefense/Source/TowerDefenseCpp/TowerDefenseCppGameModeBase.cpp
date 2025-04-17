#include "TowerDefenseCppGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCore.h"
#include "EnemySpawner.h"

ATowerDefenseCppGameModeBase::ATowerDefenseCppGameModeBase()
{
	PlayerHp = 15;
	CurrentWaveItr = 0;
	TotalEnemiesDestroyedInWave = 0;
	PlayerGold = 8;
}

void ATowerDefenseCppGameModeBase::DeductGold(int amount)
{
	PlayerGold -= amount;
}

void ATowerDefenseCppGameModeBase::AddGold(int amount)
{
	PlayerGold += amount;
}

void ATowerDefenseCppGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("WaveGoldReward: %d"), WaveData[0]->WaveGoldReward);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerCore::StaticClass(), PlayerCores);
	for (AActor* Actors : PlayerCores)
	{
		APlayerCore* core = Cast<APlayerCore>(Actors);
		if (core)
		{
			core->OnPlayerCoreHit.AddDynamic(this, &ATowerDefenseCppGameModeBase::OnCoreHit);
		}
	}
	if (WaveData.Num() != 0)
	{		
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemySpawner::StaticClass(), EnemySpawners);
		TotalWaveCount = WaveData.Num();
		UE_LOG(LogTemp, Warning, TEXT("TotalWaveCount: %d"), TotalWaveCount);
		for (AActor* Actors : EnemySpawners)
		{
			AEnemySpawner* Spawner = Cast<AEnemySpawner>(Actors);
			if (Spawner)
			{
				Spawner->OnEnemySpawnedDeath.AddDynamic(this, &ATowerDefenseCppGameModeBase::UpdateTotalEnemyDestroyed);
			}
		}
		StartNewWave();		
	}
}

void ATowerDefenseCppGameModeBase::OnCoreHit()
{
	ReduceHp();	
}

void ATowerDefenseCppGameModeBase::StartNewWave()
{
	UE_LOG(LogTemp, Warning, TEXT("Wave Started"));
	if (CurrentWaveItr < TotalWaveCount)
	{
		for (AActor* Actors : EnemySpawners)
		{
			TotalEnemiesSpawned = EnemySpawners.Num() * WaveData[CurrentWaveItr]->SpawnAmount;
			AEnemySpawner* Spawner = Cast<AEnemySpawner>(Actors);
			if (Spawner)
			{
				Spawner->SetWaveParameters(WaveData[CurrentWaveItr]->BP_Enemy, WaveDelay, WaveData[CurrentWaveItr]->SpawnAmount, 
					WaveData[CurrentWaveItr]->SpawnInterval, WaveData[CurrentWaveItr]->HpScaling, WaveData[CurrentWaveItr]->GoldRewardScaling);
				Spawner->StartWave();
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("You Win"));
	}
	CurrentWaveItr++;
	if (CurrentWaveItr >= TotalWaveCount)
	{
		CurrentWaveItr = TotalWaveCount;
		QuitGame();
	}
}

void ATowerDefenseCppGameModeBase::UpdateTotalEnemyDestroyed(int goldReward)
{
	TotalEnemiesDestroyedInWave++;
	PlayerGold += goldReward;
	if (TotalEnemiesDestroyedInWave >= TotalEnemiesSpawned)
	{	
		PlayerGold += WaveData[CurrentWaveItr - 1]->WaveGoldReward;
		StartNewWave();
		TotalEnemiesDestroyedInWave = 0;
	}
}

void ATowerDefenseCppGameModeBase::ReduceHp()
{
	PlayerHp--;
	if (PlayerHp <= 0)
	{
		PlayerHp = 0;
		QuitGame();
	}
}

void ATowerDefenseCppGameModeBase::QuitGame()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController)
	{
		PlayerController->ConsoleCommand("quit", true);
	}
}