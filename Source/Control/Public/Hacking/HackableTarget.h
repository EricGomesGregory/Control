// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTagContainer.h"
#include "Hacking/HackingTypes.h"
#include "HackableTarget.generated.h"


/**  */
class FHackingOptionBuilder
{
public:
	FHackingOptionBuilder(TScriptInterface<IHackableTarget> InterfaceTargetScope, TArray<FHackingOption>& InteractOptions)
		: Scope(InterfaceTargetScope), Options(InteractOptions) {
	}

	void AddHackingOption(const FHackingOption& Option)
	{
		FHackingOption& OptionEntry = Options.Add_GetRef(Option);
		OptionEntry.HackableTarget = Scope;
	}

private:
	TScriptInterface<IHackableTarget> Scope;
	TArray<FHackingOption>& Options;
};


UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UHackableTarget : public UInterface
{
	GENERATED_BODY()
};

/** */
class CONTROL_API IHackableTarget
{
	GENERATED_BODY()

public:
	/**  */
	virtual void GatherHackingOptions(const FHackingQuery& InteractQuery, FHackingOptionBuilder& OptionBuilder) = 0;

	/**  */
	virtual void CustomizeHackingEventData(const FGameplayTag& HackingEventTag, FGameplayEventData& InOutEventData) {}
};
