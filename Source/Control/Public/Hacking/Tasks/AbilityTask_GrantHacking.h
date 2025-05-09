// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_GrantHacking.generated.h"

/**
 * 
 */
UCLASS()
class CONTROL_API UAbilityTask_GrantHacking : public UAbilityTask
{
	GENERATED_BODY()
	
public:
	virtual void Activate() override;

	/** Wait until an overlap occurs. This will need to be better fleshed out so we can specify game specific collision requirements */
	UFUNCTION(BlueprintCallable, Category = "Control Protocol|Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UAbilityTask_GrantHacking* GrantAbilitiesForNearbyHackables(UGameplayAbility* OwningAbility, float HackingScanRange, float HackingScanRate);

private:

	virtual void OnDestroy(bool AbilityEnded) override;

	void QueryInteractables();

	float HackingScanRange = 1000;
	float HackingScanRate = 0.200;

	FTimerHandle QueryTimerHandle;

	TMap<FObjectKey, FGameplayAbilitySpecHandle> HackingAbilityCache;
};
