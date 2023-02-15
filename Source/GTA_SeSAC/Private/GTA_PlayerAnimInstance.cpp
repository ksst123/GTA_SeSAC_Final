// Fill out your copyright notice in the Description page of Project Settings.


#include "GTA_PlayerAnimInstance.h"
#include "GTA_Player.h"
#include "GameFramework/CharacterMovementComponent.h"

void UGTA_PlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ownerPlayer = Cast<AGTA_Player>(TryGetPawnOwner());

	if (ownerPlayer != nullptr)
	{
		FVector velocity = ownerPlayer->GetVelocity();
		Speed = FVector::DotProduct(ownerPlayer->GetActorForwardVector(), velocity);

		bIsJumping = ownerPlayer->GetCharacterMovement()->IsFalling();
	}
}

void UGTA_PlayerAnimInstance::AnimNotify_JapEnd()
{
}

void UGTA_PlayerAnimInstance::AnimNotify_StraightEnd()
{
}

void UGTA_PlayerAnimInstance::AnimNotify_DamagedJapEnd()
{
}

void UGTA_PlayerAnimInstance::AnimNotify_DamagedStraightEnd()
{
}

void UGTA_PlayerAnimInstance::AnimNotify_DamagedFistDie()
{
}
