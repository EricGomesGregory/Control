// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HackingStatics.generated.h"

class IHackableTarget;

/**
 * 
 */
UCLASS()
class CONTROL_API UHackingStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UHackingStatics();

public:
	UFUNCTION(BlueprintCallable)
	static AActor* GetActorFromHackableTarget(TScriptInterface<IHackableTarget> HackableTarget);

	UFUNCTION(BlueprintCallable)
	static void GetHackableTargetsFromActor(AActor* Actor, TArray<TScriptInterface<IHackableTarget>>& OutHackableTargets);

	static void AppendHackableTargetsFromOverlapResults(const TArray<FOverlapResult>& OverlapResults, TArray<TScriptInterface<IHackableTarget>>& OutHackableTargets);
	static void AppendHackableTargetsFromHitResult(const FHitResult& HitResult, TArray<TScriptInterface<IHackableTarget>>& OutHackableTargets);
};
