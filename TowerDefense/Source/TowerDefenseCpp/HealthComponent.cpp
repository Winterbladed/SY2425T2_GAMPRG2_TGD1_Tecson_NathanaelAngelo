// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
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
	//UE_LOG(LogTemp, Warning, TEXT("Taking Damage"));
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

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHp = MaxHp;
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

