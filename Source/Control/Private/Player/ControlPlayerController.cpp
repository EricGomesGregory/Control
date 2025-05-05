// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ControlPlayerController.h"
#include "AbilitySystem/ControlAbilitySystemComponent.h"
#include "Input/ControlEnhancedInputComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"


AControlPlayerController::AControlPlayerController(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer) {
}

void AControlPlayerController::BeginPlay() {
	Super::BeginPlay();

	check(InputContext);

	auto* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem) {
		Subsystem->AddMappingContext(InputContext, 0);
	}
}

void AControlPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();

	auto* ControlInputComponent = CastChecked<UControlEnhancedInputComponent>(InputComponent);

	// Binds Ability actions based on config
	ControlInputComponent->
		BindAbilityActions(InputConfig, this, 
			&ThisClass::AbilityInputTagPressed, 
			&ThisClass::AbilityInputTagReleased, 
			&ThisClass::AbilityInputTagHeld);
}

UControlAbilitySystemComponent* AControlPlayerController::GetAbilitySystemComponent() {
	if (AbilitySystemComponent == nullptr) {
		auto* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>());
		AbilitySystemComponent = Cast<UControlAbilitySystemComponent>(ASC);
	}
	return AbilitySystemComponent;
}

void AControlPlayerController::AbilityInputTagPressed(FGameplayTag InputTag) {
	GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Green, TEXT("Pressed: " + InputTag.ToString()));
	if (GetAbilitySystemComponent() == nullptr) return;
	GetAbilitySystemComponent()->AbilityInputTagPressed(InputTag);
}

void AControlPlayerController::AbilityInputTagReleased(FGameplayTag InputTag) {
	GEngine->AddOnScreenDebugMessage(2, 1.f, FColor::Green, TEXT("Released: " + InputTag.ToString()));
	
	if (GetAbilitySystemComponent() == nullptr) return;
	GetAbilitySystemComponent()->AbilityInputTagReleased(InputTag);
}

void AControlPlayerController::AbilityInputTagHeld(FGameplayTag InputTag) {
	GEngine->AddOnScreenDebugMessage(3, 1.f, FColor::Green, TEXT("Held: " + InputTag.ToString()));
	
	if (GetAbilitySystemComponent() == nullptr) return;
	GetAbilitySystemComponent()->AbilityInputTagHeld(InputTag);
}


