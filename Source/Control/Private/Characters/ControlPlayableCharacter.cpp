// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ControlPlayableCharacter.h"
#include "Characters/ControlCharacterDefinition.h"
#include "AbilitySystem/ControlAbilitySystemComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/ControlPlayerController.h"
#include "Player/ControlPlayerState.h"
#include "Camera/CameraComponent.h"


FName AControlPlayableCharacter::SpringArmComponentName(TEXT("Spring Arm"));
FName AControlPlayableCharacter::CameraComponentName(TEXT("Camera"));

AControlPlayableCharacter::AControlPlayableCharacter() {
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(SpringArmComponentName);
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->TargetArmLength = 0.f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(CameraComponentName);
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void AControlPlayableCharacter::PossessedBy(AController* NewController) {
	Super::PossessedBy(NewController);

	/* Server Logic: Initializes ability system actor info and sets AbilitySystemComponent and attributeSet references */
	InitAbilityActorInfo();
}

void AControlPlayableCharacter::OnRep_PlayerState() {
	Super::OnRep_PlayerState();

	/* Client Logic: Initializes ability system actor info and sets AbilitySystemComponent and attributeSet references */
	InitAbilityActorInfo();
}

void AControlPlayableCharacter::UnPossessed() {
	if (auto* PlayerController = Cast<AControlPlayerController>(Controller)) {
		auto* GamePlayerState = CastChecked<AControlPlayerState>(GetPlayerState());
		
		GamePlayerState->UnPossessedCharacter();
	}
}

void AControlPlayableCharacter::BeginPlay() {
	Super::BeginPlay();

	CharacterDefinition->SetupCharacterGameplay(this);
}

void AControlPlayableCharacter::InitAbilityActorInfo() {
	if (auto* PlayerController = Cast<AControlPlayerController>(Controller)) {
		auto* GamePlayerState = CastChecked<AControlPlayerState>(GetPlayerState());
		/*
		AbilitySystemComponent = GamePlayerState->GetAbilitySystemComponent();
		AbilitySystemComponent->InitAbilityActorInfo(GamePlayerState, this);
		AttributeSet = GamePlayerState->GetAttributeSet();
		*/

		FControlPlayableCharacterData NewCharacterData;
		NewCharacterData.AbilitySystemComponent = AbilitySystemComponent;
		NewCharacterData.AttributeSet = AttributeSet;
		NewCharacterData.CharacterName = CharacterDefinition->GetCharacterName();

		GamePlayerState->PossessedCharacter(NewCharacterData);

	}
}
