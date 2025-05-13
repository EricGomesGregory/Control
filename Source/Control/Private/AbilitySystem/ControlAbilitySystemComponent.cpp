// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ControlAbilitySystemComponent.h"


UControlAbilitySystemComponent::UControlAbilitySystemComponent(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer) {

}

FGameplayAbilitySpecHandle UControlAbilitySystemComponent::AddCharacterAbility(const TSubclassOf<UGameplayAbility>& AbilityClass, FGameplayTag InputTag, int32 Level) {
	auto AbilitySpec = FGameplayAbilitySpec(AbilityClass, Level);
	AbilitySpec.GetDynamicSpecSourceTags().AddTag(InputTag);
	return GiveAbility(AbilitySpec);
}

void UControlAbilitySystemComponent::AbilityInputTagPressed(const FGameplayTag& InputTag) {
	if (InputTag.IsValid() == false) return;

	for (auto& AbilitySpec : GetActivatableAbilities()) {
		if (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag) == false) continue;

		AbilitySpecInputPressed(AbilitySpec);
	}
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

void UControlAbilitySystemComponent::AbilitySpecInputPressed(FGameplayAbilitySpec& Spec) {
	Super::AbilitySpecInputPressed(Spec);

	if (Spec.IsActive()) {
		TArray<UGameplayAbility*> Instances = Spec.GetAbilityInstances();
		const FGameplayAbilityActivationInfo& ActivationInfo = Instances.Last()->GetCurrentActivationInfoRef();
		FPredictionKey OriginalPredictionKey = ActivationInfo.GetActivationPredictionKey();
		
		InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed, Spec.Handle, OriginalPredictionKey);
	}
}

void UControlAbilitySystemComponent::AbilitySpecInputReleased(FGameplayAbilitySpec& Spec) {
	Super::AbilitySpecInputReleased(Spec);

	if (Spec.IsActive()) {
		TArray<UGameplayAbility*> Instances = Spec.GetAbilityInstances();
		const FGameplayAbilityActivationInfo& ActivationInfo = Instances.Last()->GetCurrentActivationInfoRef();
		FPredictionKey OriginalPredictionKey = ActivationInfo.GetActivationPredictionKey();
		
		InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputReleased, Spec.Handle, OriginalPredictionKey);
	}
}
