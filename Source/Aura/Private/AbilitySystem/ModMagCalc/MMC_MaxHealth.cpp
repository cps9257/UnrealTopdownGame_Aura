// Copyright Rong Jie


#include "AbilitySystem/ModMagCalc/MMC_MaxHealth.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	AttributeDef.AttributeToCapture = UAuraAttributeSet::GetVigorAttribute();
	AttributeDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	AttributeDef.bSnapshot = false;
	RelevantAttributesToCapture.Add(AttributeDef);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather tags from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	float AttributeValue = 0.f;
	GetCapturedAttributeMagnitude(AttributeDef,Spec,EvaluateParameters,AttributeValue);
	AttributeValue = FMath::Max<float>(AttributeValue,0.f);

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();

	return 80.f + 2.5f * AttributeValue + 10.0f * PlayerLevel;
}
