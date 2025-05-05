// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "ControlPlayerState.generated.h"

class UAttributeSet;


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

public:
	static FName AbilitySystemComponentName;

	static FName AttributeSetName;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Control Protocol|Ability System")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

};
