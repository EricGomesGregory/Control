// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ControlPlayerCharacterInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UControlPlayerCharacterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CONTROL_API IControlPlayerCharacterInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Control Protocol|Player Character")
	FVector GetCameraPosition();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Control Protocol|Player Character")
	FVector GetCameraForward();
};
