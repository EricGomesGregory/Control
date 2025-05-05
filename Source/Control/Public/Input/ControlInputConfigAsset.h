// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "ControlInputConfigAsset.generated.h"

class UInputAction;


USTRUCT(BlueprintType)
struct FControlInputAction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	const UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (Categories = "Input"))
	FGameplayTag InputTag = FGameplayTag();
};

/**
 * 
 */
UCLASS()
class CONTROL_API UControlInputConfigAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FControlInputAction> AbilityInputActions;

	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& Tag, bool bLogNotFound = false) const;
};
