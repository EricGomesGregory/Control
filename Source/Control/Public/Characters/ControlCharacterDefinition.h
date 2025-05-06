// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AbilitySystem/ControlAbilitySet.h"
#include "ControlCharacterDefinition.generated.h"

class AControlCharacterBase;

/**
 * 
 */
UCLASS()
class CONTROL_API UControlCharacterDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UControlCharacterDefinition(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	void SetupCharacterVisuals(const AControlCharacterBase* Character);

	void SetupCharacterGameplay(const AControlCharacterBase* Character);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Control Protocol|Character Definition")
	TObjectPtr<UControlAbilitySet> AbilitySet;


};
