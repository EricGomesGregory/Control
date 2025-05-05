// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerController.h"
#include "ControlPlayerController.generated.h"

class UInputMappingContext;
class UControlInputConfigAsset;
class UControlAbilitySystemComponent;


/**
 * 
 */
UCLASS()
class CONTROL_API AControlPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AControlPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> InputContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UControlInputConfigAsset> InputConfig;

	UPROPERTY()
	TObjectPtr<UControlAbilitySystemComponent> AbilitySystemComponent;

	UControlAbilitySystemComponent* GetAbilitySystemComponent();
	

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);
};
