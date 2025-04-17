#include "EnemyController.h"
#include "Enemy.h"

void AEnemyController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	AEnemy* EnemyAI = Cast<AEnemy>(GetPawn());
	if (EnemyAI)
	{
		EnemyAI->MoveToWayPoints();
		
	}
}