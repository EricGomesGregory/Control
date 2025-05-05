// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ControlCharacterBase.h"


AControlCharacterBase::AControlCharacterBase() {
 	PrimaryActorTick.bCanEverTick = true;

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
