// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "Characters/ControlPlayableCharacterTypes.h"
#include "ControlPlayerState.generated.h"

class UAttributeSet;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FControlPlayerState_PossessedDelegate, FControlPlayableCharacterData&, NewCharacterData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FControlPlayerState_UnPossessedDelegate, FControlPlayableCharacterData&, OldCharacterData);

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

	void PossessedCharacter(FControlPlayableCharacterData& CharacterData);
	void UnPossessedCharacter();

public:
	UPROPERTY()
	FControlPlayerState_PossessedDelegate OnPossessed;
	
	UPROPERTY(BlueprintAssignable)
	FControlPlayerState_UnPossessedDelegate OnUnPossessed;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control Protocol")
	FText CharacterName;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

};
