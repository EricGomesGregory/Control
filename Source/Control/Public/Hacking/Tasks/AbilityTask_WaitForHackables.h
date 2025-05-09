// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hacking/HackingTypes.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_WaitForHackables.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHackableObjectsChangedEvent, const TArray<FHackingOption>&, HackableOptions);

/**  */
UCLASS(Abstract)
class CONTROL_API UAbilityTask_WaitForHackables : public UAbilityTask
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
	FHackableObjectsChangedEvent HackableObjectsChanged;

protected:

	static void LineTrace(FHitResult& OutHitResult, const UWorld* World, const FVector& Start, const FVector& End, FName ProfileName, const FCollisionQueryParams Params);

	void AimWithPlayerController(const AActor* InSourceActor, FCollisionQueryParams Params, const FVector& TraceStart, float MaxRange, FVector& OutTraceEnd, bool bIgnorePitch = false) const;

	static bool ClipCameraRayToAbilityRange(FVector CameraLocation, FVector CameraDirection, FVector AbilityCenter, float AbilityRange, FVector& ClippedPosition);

	void UpdateHackableOptions(const FHackingQuery& InteractQuery, const TArray<TScriptInterface<IHackableTarget>>& HackableTargets);

	FCollisionProfileName TraceProfile;

	// Does the trace affect the aiming pitch
	bool bTraceAffectsAimPitch = true;

	TArray<FHackingOption> CurrentOptions;
};
