// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/InteractionTypes.h"
#include "AbilitySystem/ControlGameplayAbility.h"
#include "ControlGameplayAbility_Interact.generated.h"

/**
 * 
 */
UCLASS()
class CONTROL_API UControlGameplayAbility_Interact : public UControlGameplayAbility
{
	GENERATED_BODY()
	
public:
	UControlGameplayAbility_Interact(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintCallable)
	void UpdateInteractions(const TArray<FInteractionOption>& InteractiveOptions);

	UFUNCTION(BlueprintCallable)
	void TriggerInteraction();


protected:
	UPROPERTY(BlueprintReadWrite)
	TArray<FInteractionOption> CurrentOptions;

	// @Eric TODO: Handle UI indicator like Lyra?
	// UPROPERTY()
	// TArray<TObjectPtr<UIndicatorDescriptor>> Indicators;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Control Protocol|Interact")
	float InteractionScanRate = 0.1f;

	UPROPERTY(EditDefaultsOnly, Category = "Control Protocol|Interact")
	float InteractionScanRange = 500;

	UPROPERTY(EditDefaultsOnly, Category = "Control Protocol|Interact")
	TSoftClassPtr<UUserWidget> DefaultInteractionWidgetClass;
};
