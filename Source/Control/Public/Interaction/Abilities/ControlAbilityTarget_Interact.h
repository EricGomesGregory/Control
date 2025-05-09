// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor_Trace.h"
#include "ControlAbilityTarget_Interact.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class CONTROL_API AControlAbilityTarget_Interact : public AGameplayAbilityTargetActor_Trace
{
	GENERATED_BODY()
	
public:
	AControlAbilityTarget_Interact(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual FHitResult PerformTrace(AActor* InSourceActor) override;

protected:

};
