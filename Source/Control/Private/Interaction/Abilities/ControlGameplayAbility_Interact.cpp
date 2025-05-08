// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/Abilities/ControlGameplayAbility_Interact.h"
#include "Interaction/Tasks/AbilityTask_GrantInteraction.h"
#include "Interaction/InteractableTarget.h"
#include "Interaction/InteractionStatics.h"
#include "AbilitySystemComponent.h"

#include "Player/ControlPlayerController.h"
#include "ControlGameplayTags.h"


UControlGameplayAbility_Interact::UControlGameplayAbility_Interact(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer){
	bActivateAbilityOnGranted = true;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
}

void UControlGameplayAbility_Interact::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) {
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UAbilitySystemComponent* AbilitySystem = GetAbilitySystemComponentFromActorInfo();
	if (AbilitySystem && AbilitySystem->GetOwnerRole() == ROLE_Authority) {
		UAbilityTask_GrantInteraction* Task = UAbilityTask_GrantInteraction::GrantAbilitiesForNearbyInteractors(this, InteractionScanRange, InteractionScanRate);
		Task->ReadyForActivation();
	}
}

void UControlGameplayAbility_Interact::UpdateInteractions(const TArray<FInteractionOption>& InteractiveOptions) {
	if (auto* PC = CastChecked<AControlPlayerController>(CurrentActorInfo->PlayerController)) {
		/* @Eric TODO: Handle UI like Lyra?
		if (ULyraIndicatorManagerComponent* IndicatorManager = ULyraIndicatorManagerComponent::GetComponent(PC)) {
			for (UIndicatorDescriptor* Indicator : Indicators) {
				IndicatorManager->RemoveIndicator(Indicator);
			}
			Indicators.Reset();

			for (const FInteractionOption& InteractionOption : InteractiveOptions) {
				AActor* InteractableTargetActor = UInteractionStatics::GetActorFromInteractableTarget(InteractionOption.InteractableTarget);

				TSoftClassPtr<UUserWidget> InteractionWidgetClass =
					InteractionOption.InteractionWidgetClass.IsNull() ? DefaultInteractionWidgetClass : InteractionOption.InteractionWidgetClass;

				UIndicatorDescriptor* Indicator = NewObject<UIndicatorDescriptor>();
				Indicator->SetDataObject(InteractableTargetActor);
				Indicator->SetSceneComponent(InteractableTargetActor->GetRootComponent());
				Indicator->SetIndicatorClass(InteractionWidgetClass);
				IndicatorManager->AddIndicator(Indicator);

				Indicators.Add(Indicator);
			}
		}
		else {
			//TODO This should probably be a noisy warning.  Why are we updating interactions on a PC that can never do anything with them?
		}
		*/
	}

	CurrentOptions = InteractiveOptions;
}

void UControlGameplayAbility_Interact::TriggerInteraction() {
	if (CurrentOptions.Num() == 0) {
		return;
	}

	UAbilitySystemComponent* AbilitySystem = GetAbilitySystemComponentFromActorInfo();
	if (AbilitySystem) {
		const FInteractionOption& InteractionOption = CurrentOptions[0];
		FGameplayTag AbilityInteractionActivateTag = FControlGameplayTags::Get().Ability_Interaction_Activate;

		AActor* Instigator = GetAvatarActorFromActorInfo();
		AActor* InteractableTargetActor = UInteractionStatics::GetActorFromInteractableTarget(InteractionOption.InteractableTarget);

		// Allow the target to customize the event data we're about to pass in, in case the ability needs custom data
		// that only the actor knows.
		FGameplayEventData Payload;
		Payload.EventTag = AbilityInteractionActivateTag;
		Payload.Instigator = Instigator;
		Payload.Target = InteractableTargetActor;

		// If needed we allow the interactable target to manipulate the event data so that for example, a button on the wall
		// may want to specify a door actor to execute the ability on, so it might choose to override Target to be the
		// door actor.
		InteractionOption.InteractableTarget->CustomizeInteractionEventData(AbilityInteractionActivateTag, Payload);

		// Grab the target actor off the payload we're going to use it as the 'avatar' for the interaction, and the
		// source InteractableTarget actor as the owner actor.
		AActor* TargetActor = const_cast<AActor*>(ToRawPtr(Payload.Target));

		// The actor info needed for the interaction.
		FGameplayAbilityActorInfo ActorInfo;
		ActorInfo.InitFromActor(InteractableTargetActor, TargetActor, InteractionOption.TargetAbilitySystem);

		// Trigger the ability using event tag.
		const bool bSuccess = InteractionOption.TargetAbilitySystem->TriggerAbilityFromGameplayEvent(
			InteractionOption.TargetInteractionAbilityHandle,
			&ActorInfo,
			AbilityInteractionActivateTag,
			&Payload,
			*InteractionOption.TargetAbilitySystem
		);
	}
}
