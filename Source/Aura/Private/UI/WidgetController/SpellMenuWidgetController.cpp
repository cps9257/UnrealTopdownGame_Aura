// Copyright Rong Jie


#include "UI/WidgetController/SpellMenuWidgetController.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Player/AuraPlayerState.h"

void USpellMenuWidgetController::BroadcastInitialValues()
{
	BroadcastAbilityInfo();
	
	OnSpellPointChangedDelegate.Broadcast(GetAuraPS()->GetSpellPoints());
}

void USpellMenuWidgetController::BindCallbacksToDependencies()
{
	GetAuraASC()->AbilityStatusChanged.AddLambda([this](const FGameplayTag& AbilityTag, const FGameplayTag& StatusTag)
	{
		if(AbilityInfo)
		{
			FAuraAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AbilityTag);
			Info.StatusTag = StatusTag;
			AbilityInfoDelegate.Broadcast(Info);
		}
	});

	GetAuraPS()->OnSpellPointsChangedDelegate.AddLambda(
		[this](int32 NewSpellPoint)
		{
			OnSpellPointChangedDelegate.Broadcast(NewSpellPoint);
		}
	);
}

// Status, SpellPoints , enableSpendBtn, enableEquipBtn
// Locked, >0, false, false
// Locked, =0, false, false
// Eligible, >0, true, false
// Eligible, =0, false, false
// Unlock, >0, true, true
// Unlock, =0, false, true
// Equipped, >0, true, true
// Equipped, =0, false, true
void USpellMenuWidgetController::SelectSpellGlobe(const FGameplayTag& AbilityTag)
{
	bool bSpendPointButtonEnable = false;
	bool bEquipButtonEnable = false;
	FGameplayTag StatusTag;
	const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();

	const bool bTagValid = AbilityTag.IsValid();
	const FGameplayAbilitySpec* AbilitySpec = GetAuraASC()->GetSpecFromAbilityTag(AbilityTag);
	const bool bSpecValid = AbilitySpec != nullptr;

	if (!bTagValid || !bSpecValid)
	{
		StatusTag = GameplayTags.Abilities_Status_Locked;
	}
	else
	{
		StatusTag = GetAuraASC()->GetStatusFromSpec(*AbilitySpec);
	}

	const int32 SpellPoints = GetAuraPS()->GetSpellPoints();

	if (StatusTag.MatchesTagExact(GameplayTags.Abilities_Status_Locked))
	{
		bSpendPointButtonEnable = false;
		bEquipButtonEnable = false;
	}
	else if (StatusTag.MatchesTagExact(GameplayTags.Abilities_Status_Eligible))
	{
		bSpendPointButtonEnable = SpellPoints > 0;
		bEquipButtonEnable = false;
	}
	else if (StatusTag.MatchesTagExact(GameplayTags.Abilities_Status_Unlocked))
	{
		bSpendPointButtonEnable = SpellPoints > 0;
		bEquipButtonEnable = true;
	}
	else if (StatusTag.MatchesTagExact(GameplayTags.Abilities_Status_Equipped))
	{
		bSpendPointButtonEnable = SpellPoints > 0;
		bEquipButtonEnable = true;
	}

	OnSpellGlobeSelectedDelegate.Broadcast(bSpendPointButtonEnable, bEquipButtonEnable);
}
