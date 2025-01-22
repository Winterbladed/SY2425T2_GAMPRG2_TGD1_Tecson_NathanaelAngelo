#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndlessRunnerActor.generated.h"

UCLASS()
class ENDLESSRUNNER_API AEndlessRunnerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEndlessRunnerActor();

protected:
	// void Start Function
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	int CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	int MaxHealth;

public:	
	// void Update Function
	virtual void Tick(float DeltaTime) override;

};