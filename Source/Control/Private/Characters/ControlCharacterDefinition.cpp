// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ControlCharacterDefinition.h"
#include "AbilitySystem/ControlAbilitySystemComponent.h"
#include "Characters/ControlCharacterBase.h"


UControlCharacterDefinition::UControlCharacterDefinition(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer) {
}

void UControlCharacterDefinition::SetupCharacterVisuals(const AControlCharacterBase* Character) {
	// @Eric TODO: Handle character skin and accessories
}

void UControlCharacterDefinition::SetupCharacterGameplay(const AControlCharacterBase* Character) {
	auto* CharacterASC = CastChecked<UControlAbilitySystemComponent>(Character->GetAbilitySystemComponent());

	AbilitySet->GiveToAbilitySystem(CharacterASC, nullptr);
}
