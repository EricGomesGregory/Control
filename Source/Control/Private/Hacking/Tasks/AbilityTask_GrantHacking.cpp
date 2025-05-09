// Fill out your copyright notice in the Description page of Project Settings.


#include "Hacking/Tasks/AbilityTask_GrantHacking.h"
#include "Hacking/HackableTarget.h"
#include "Hacking/HackingStatics.h"
#include "AbilitySystemComponent.h"
#include "Engine/OverlapResult.h"


void UAbilityTask_GrantHacking::Activate() {
	SetWaitingOnAvatar();

	UWorld* World = GetWorld();
	World->GetTimerManager().SetTimer(QueryTimerHandle, this, &ThisClass::QueryInteractables, HackingScanRate, true);
}

UAbilityTask_GrantHacking* UAbilityTask_GrantHacking::GrantAbilitiesForNearbyHackables(UGameplayAbility* OwningAbility, float HackingScanRange, float HackingScanRate) {
	auto* MyObj = NewAbilityTask<UAbilityTask_GrantHacking>(OwningAbility);
	MyObj->HackingScanRange = HackingScanRange;
	MyObj->HackingScanRate = HackingScanRate;
	return MyObj;
}

void UAbilityTask_GrantHacking::OnDestroy(bool AbilityEnded) {
	if (UWorld* World = GetWorld()) {
		World->GetTimerManager().ClearTimer(QueryTimerHandle);
	}

	Super::OnDestroy(AbilityEnded);
}

void UAbilityTask_GrantHacking::QueryInteractables() {
	UWorld* World = GetWorld();
	AActor* ActorOwner = GetAvatarActor();

	if (World && ActorOwner) {
		FCollisionQueryParams Params(SCENE_QUERY_STAT(UAbilityTask_GrantNearbyHacking), false);

		TArray<FOverlapResult> OverlapResults;															// @Eric TODO: #define Control_TraceChannel_hacking as ECC_EngineTraceChannel2 
		World->OverlapMultiByChannel(OUT OverlapResults, ActorOwner->GetActorLocation(), FQuat::Identity, ECC_EngineTraceChannel2 /*Control_TraceChannel_hacking*/, FCollisionShape::MakeSphere(HackingScanRange), Params);

		if (OverlapResults.Num() > 0) {
			TArray<TScriptInterface<IHackableTarget>> InteractableTargets;
			UHackingStatics::AppendHackableTargetsFromOverlapResults(OverlapResults, OUT InteractableTargets);

			FHackingQuery HackingQuery;
			HackingQuery.RequestingAvatar = ActorOwner;
			HackingQuery.RequestingController = Cast<AController>(ActorOwner->GetOwner());

			TArray<FHackingOption> Options;
			for (TScriptInterface<IHackableTarget>& InteractiveTarget : InteractableTargets) {
				FHackingOptionBuilder HackingBuilder(InteractiveTarget, Options);
				InteractiveTarget->GatherHackingOptions(HackingQuery, HackingBuilder);
			}

			// Check if any of the options need to grant the ability to the user before they can be used.
			for (FHackingOption& Option : Options) {
				if (Option.HackingAbilityToGrant) {
					// Grant the ability to the GAS, otherwise it won't be able to do whatever the interaction is.
					FObjectKey ObjectKey(Option.HackingAbilityToGrant);
					if (!HackingAbilityCache.Find(ObjectKey)) {
						FGameplayAbilitySpec Spec(Option.HackingAbilityToGrant, 1, INDEX_NONE, this);
						FGameplayAbilitySpecHandle Handle = AbilitySystemComponent->GiveAbility(Spec);
						HackingAbilityCache.Add(ObjectKey, Handle);
					}
				}
			}
		}
	}
}
