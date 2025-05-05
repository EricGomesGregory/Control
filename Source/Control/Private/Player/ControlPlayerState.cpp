// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ControlPlayerState.h"
#include "AbilitySystem/ControlAbilitySystemComponent.h"
#include "AbilitySystem/ControlAttributeSet.h"


FName AControlPlayerState::AbilitySystemComponentName(TEXT("Ability System Component"));
FName AControlPlayerState::AttributeSetName(TEXT("Attribute Set"));

AControlPlayerState::AControlPlayerState(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer) {
	AbilitySystemComponent = CreateDefaultSubobject<UControlAbilitySystemComponent>(AbilitySystemComponentName);
	AbilitySystemComponent->SetIsReplicated(true); //Enable component to be replicated on multiplayer
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UControlAttributeSet>(AttributeSetName);

	SetNetUpdateFrequency(100.0f);
}

UAbilitySystemComponent* AControlPlayerState::GetAbilitySystemComponent() const {
	return AbilitySystemComponent;
}

UAttributeSet* AControlPlayerState::GetAttributeSet() const {
	return AttributeSet;
}