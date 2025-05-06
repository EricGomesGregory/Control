// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "ControlAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class CONTROL_API UControlAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	UControlAbilitySystemComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	FGameplayAbilitySpecHandle AddCharacterAbility(const TSubclassOf<UGameplayAbility>& AbilityClass, FGameplayTag InputTag, int32 Level = 1);

	void AbilityInputTagPressed(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);
	void AbilityInputTagHeld(const FGameplayTag& InputTag);
};
