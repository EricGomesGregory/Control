// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ControlPlayableCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/ControlPlayerController.h"
#include "Camera/CameraComponent.h"


FName AControlPlayableCharacter::SpringArmComponentName(TEXT("Spring Arm"));
FName AControlPlayableCharacter::CameraComponentName(TEXT("Camera"));

AControlPlayableCharacter::AControlPlayableCharacter() {
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(SpringArmComponentName);
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 0.f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(CameraComponentName);
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->bUsePawnControlRotation = true;
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

void AControlPlayableCharacter::InitAbilityActorInfo() {
	if (auto* PlayerController = Cast<AControlPlayerController>(Controller)) {
		// @ Eric TODO: Handle player possession
	}
}
