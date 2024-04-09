// Copyright Rong Jie

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "SpellMenuWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSpellGlobeSelectedSignature, bool , bSpendPointButtonEnable, bool , bEquipButtonEnable);

/**
 * 
 */
UCLASS()
class AURA_API USpellMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	
	UPROPERTY(BlueprintAssignable, Category= "GAS|SpellPoint")
	FOnPlayerStatChangedSignature OnSpellPointChangedDelegate;

	UPROPERTY(BlueprintAssignable, Category= "GAS|SpellPoint")
	FOnSpellGlobeSelectedSignature OnSpellGlobeSelectedDelegate;

	UFUNCTION(BlueprintCallable, Category= "GAS|SpellPoint")
	void SelectSpellGlobe(const FGameplayTag& AbilityTag);
};
