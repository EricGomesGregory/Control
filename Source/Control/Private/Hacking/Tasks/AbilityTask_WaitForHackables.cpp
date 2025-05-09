// Fill out your copyright notice in the Description page of Project Settings.


#include "Hacking/Tasks/AbilityTask_WaitForHackables.h"
#include "Hacking/HackableTarget.h"
#include "AbilitySystemComponent.h"


void UAbilityTask_WaitForHackables::LineTrace(FHitResult& OutHitResult, const UWorld* World, const FVector& Start, const FVector& End, FName ProfileName, const FCollisionQueryParams Params) {
	check(World);

	OutHitResult = FHitResult();
	TArray<FHitResult> HitResults;
	World->LineTraceMultiByProfile(HitResults, Start, End, ProfileName, Params);

	OutHitResult.TraceStart = Start;
	OutHitResult.TraceEnd = End;

	if (HitResults.Num() > 0) {
		OutHitResult = HitResults[0];
	}
}

void UAbilityTask_WaitForHackables::AimWithPlayerController(const AActor* InSourceActor, FCollisionQueryParams Params, const FVector& TraceStart, float MaxRange, FVector& OutTraceEnd, bool bIgnorePitch) const {
	if (!Ability) { // Server and launching client only
		return;
	}

	APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get();
	check(PC);

	FVector ViewStart;
	FRotator ViewRot;
	PC->GetPlayerViewPoint(ViewStart, ViewRot);

	const FVector ViewDir = ViewRot.Vector();
	FVector ViewEnd = ViewStart + (ViewDir * MaxRange);

	ClipCameraRayToAbilityRange(ViewStart, ViewDir, TraceStart, MaxRange, ViewEnd);

	FHitResult HitResult;
	LineTrace(HitResult, InSourceActor->GetWorld(), ViewStart, ViewEnd, TraceProfile.Name, Params);

	const bool bUseTraceResult = HitResult.bBlockingHit && (FVector::DistSquared(TraceStart, HitResult.Location) <= (MaxRange * MaxRange));

	const FVector AdjustedEnd = (bUseTraceResult) ? HitResult.Location : ViewEnd;

	FVector AdjustedAimDir = (AdjustedEnd - TraceStart).GetSafeNormal();
	if (AdjustedAimDir.IsZero()) {
		AdjustedAimDir = ViewDir;
	}

	if (!bTraceAffectsAimPitch && bUseTraceResult) {
		FVector OriginalAimDir = (ViewEnd - TraceStart).GetSafeNormal();

		if (!OriginalAimDir.IsZero()) {
			// Convert to angles and use original pitch
			const FRotator OriginalAimRot = OriginalAimDir.Rotation();

			FRotator AdjustedAimRot = AdjustedAimDir.Rotation();
			AdjustedAimRot.Pitch = OriginalAimRot.Pitch;

			AdjustedAimDir = AdjustedAimRot.Vector();
		}
	}

	OutTraceEnd = TraceStart + (AdjustedAimDir * MaxRange);
}

bool UAbilityTask_WaitForHackables::ClipCameraRayToAbilityRange(FVector CameraLocation, FVector CameraDirection, FVector AbilityCenter, float AbilityRange, FVector& ClippedPosition) {
	FVector CameraToCenter = AbilityCenter - CameraLocation;
	float DotToCenter = FVector::DotProduct(CameraToCenter, CameraDirection);
	
	//If this fails, we're pointed away from the center, but we might be inside the sphere and able to find a good exit point.
	if (DotToCenter >= 0) {
		float DistanceSquared = CameraToCenter.SizeSquared() - (DotToCenter * DotToCenter);
		float RadiusSquared = (AbilityRange * AbilityRange);
		if (DistanceSquared <= RadiusSquared) {
			float DistanceFromCamera = FMath::Sqrt(RadiusSquared - DistanceSquared);
			float DistanceAlongRay = DotToCenter + DistanceFromCamera;						//Subtracting instead of adding will get the other intersection point
			ClippedPosition = CameraLocation + (DistanceAlongRay * CameraDirection);		//Cam aim point clipped to range sphere
			return true;
		}
	}

	return false;
}

void UAbilityTask_WaitForHackables::UpdateHackableOptions(const FHackingQuery& InteractQuery, const TArray<TScriptInterface<IHackableTarget>>& HackableTargets) {
	TArray<FHackingOption> NewOptions;

	for (const TScriptInterface<IHackableTarget>& HackingTarget : HackableTargets) {
		TArray<FHackingOption> TempOptions;
		FHackingOptionBuilder HackingBuilder(HackingTarget, TempOptions);
		HackingTarget->GatherHackingOptions(InteractQuery, HackingBuilder);

		for (FHackingOption& Option : TempOptions) {
			FGameplayAbilitySpec* HackingAbilitySpec = nullptr;

			// if there is a handle an a target ability system, we're triggering the ability on the target.
			if (Option.TargetAbilitySystem && Option.TargetHackingAbilityHandle.IsValid()) {
				// Find the spec
				HackingAbilitySpec = Option.TargetAbilitySystem->FindAbilitySpecFromHandle(Option.TargetHackingAbilityHandle);
			}
			// If there's an interaction ability then we're activating it on ourselves.
			else if (Option.HackingAbilityToGrant) {
				// Find the spec
				HackingAbilitySpec = AbilitySystemComponent->FindAbilitySpecFromClass(Option.HackingAbilityToGrant);

				if (HackingAbilitySpec) {
					// update the option
					Option.TargetAbilitySystem = AbilitySystemComponent.Get();
					Option.TargetHackingAbilityHandle = HackingAbilitySpec->Handle;
				}
			}

			if (HackingAbilitySpec) {
				// Filter any options that we can't activate right now for whatever reason.
				if (HackingAbilitySpec->Ability->CanActivateAbility(HackingAbilitySpec->Handle, AbilitySystemComponent->AbilityActorInfo.Get())) {
					NewOptions.Add(Option);
				}
			}
		}
	}

	bool bOptionsChanged = false;
	if (NewOptions.Num() == CurrentOptions.Num()) {
		NewOptions.Sort();

		for (int OptionIndex = 0; OptionIndex < NewOptions.Num(); OptionIndex++) {
			const FHackingOption& NewOption = NewOptions[OptionIndex];
			const FHackingOption& CurrentOption = CurrentOptions[OptionIndex];

			if (NewOption != CurrentOption) {
				bOptionsChanged = true;
				break;
			}
		}
	}
	else {
		bOptionsChanged = true;
	}

	if (bOptionsChanged) {
		CurrentOptions = NewOptions;
		HackableObjectsChanged.Broadcast(CurrentOptions);
	}
}
