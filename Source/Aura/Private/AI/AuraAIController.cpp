// Copyright Rong Jie


#include "AI/AuraAIController.h"

#include "Aura/Aura.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AAuraAIController::AAuraAIController()
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>("BlackboardComponent");
	check(Blackboard);
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviorTreeComponent");
	check(BehaviorTreeComponent);
}

FGenericTeamId AAuraAIController::GetGenericTeamId() const
{
	return FGenericTeamId(ENEMY_TEAM_ID);
}

ETeamAttitude::Type AAuraAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	if (const APawn* OtherPawn = Cast<APawn>(&Other)) {
     
		if (const IGenericTeamAgentInterface* TeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController()))
		{
			return Super::GetTeamAttitudeTowards(*OtherPawn->GetController());
		}
	}
	
	return ETeamAttitude::Neutral;
}
