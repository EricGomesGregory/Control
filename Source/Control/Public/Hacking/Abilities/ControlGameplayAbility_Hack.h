// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hacking/HackingTypes.h"
#include "AbilitySystem/ControlGameplayAbility.h"
#include "ControlGameplayAbility_Hack.generated.h"

/**
 * 
 */
UCLASS()
class CONTROL_API UControlGameplayAbility_Hack : public UControlGameplayAbility
{
	GENERATED_BODY()

public:
	UControlGameplayAbility_Hack(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintCallable)
	void UpdateHackings(const TArray<FHackingOption>& HackingOptions);

	UFUNCTION(BlueprintCallable)
	void TriggerHacking();


protected:
	UPROPERTY(BlueprintReadWrite)
	TArray<FHackingOption> CurrentOptions;

	// @Eric TODO: Handle UI indicator like Lyra?
	// UPROPERTY()
	// TArray<TObjectPtr<UIndicatorDescriptor>> Indicators;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Control Protocol|Hacking")
	float HackingScanRate = 0.2f;

	UPROPERTY(EditDefaultsOnly, Category = "Control Protocol|Hacking")
	float HackingScanRange = 1000;

	UPROPERTY(EditDefaultsOnly, Category = "Control Protocol|Hacking")
	TSoftClassPtr<UUserWidget> DefaultHackingWidgetClass;
};
