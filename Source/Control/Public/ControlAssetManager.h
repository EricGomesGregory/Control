// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "ControlAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class CONTROL_API UControlAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:
	static const UControlAssetManager& Get();

protected:
	virtual void StartInitialLoading();
};
