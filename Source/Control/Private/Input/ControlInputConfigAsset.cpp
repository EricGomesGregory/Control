// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/ControlInputConfigAsset.h"

const UInputAction* UControlInputConfigAsset::FindAbilityInputActionForTag(const FGameplayTag& Tag, bool bLogNotFound) const {
	for (const auto& Action : AbilityInputActions) {
		if (Action.InputAction && Action.InputTag == Tag) {
			return Action.InputAction;
		}
	}
	if (bLogNotFound) {
		UE_LOG(LogTemp, Error, TEXT("Unable to find AbilityInputAction for InputTag: %s, on InputConfig: %s"), *Tag.ToString(), *GetNameSafe(this));
	}
	return nullptr;
}
