// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ControlPlayerState.h"
#include "AbilitySystem/ControlAbilitySet.h"
#include "AbilitySystem/ControlAbilitySystemComponent.h"
#include "AbilitySystemComponent.h"


AControlPlayerState::AControlPlayerState(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer) {
	SetNetUpdateFrequency(100.0f);
}

UAbilitySystemComponent* AControlPlayerState::GetAbilitySystemComponent() const {
	return AbilitySystemComponent;
}

UAttributeSet* AControlPlayerState::GetAttributeSet() const {
	return AttributeSet;
}

void AControlPlayerState::PossessedCharacter(FControlPlayableCharacterData& NewCharacterData) {
	AbilitySystemComponent = NewCharacterData.AbilitySystemComponent;
	AttributeSet = NewCharacterData.AttributeSet;
	CharacterName = NewCharacterData.CharacterName;

	if (IsValid(AbilitySet)) {
		auto* GameAbilitySystemComponent = CastChecked<UControlAbilitySystemComponent>(AbilitySystemComponent);
		AbilitySet->GiveToAbilitySystem(GameAbilitySystemComponent, &GrantedHandles);
	}

	OnPossessed.Broadcast(NewCharacterData);
}

void AControlPlayerState::UnPossessedCharacter() {
	FControlPlayableCharacterData OldCharacterData;
	OldCharacterData.AbilitySystemComponent = AbilitySystemComponent;
	OldCharacterData.AttributeSet = AttributeSet;
	OldCharacterData.CharacterName = CharacterName;

	auto* GameAbilitySystemComponent = CastChecked<UControlAbilitySystemComponent>(AbilitySystemComponent);
	GrantedHandles.TakeFromAbilitySystem(GameAbilitySystemComponent);

	OnUnPossessed.Broadcast(OldCharacterData);
}

