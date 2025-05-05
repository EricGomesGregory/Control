// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/ControlAbility_CharacterLook.h"
#include "Player/ControlPlayerInputInterface.h"
#include "GameFramework/Character.h"


bool UControlAbility_CharacterLook::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const {
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags)) {
		return false;
	}

	const ACharacter* Character = CastChecked<ACharacter>(ActorInfo->AvatarActor.Get(), ECastCheckedType::NullAllowed);
	return (Character != nullptr /*@Eric TODO: Check if character can move */);
}

void UControlAbility_CharacterLook::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) {
	if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo) == false) {
		return;
	}

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo)) {
		return;
	}

	ACharacter* Character = CastChecked<ACharacter>(ActorInfo->AvatarActor.Get());

	// Handles player input checking
	if (auto* PlayerInputInterface = Cast<IControlPlayerInputInterface>(Character)) {
		FVector2D ActionValue = PlayerInputInterface->GetMoveActionValue();

		if (ActionValue.IsZero()) return;

		const FRotator Rotation = Character->GetControlRotation();
		const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// Rotates current controlled character/pawn in the horizontal direction
		Character->AddControllerYawInput(ActionValue.X);
		// Rotates the camera of the current controlled character/pawn in the vertical direction
		Character->AddControllerPitchInput(-ActionValue.Y);
	}
}
