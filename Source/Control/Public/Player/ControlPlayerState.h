// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "ControlPlayerState.generated.h"

class UAttributeSet;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAbilitySystemComponentChanged, UAbilitySystemComponent*, InASC, UAbilitySystemComponent*, OldASC);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAttributeSetChanged, UAttributeSet*, InAttributeSet, UAttributeSet*, OldAttributeSet);

/**
 * 
 */
UCLASS()
class CONTROL_API AControlPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	AControlPlayerState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	//~IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSet() const;
	//~End IAbilitySystemInterface

	void SetAbilitySystemComponent(UAbilitySystemComponent* InASC);
	
	void SetAttributeSet(UAttributeSet* InAttributeSet);

public:
	UPROPERTY()
	FAbilitySystemComponentChanged OnAbilitySystemComponentChanged;

	UPROPERTY()
	FAttributeSetChanged OnAttributeSetChanged;

protected:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

};
