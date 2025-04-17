#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Waypoint.generated.h"

UCLASS()
class TOWERDEFENSECPP_API AWaypoint : public AActor
{
	GENERATED_BODY()
	
public:	
	AWaypoint();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	int GetWayPointSequence();

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int WaypointSequence;
};