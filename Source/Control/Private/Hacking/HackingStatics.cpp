// Fill out your copyright notice in the Description page of Project Settings.


#include "Hacking/HackingStatics.h"
#include "Hacking/HackableTarget.h"
#include "Engine/OverlapResult.h"


UHackingStatics::UHackingStatics()
{
}

AActor* UHackingStatics::GetActorFromHackableTarget(TScriptInterface<IHackableTarget> HackableTarget) {
	if (UObject* Object = HackableTarget.GetObject()) {
		if (AActor* Actor = Cast<AActor>(Object)) {
			return Actor;
		}
		else if (UActorComponent* ActorComponent = Cast<UActorComponent>(Object)) {
			return ActorComponent->GetOwner();
		}
		else {
			unimplemented();
		}
	}

	return nullptr;
}

void UHackingStatics::GetHackableTargetsFromActor(AActor* Actor, TArray<TScriptInterface<IHackableTarget>>& OutHackableTargets) {
	// If the actor is directly interactable, return that.
	TScriptInterface<IHackableTarget> HackableActor(Actor);
	if (HackableActor) {
		OutHackableTargets.Add(HackableActor);
	}

	// If the actor isn't hackable, it might have a component that has a hackable interface.
	TArray<UActorComponent*> HackableComponents = Actor ? Actor->GetComponentsByInterface(UHackableTarget::StaticClass()) : TArray<UActorComponent*>();
	for (UActorComponent* HackableComponent : HackableComponents) {
		OutHackableTargets.Add(TScriptInterface<IHackableTarget>(HackableComponent));
	}
}

void UHackingStatics::AppendHackableTargetsFromOverlapResults(const TArray<FOverlapResult>& OverlapResults, TArray<TScriptInterface<IHackableTarget>>& OutHackableTargets) {
	for (const FOverlapResult& Overlap : OverlapResults) {
		TScriptInterface<IHackableTarget> HackableActor(Overlap.GetActor());
		if (HackableActor) {
			OutHackableTargets.AddUnique(HackableActor);
		}

		TScriptInterface<IHackableTarget> HackableComponent(Overlap.GetComponent());
		if (HackableComponent) {
			OutHackableTargets.AddUnique(HackableComponent);
		}
	}
}

void UHackingStatics::AppendHackableTargetsFromHitResult(const FHitResult& HitResult, TArray<TScriptInterface<IHackableTarget>>& OutHackableTargets) {
	TScriptInterface<IHackableTarget> InteractableActor(HitResult.GetActor());
	if (InteractableActor) {
		OutHackableTargets.AddUnique(InteractableActor);
	}

	TScriptInterface<IHackableTarget> InteractableComponent(HitResult.GetComponent());
	if (InteractableComponent) {
		OutHackableTargets.AddUnique(InteractableComponent);
	}
}
