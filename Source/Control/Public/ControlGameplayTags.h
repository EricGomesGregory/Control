// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * 
 */
struct FControlGameplayTags
{
public:
	static FControlGameplayTags& Get() { return Instance; }
	static void InitializeNativeGameplayTags();

	FGameplayTag Input_Move;
	FGameplayTag Input_Look;
	FGameplayTag Input_Jump;
	FGameplayTag Input_Crouch;
	FGameplayTag Input_Interact;
	FGameplayTag Input_Hack;

	FGameplayTag Attribute_Vital_Health;
	FGameplayTag Attribute_Vital_MaxHealth;

	FGameplayTag Ability_Interaction_Activate;
	FGameplayTag Ability_Interaction_Duration_Message;

	FGameplayTag Ability_Hacking_Activate;
	FGameplayTag Ability_Hacking_Duration_Message;

private:
	static FControlGameplayTags Instance;

	static FGameplayTag CreateNativeTag(const FName Name, const FString Description = FString());
};
