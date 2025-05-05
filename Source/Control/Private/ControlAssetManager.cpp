// Fill out your copyright notice in the Description page of Project Settings.


#include "ControlAssetManager.h"
#include "ControlGameplayTags.h"

const UControlAssetManager& UControlAssetManager::Get() {
	checkf(GEngine, TEXT("Global Engine is invalid!"));

	auto* SpaceboundAssetManager = CastChecked<UControlAssetManager>(GEngine->AssetManager);
	return *SpaceboundAssetManager;
}

void UControlAssetManager::StartInitialLoading() {
	Super::StartInitialLoading();

	FControlGameplayTags::InitializeNativeGameplayTags();
}
