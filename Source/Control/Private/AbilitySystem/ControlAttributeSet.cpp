// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ControlAttributeSet.h"
#include "ControlGameplayTags.h"
#include "Net/UnrealNetwork.h"

UControlAttributeSet::UControlAttributeSet(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer) {

	const auto& GameplayTags = FControlGameplayTags::Get();

	TagsToAttributes.Add(GameplayTags.Attribute_Vital_Health, GetHealthAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Vital_MaxHealth, GetMaxHealthAttribute);
}

void UControlAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MaxHealth, COND_None, REPNOTIFY_Always);
}

void UControlAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) {
	Super::PreAttributeBaseChange(Attribute, NewValue);

	// @Eric TODO: Implement
}

void UControlAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) {
	Super::PostGameplayEffectExecute(Data);

	// @Eric TODO: Implement
}

void UControlAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Health, OldHealth);
}

void UControlAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MaxHealth, OldMaxHealth);

}
