// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "GameplayAbilitySpecHandle.h"
#include "ActiveGameplayEffectHandle.h"
#include "ControlAbilitySet.generated.h"

class UControlAbilitySystemComponent;
class UControlGameplayAbility;
class UGameplayEffect;
class UAttributeSet;


/**
 * FControlAbilitySet_GameplayAbility
 *
 * Data used by the ability set to grant gameplay abilities.
 */
USTRUCT(BlueprintType)
struct FControlAbilitySet_GameplayAbility
{
	GENERATED_BODY()

public:

	// Gameplay ability to grant.
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UControlGameplayAbility> Ability = nullptr;

	// Tag used to process input for the ability.
	UPROPERTY(EditDefaultsOnly, Meta = (Categories = "Input"))
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly)
	bool bCustomAbilityLevel = false;

	// Level of ability to grant.
	UPROPERTY(EditDefaultsOnly, meta = (EditCondition = "bCustomAbilityLevel", EditConditionHides))
	int32 AbilityLevel = 1;
};


/**
 * FControlAbilitySet_GameplayEffect
 *
 * Data used by the ability set to grant gameplay effects.
 */
USTRUCT(BlueprintType)
struct FControlAbilitySet_GameplayEffect
{
	GENERATED_BODY()

public:

	// Gameplay effect to grant.
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> GameplayEffect = nullptr;

	// Level of gameplay effect to grant.
	UPROPERTY(EditDefaultsOnly)
	float EffectLevel = 1.0f;
};

/**
 * FControlAbilitySet_AttributeSet
 *
 *	Data used by the ability set to grant attribute sets.
 */
USTRUCT(BlueprintType)
struct FControlAbilitySet_AttributeSet
{
	GENERATED_BODY()

public:
	// Gameplay effect to grant.
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAttributeSet> AttributeSet;

};

/**
 * FAbilitySet_GrantedHandles
 *
 * Data used to store handles to what has been granted by the ability set.
 */
USTRUCT(BlueprintType)
struct FAbilitySet_GrantedHandles
{
	GENERATED_BODY()

public:

	void AddAbilitySpecHandle(const FGameplayAbilitySpecHandle& Handle);
	void AddGameplayEffectHandle(const FActiveGameplayEffectHandle& Handle);
	void AddAttributeSet(UAttributeSet* Set);

	void TakeFromAbilitySystem(UControlAbilitySystemComponent* AbilitySystemComponent);

protected:

	// Handles to the granted abilities.
	UPROPERTY()
	TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;

	// Handles to the granted gameplay effects.
	UPROPERTY()
	TArray<FActiveGameplayEffectHandle> GameplayEffectHandles;

	// Pointers to the granted attribute sets
	UPROPERTY()
	TArray<TObjectPtr<UAttributeSet>> GrantedAttributeSets;
};

/**
 * 
 */
UCLASS()
class CONTROL_API UControlAbilitySet : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UControlAbilitySet(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// Grants the ability set to the specified ability system component.
	// The returned handles can be used later to take away anything that was granted.
	void GiveToAbilitySystem(UControlAbilitySystemComponent* AbilitySystemComponent, FAbilitySet_GrantedHandles* OutGrantedHandles, UObject* SourceObject = nullptr) const;

protected:
	// Gameplay abilities to grant when this ability set is granted.
	UPROPERTY(EditDefaultsOnly, Category = "Control Protocol|Gameplay Abilities", meta = (TitleProperty = Ability))
	TArray<FControlAbilitySet_GameplayAbility> GrantedGameplayAbilities;

	// Gameplay effects to grant when this ability set is granted.
	UPROPERTY(EditDefaultsOnly, Category = "Control Protocol|Gameplay Effects", meta = (TitleProperty = GameplayEffect))
	TArray<FControlAbilitySet_GameplayEffect> GrantedGameplayEffects;

	// Attribute sets to grant when this ability set is granted.
	UPROPERTY(EditDefaultsOnly, Category = "Control Protocol|Attribute Sets", meta = (TitleProperty = AttributeSet))
	TArray<FControlAbilitySet_AttributeSet> GrantedAttributes;
};
