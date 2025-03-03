#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndlessRunnerActor.generated.h"

UCLASS()
class ENDLESSRUNNER_API AEndlessRunnerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AEndlessRunnerActor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	int CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	int MaxHealth;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* CollisionBox;

	UFUNCTION(BlueprintImplementableEvent, Category = "Obstacle")
	void OnTrigger();

	UFUNCTION()
	void HandleCollision(AActor* OverlappedActor, AActor* OtherActor);
};