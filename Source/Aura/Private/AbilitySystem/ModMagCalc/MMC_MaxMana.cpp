// Copyright Rong Jie


#include "AbilitySystem/ModMagCalc/MMC_MaxMana.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	AttributeDef.AttributeToCapture = UAuraAttributeSet::GetIntelligenceAttribute();
	AttributeDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	AttributeDef.bSnapshot = false;
	RelevantAttributesToCapture.Add(AttributeDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
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

	int32 PlayerLevel = 1;
	if (Spec.GetContext().GetSourceObject()->Implements<UCombatInterface>())
	{
		PlayerLevel = ICombatInterface::Execute_GetPlayerLevel(Spec.GetContext().GetSourceObject());
	}

	return 50.f + 2.5f * AttributeValue + 10.0f * PlayerLevel;
}
