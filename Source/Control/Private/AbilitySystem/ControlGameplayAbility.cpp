// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ControlGameplayAbility.h"
#include "GameFramework/Character.h"


void UControlGameplayAbility::CharacterMove(FVector2D InActionValue) {
	if (InActionValue.IsZero()) return;

	auto* ControlledCharacter = CastChecked<ACharacter>(GetAvatarActorFromActorInfo());
	const FRotator Rotation = ControlledCharacter->GetControlRotation();
	const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// Moves current controlled character/pawn in the forward direction
	ControlledCharacter->AddMovementInput(ForwardDirection, InActionValue.Y);
	
	// Moves current controlled character/pawn in the right direction
	ControlledCharacter->AddMovementInput(RightDirection, InActionValue.X);
}

void UControlGameplayAbility::CharacterLook(FVector2D InActionValue) {
	if (InActionValue.IsZero()) return;

	auto* ControlledCharacter = CastChecked<ACharacter>(GetAvatarActorFromActorInfo());
	
	// Rotates current controlled character/pawn in the horizontal direction
	ControlledCharacter->AddControllerYawInput(InActionValue.X);
	
	// Rotates current controlled character/pawn vision in the vertical direction
	ControlledCharacter->AddControllerPitchInput(-InActionValue.Y);
}
