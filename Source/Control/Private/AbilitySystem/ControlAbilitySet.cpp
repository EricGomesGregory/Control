// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ControlAbilitySet.h"
#include "AbilitySystem/ControlGameplayAbility.h"
#include "AbilitySystem/ControlAbilitySystemComponent.h"


void FAbilitySet_GrantedHandles::AddAbilitySpecHandle(const FGameplayAbilitySpecHandle& Handle) {
	if (Handle.IsValid()) {
		AbilitySpecHandles.Add(Handle);
	}
}

void FAbilitySet_GrantedHandles::AddGameplayEffectHandle(const FActiveGameplayEffectHandle& Handle) {
	if (Handle.IsValid()) {
		GameplayEffectHandles.Add(Handle);
	}
}

void FAbilitySet_GrantedHandles::AddAttributeSet(UAttributeSet* Set) {
	GrantedAttributeSets.Add(Set);
}

void FAbilitySet_GrantedHandles::TakeFromAbilitySystem(UControlAbilitySystemComponent* AbilitySystemComponent) {
	check(AbilitySystemComponent);

	if (AbilitySystemComponent->IsOwnerActorAuthoritative() == false) {
		return;
	}

	for (const FGameplayAbilitySpecHandle& Handle : AbilitySpecHandles) {
		if (Handle.IsValid()) {
			AbilitySystemComponent->ClearAbility(Handle);
		}
	}

	for (const FActiveGameplayEffectHandle& Handle : GameplayEffectHandles) {
		if (Handle.IsValid()) {
			AbilitySystemComponent->RemoveActiveGameplayEffect(Handle);
		}
	}

	for (UAttributeSet* Set : GrantedAttributeSets) {
		AbilitySystemComponent->RemoveSpawnedAttribute(Set);
	}

	AbilitySpecHandles.Reset();
	GameplayEffectHandles.Reset();
	GrantedAttributeSets.Reset();
}

UControlAbilitySet::UControlAbilitySet(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer) {
}

void UControlAbilitySet::GiveToAbilitySystem(UControlAbilitySystemComponent* AbilitySystemComponent, FAbilitySet_GrantedHandles* OutGrantedHandles, UObject* SourceObject) const {
	check(AbilitySystemComponent);

	if (AbilitySystemComponent->IsOwnerActorAuthoritative() == false) {
		return;
	}

	for (int32 AbilityIndex = 0; AbilityIndex < GrantedGameplayAbilities.Num(); AbilityIndex++) {
		const auto& AbilityToGrant = GrantedGameplayAbilities[AbilityIndex];

		if (!IsValid(AbilityToGrant.Ability)) {
			UE_LOG(LogTemp, Error, TEXT("GrantedGameplayAbilities[%d] on ability set [%s] is not valid."), AbilityIndex, *GetNameSafe(this));
			continue;
		}

		auto* GameAbility = AbilityToGrant.Ability->GetDefaultObject<UControlGameplayAbility>();
		int32 AbilityLevel = AbilityToGrant.bCustomAbilityLevel ? AbilityToGrant.AbilityLevel : 1; // TODO: Get level of actor to grant the ability
		auto AbilitySpecHandle = AbilitySystemComponent->AddCharacterAbility(GameAbility->GetClass(), AbilityToGrant.InputTag, AbilityLevel);

		if (OutGrantedHandles) {
			OutGrantedHandles->AddAbilitySpecHandle(AbilitySpecHandle);
		}
	}
}
