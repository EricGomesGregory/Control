// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/ControlCharacterBase.h"
#include "Player/ControlPlayerInputInterface.h"
#include "Characters/ControlPlayerCharacterInterface.h"
#include "ControlPlayableCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;


/**
 * 
 */
UCLASS()
class CONTROL_API AControlPlayableCharacter : public AControlCharacterBase, 
	public IControlPlayerInputInterface, public IControlPlayerCharacterInterface
{
	GENERATED_BODY()
	
public:
	AControlPlayableCharacter();

	//~Begin APawn Interface
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	
	virtual void UnPossessed() override;
	//~End APawn Interface

	//~Begin AActor Interface
	virtual void BeginPlay() override;
	//~End AActor Interface

public:
	static FName SpringArmComponentName;
	static FName CameraComponentName;

protected:
	virtual void InitAbilityActorInfo() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCameraComponent> CameraComponent;

};
