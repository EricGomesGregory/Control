// Fill out your copyright notice in the Description page of Project Settings.


#include "Hacking/Abilities/ControlGameplayAbility_Hack.h"
#include "Hacking/Tasks/AbilityTask_GrantHacking.h"
#include "Hacking/HackingStatics.h"
#include "Hacking/HackableTarget.h"
#include "Player/ControlPlayerController.h"
#include "AbilitySystemComponent.h"
#include "ControlGameplayTags.h"


UControlGameplayAbility_Hack::UControlGameplayAbility_Hack(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer) {
	bActivateAbilityOnGranted = true;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
}

void UControlGameplayAbility_Hack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) {
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UAbilitySystemComponent* AbilitySystem = GetAbilitySystemComponentFromActorInfo();
	if (AbilitySystem && AbilitySystem->GetOwnerRole() == ROLE_Authority) {
		UAbilityTask_GrantHacking* Task = UAbilityTask_GrantHacking::GrantAbilitiesForNearbyHackables(this, HackingScanRange, HackingScanRate);
		Task->ReadyForActivation();
	}
}

void UControlGameplayAbility_Hack::UpdateHackings(const TArray<FHackingOption>& HackingOptions) {
	if (auto* PC = CastChecked<AControlPlayerController>(CurrentActorInfo->PlayerController)) {
		/* @Eric TODO: Handle UI like Lyra?
		if (ULyraIndicatorManagerComponent* IndicatorManager = ULyraIndicatorManagerComponent::GetComponent(PC)) {
			for (UIndicatorDescriptor* Indicator : Indicators) {
				IndicatorManager->RemoveIndicator(Indicator);
			}
			Indicators.Reset();

			for (const FHackingOption& HackingOption : InteractiveOptions) {
				AActor* HackableTargetActor = UHackingStatics::GetActorFromHackableTarget(HackingOption.HackableTarget);

				TSoftClassPtr<UUserWidget> HackingWidgetClass =
					HackingOption.HackingWidgetClass.IsNull() ? DefaultHackingWidgetClass : HackingOption.HackingWidgetClass;

				UIndicatorDescriptor* Indicator = NewObject<UIndicatorDescriptor>();
				Indicator->SetDataObject(HackableTargetActor);
				Indicator->SetSceneComponent(HackableTargetActor->GetRootComponent());
				Indicator->SetIndicatorClass(HackingWidgetClass);
				IndicatorManager->AddIndicator(Indicator);

				Indicators.Add(Indicator);
			}
		}
		else {
			//TODO This should probably be a noisy warning.  Why are we updating hackings on a PC that can never do anything with them?
		}
		*/
	}

	CurrentOptions = HackingOptions;
}

void UControlGameplayAbility_Hack::TriggerHacking() {
	if (CurrentOptions.Num() == 0) {
		return;
	}

	UAbilitySystemComponent* AbilitySystem = GetAbilitySystemComponentFromActorInfo();
	if (AbilitySystem) {
		const FHackingOption& HackingOption = CurrentOptions[0];
		FGameplayTag AbilityHackingActivateTag = FControlGameplayTags::Get().Ability_Hacking_Activate;

		AActor* Instigator = GetAvatarActorFromActorInfo();
		AActor* HackableTargetActor = UHackingStatics::GetActorFromHackableTarget(HackingOption.HackableTarget);

		// Allow the target to customize the event data we're about to pass in, in case the ability needs custom data
		// that only the actor knows.
		FGameplayEventData Payload;
		Payload.EventTag = AbilityHackingActivateTag;
		Payload.Instigator = Instigator;
		Payload.Target = HackableTargetActor;

		// If needed we allow the hackable target to manipulate the event data so that for example, a button on the wall
		// may want to specify a door actor to execute the ability on, so it might choose to override Target to be the
		// door actor.
		HackingOption.HackableTarget->CustomizeHackingEventData(AbilityHackingActivateTag, Payload);

		// Grab the target actor off the payload we're going to use it as the 'avatar' for the hacking, and the
		// source HackableTarget actor as the owner actor.
		AActor* TargetActor = const_cast<AActor*>(ToRawPtr(Payload.Target));

		// The actor info needed for the hacking.
		FGameplayAbilityActorInfo ActorInfo;
		ActorInfo.InitFromActor(HackableTargetActor, TargetActor, HackingOption.TargetAbilitySystem);

		// Trigger the ability using event tag.
		const bool bSuccess = HackingOption.TargetAbilitySystem->TriggerAbilityFromGameplayEvent(
			HackingOption.TargetHackingAbilityHandle,
			&ActorInfo,
			AbilityHackingActivateTag,
			&Payload,
			*HackingOption.TargetAbilitySystem
		);
	}
}
