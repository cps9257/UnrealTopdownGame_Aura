// Copyright Rong Jie

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Components/WidgetComponent.h"
#include "Interaction/EnemyInterface.h"
#include "UI/Widget/AuraUserWidget.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AAuraEnemy();

	/** Begin Enemy Interface **/
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	/** End Enemy Interface **/

	/** Begin Combat Interface **/
	virtual int32 GetPlayerLevel() override;
	/** End Combat Interface **/

	UFUNCTION(BlueprintCallable)
	void BroadcastInitialValues();
	void BindCallbacksToDependencies();

	UPROPERTY(BlueprintAssignable, Category= "GAS|Attributes")
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category= "GAS|Attributes")
	FOnAttributeChangedSignature OnMaxHealthChanged;
	
protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	void InitHealthBarWidget();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;

	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UWidgetComponent> HealthBar;
	
};
