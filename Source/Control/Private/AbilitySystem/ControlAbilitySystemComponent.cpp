// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ControlAbilitySystemComponent.h"


UControlAbilitySystemComponent::UControlAbilitySystemComponent(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer) {

}

void UControlAbilitySystemComponent::AbilityInputTagPressed(const FGameplayTag& InputTag) {
	// @Eric TODO: Implement trigger ability on pressed
}

void UControlAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag) {
	if (InputTag.IsValid() == false) return;

	for (auto& AbilitySpec : GetActivatableAbilities()) {
		if (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag) == false) continue;

		AbilitySpecInputReleased(AbilitySpec);
	}
}

void UControlAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag) {
	if (InputTag.IsValid() == false) return;

	for (auto& AbilitySpec : GetActivatableAbilities()) {
		if (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag) == false) continue;

		AbilitySpecInputPressed(AbilitySpec);

		if (AbilitySpec.IsActive()) continue;
		TryActivateAbility(AbilitySpec.Handle);
	}
}
