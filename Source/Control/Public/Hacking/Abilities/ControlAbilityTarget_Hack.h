// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor_Trace.h"
#include "ControlAbilityTarget_Hack.generated.h"

/**
 * 
 */
UCLASS()
class CONTROL_API AControlAbilityTarget_Hack : public AGameplayAbilityTargetActor_Trace
{
	GENERATED_BODY()

public:
	AControlAbilityTarget_Hack(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual FHitResult PerformTrace(AActor* InSourceActor) override;

protected:

};
