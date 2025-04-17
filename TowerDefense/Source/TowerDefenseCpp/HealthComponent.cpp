#include "HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHealthComponent::ScaleHp(float scale)
{
	MaxHp *= scale;
	CurrentHp = MaxHp;
}

float UHealthComponent::GetCurrentHp()
{
	return CurrentHp;
}

float UHealthComponent::GetMaxHp()
{
	return MaxHp;
}

void UHealthComponent::TakeDamage(float damage)
{
	AActor* Owner = GetOwner();
	if (Owner)
	{
		CurrentHp -= damage;
		if (CurrentHp <= 0)
		{
			CurrentHp = 0;
			Owner->Destroy();
		}
	}
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHp = MaxHp;
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}