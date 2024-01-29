// Copyright Rong Jie

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "Engine/AssetManager.h"
#include "AuraAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraAssetManager : public UAssetManager
{
public:
	GENERATED_BODY()
	static UAuraAssetManager& Get();

protected:
	virtual void StartInitialLoading() override;
};
