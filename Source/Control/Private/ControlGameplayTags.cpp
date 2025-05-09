// Fill out your copyright notice in the Description page of Project Settings.


#include "ControlGameplayTags.h"
#include "GameplayTagsManager.h"


FControlGameplayTags FControlGameplayTags::Instance;

void FControlGameplayTags::InitializeNativeGameplayTags() {

	/* Input tags */

	Instance.Input_Move = CreateNativeTag("Input.Move", "");
	Instance.Input_Look = CreateNativeTag("Input.Look", "");
	Instance.Input_Crouch = CreateNativeTag("Input.Crouch", "");
	Instance.Input_Jump = CreateNativeTag("Input.Jump", "");
	Instance.Input_Interact = CreateNativeTag("Input.Interact", "");


	/* Attribute tags */

	Instance.Attribute_Vital_Health = CreateNativeTag("Attribute.Vital.Health");
	Instance.Attribute_Vital_MaxHealth = CreateNativeTag("Attribute.Vital.MaxHealth");

	
	/* Ability tags */

	// Interaction
	Instance.Ability_Interaction_Activate = CreateNativeTag("Ability.Interaction.Activate", "");
	Instance.Ability_Interaction_Duration_Message = CreateNativeTag("Ability.Interaction.Duration.Message");

	// Hacking
	Instance.Ability_Hacking_Activate = CreateNativeTag("Ability.Hacking.Activate", "");
	Instance.Ability_Hacking_Duration_Message = CreateNativeTag("Ability.Hacking.Duration.Message");
}

FGameplayTag FControlGameplayTags::CreateNativeTag(const FName Name, const FString Description) {
	return UGameplayTagsManager::Get().AddNativeGameplayTag(Name, Description);
}
