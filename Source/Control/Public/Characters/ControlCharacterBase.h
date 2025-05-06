// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "ControlCharacterBase.generated.h"

class UAttributeSet;
class UGameplayEffect;
class UControlCharacterDefinition;


UCLASS(Abstract)
class CONTROL_API AControlCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AControlCharacterBase();

	//~IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSet() const;
	//~End IAbilitySystemInterface

public:
	static FName AbilitySystemComponentName;

	static FName AttributeSetName;

protected:
	virtual void InitAbilityActorInfo() {};

	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> Effect, float level = 1.f) const;

protected:
	UPROPERTY(EditAnywhere, Category = "Control Protocol|Character")
	TObjectPtr<UControlCharacterDefinition> CharacterDefinition;

	UPROPERTY(VisibleAnywhere, Category = "Control Protocol|Ability System")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
