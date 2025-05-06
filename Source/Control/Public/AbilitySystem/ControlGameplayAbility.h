// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "ControlGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class CONTROL_API UControlGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, Category = "Control Protocol|Character|Player")
	void CharacterMove(FVector2D InActionValue);

	UFUNCTION(BlueprintCallable, Category = "Control Protocol|Character|Player")
	void CharacterLook(FVector2D InActionValue);
};
