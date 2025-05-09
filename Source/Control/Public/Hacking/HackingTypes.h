// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "HackingTypes.generated.h"



class IHackableTarget;
class UUserWidget;


/**  */
USTRUCT(BlueprintType)
struct FHackingQuery
{
	GENERATED_BODY()

public:
	/** The requesting pawn. */
	UPROPERTY(BlueprintReadWrite)
	TWeakObjectPtr<AActor> RequestingAvatar;

	/** Allow us to specify a controller - does not need to match the owner of the requesting avatar. */
	UPROPERTY(BlueprintReadWrite)
	TWeakObjectPtr<AController> RequestingController;

	/** A generic UObject to shove in extra data required for the hacking */
	UPROPERTY(BlueprintReadWrite)
	TWeakObjectPtr<UObject> OptionalObjectData;
};


/**  */
USTRUCT(BlueprintType)
struct FHackingOption
{
	GENERATED_BODY()

public:
	/** The hackable target */
	UPROPERTY(BlueprintReadWrite)
	TScriptInterface<IHackableTarget> HackableTarget = nullptr;

	/** Simple text the hacking might return */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Text = FText();

	/** Simple sub-text the hacking might return */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText SubText = FText();

	// METHODS OF HACKING
	//--------------------------------------------------------------

	// 1) Place an ability on the avatar that they can activate when they perform hacking.

	/** The ability to grant the avatar when they get near interactable objects. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGameplayAbility> HackingAbilityToGrant;

	// - OR -

	// 2) Allow the object we're interacting with to have its own ability system and hacking ability, that we can activate instead.

	/** The ability system on the target that can be used for the TargetHackingHandle and sending the event, if needed. */
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UAbilitySystemComponent> TargetAbilitySystem = nullptr;

	/** The ability spec to activate on the object for this option. */
	UPROPERTY(BlueprintReadOnly)
	FGameplayAbilitySpecHandle TargetHackingAbilityHandle;

	// UI
	//--------------------------------------------------------------

	/** The widget to show for this kind of hacking. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftClassPtr<UUserWidget> HackingWidgetClass;

	// Methods
	//--------------------------------------------------------------

public:
	FORCEINLINE bool operator==(const FHackingOption& Other) const {
		return HackableTarget == Other.HackableTarget &&
			HackingAbilityToGrant == Other.HackingAbilityToGrant &&
			TargetAbilitySystem == Other.TargetAbilitySystem &&
			TargetHackingAbilityHandle == Other.TargetHackingAbilityHandle &&
			HackingWidgetClass == Other.HackingWidgetClass &&
			Text.IdenticalTo(Other.Text) &&
			SubText.IdenticalTo(Other.SubText);
	}

	FORCEINLINE bool operator!=(const FHackingOption& Other) const {
		return !operator==(Other);
	}

	FORCEINLINE bool operator<(const FHackingOption& Other) const {
		return HackableTarget.GetInterface() < Other.HackableTarget.GetInterface();
	}
};