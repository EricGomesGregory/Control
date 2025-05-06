// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ControlCharacterBase.h"
#include "AbilitySystem/ControlAbilitySystemComponent.h"
#include "AbilitySystem/ControlAttributeSet.h"


FName AControlCharacterBase::AbilitySystemComponentName(TEXT("Ability System Component"));
FName AControlCharacterBase::AttributeSetName(TEXT("Attribute Set"));

AControlCharacterBase::AControlCharacterBase() {
 	PrimaryActorTick.bCanEverTick = true;

    AbilitySystemComponent = CreateDefaultSubobject<UControlAbilitySystemComponent>(AbilitySystemComponentName);
    AbilitySystemComponent->SetIsReplicated(true); //Enable component to be replicated on multiplayer
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

    AttributeSet = CreateDefaultSubobject<UControlAttributeSet>(AttributeSetName);
}

UAbilitySystemComponent* AControlCharacterBase::GetAbilitySystemComponent() const {
    return AbilitySystemComponent;
}

UAttributeSet* AControlCharacterBase::GetAttributeSet() const {
    return AttributeSet;
}

void AControlCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> Effect, float level) const {
    // @Eric TODO: Implement this function
}
