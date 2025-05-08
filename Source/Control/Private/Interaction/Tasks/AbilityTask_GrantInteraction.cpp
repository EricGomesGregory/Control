// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/Tasks/AbilityTask_GrantInteraction.h"
#include "Interaction/InteractableTarget.h"
#include "Interaction/InteractionStatics.h"
#include "AbilitySystemComponent.h"


UAbilityTask_GrantInteraction::UAbilityTask_GrantInteraction(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer) {

}

void UAbilityTask_GrantInteraction::Activate() {
	SetWaitingOnAvatar();

	UWorld* World = GetWorld();
	World->GetTimerManager().SetTimer(QueryTimerHandle, this, &ThisClass::QueryInteractables, InteractionScanRate, true);
}

UAbilityTask_GrantInteraction* UAbilityTask_GrantInteraction::GrantAbilitiesForNearbyInteractors(UGameplayAbility* OwningAbility, float InteractionScanRange, float InteractionScanRate) {
	UAbilityTask_GrantInteraction* MyObj = NewAbilityTask<UAbilityTask_GrantInteraction>(OwningAbility);
	MyObj->InteractionScanRange = InteractionScanRange;
	MyObj->InteractionScanRate = InteractionScanRate;
	return MyObj;
}

void UAbilityTask_GrantInteraction::OnDestroy(bool AbilityEnded) {
	if (UWorld* World = GetWorld()) {
		World->GetTimerManager().ClearTimer(QueryTimerHandle);
	}

	Super::OnDestroy(AbilityEnded);
}

void UAbilityTask_GrantInteraction::QueryInteractables() {
	UWorld* World = GetWorld();
	AActor* ActorOwner = GetAvatarActor();

	if (World && ActorOwner) {
		FCollisionQueryParams Params(SCENE_QUERY_STAT(UAbilityTask_GrantInteraction), false);

		// @Eric TODO: Fix error C2139: 'FOverlapResult': an undefined class is not allowed as an argument to compiler intrinsic type trait '__is_trivially_destructible'
		//TArray<FOverlapResult> OverlapResults;
		//World->OverlapMultiByChannel(OUT OverlapResults, ActorOwner->GetActorLocation(), FQuat::Identity, ECC_EngineTraceChannel1 /*Control_TraceChannel_Interaction*/, FCollisionShape::MakeSphere(InteractionScanRange), Params);
		//
		//if (OverlapResults.Num() <= 0) {
		//	return;
		//}

		//TArray<TScriptInterface<IInteractableTarget>> InteractableTargets;
		//UInteractionStatics::AppendInteractableTargetsFromOverlapResults(OverlapResults, OUT InteractableTargets);

		//FInteractionQuery InteractionQuery;
		//InteractionQuery.RequestingAvatar = ActorOwner;
		//InteractionQuery.RequestingController = Cast<AController>(ActorOwner->GetOwner());

		//TArray<FInteractionOption> Options;
		//for (TScriptInterface<IInteractableTarget>& InteractiveTarget : InteractableTargets) {
		//	FInteractionOptionBuilder InteractionBuilder(InteractiveTarget, Options);
		//	InteractiveTarget->GatherInteractionOptions(InteractionQuery, InteractionBuilder);
		//}

		//// Check if any of the options need to grant the ability to the user before they can be used.
		//for (FInteractionOption& Option : Options) {
		//	if (Option.InteractionAbilityToGrant) {
		//		// Grant the ability to the GAS, otherwise it won't be able to do whatever the interaction is.
		//		FObjectKey ObjectKey(Option.InteractionAbilityToGrant);
		//		if (!InteractionAbilityCache.Find(ObjectKey)) {
		//			FGameplayAbilitySpec Spec(Option.InteractionAbilityToGrant, 1, INDEX_NONE, this);
		//			FGameplayAbilitySpecHandle Handle = AbilitySystemComponent->GiveAbility(Spec);
		//			InteractionAbilityCache.Add(ObjectKey, Handle);
		//		}
		//	}
		//}
	}
}
