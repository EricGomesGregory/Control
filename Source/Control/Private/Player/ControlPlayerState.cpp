// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ControlPlayerState.h"
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

void AControlPlayerState::SetAbilitySystemComponent(UAbilitySystemComponent* InASC) {
	UAbilitySystemComponent* OldASC = AbilitySystemComponent;
	// @Eric TODO: Handle unbinding logic

	AbilitySystemComponent = InASC;
	// @Eric TODO: Handle binding logic

	OnAbilitySystemComponentChanged.Broadcast(InASC, OldASC);
}

void AControlPlayerState::SetAttributeSet(UAttributeSet* InAttributeSet) {
	UAttributeSet* OldAttributeSet = AttributeSet;
	// @Eric TODO: Handle unbinding logic

	AttributeSet = InAttributeSet;
	// @Eric TODO: Handle binding logic
	
	OnAttributeSetChanged.Broadcast(InAttributeSet, OldAttributeSet);
}
