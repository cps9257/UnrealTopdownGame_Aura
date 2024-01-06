// Copyright Rong Jie

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "GameFramework/PlayerState.h"
#include "UObject/NoExportTypes.h"
#include "AuraWidgetController.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class AURA_API UAuraWidgetController : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly,Category="WidgetContorller")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly,Category="WidgetContorller")
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly,Category="WidgetContorller")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly,Category="WidgetContorller")
	TObjectPtr<UAttributeSet> AttributeSet;
};
