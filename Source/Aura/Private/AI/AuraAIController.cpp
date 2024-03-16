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
     
		// DEFAULT BEHAVIOR---------------------------------------------------
		if (const IGenericTeamAgentInterface* TeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController()))
		{
			return Super::GetTeamAttitudeTowards(*OtherPawn->GetController());
		}
    
		// //OR CUSTOM BEHAVIOUR--------------------------------------------------
		// if (const IGenericTeamAgentInterface* TeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController()))
		// {
		// 	//Create an alliance with Team with ID 10 and set all the other teams as Hostiles:
		// 	FGenericTeamId OtherTeamID = TeamAgent->GetGenericTeamId();
		// 	if (OtherTeamID == FGenericTeamId(NEUTRAL_TEAM_ID)) {
		// 		return ETeamAttitude::Neutral;
		// 	}
		// 	else {
		// 		return ETeamAttitude::Hostile;
		// 	}
		// }
	}

	return ETeamAttitude::Neutral;
}
