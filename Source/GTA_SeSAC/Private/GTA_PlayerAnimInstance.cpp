// Fill out your copyright notice in the Description page of Project Settings.


#include "GTA_PlayerAnimInstance.h"
#include "GTA_Player.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SphereComponent.h"

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

void UGTA_PlayerAnimInstance::AnimNotify_Jap()
{
	ownerPlayer->LeftFistCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UGTA_PlayerAnimInstance::AnimNotify_Straight()
{
	ownerPlayer->RightFistCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UGTA_PlayerAnimInstance::AnimNotify_DamagedStraightEnd()
{
}
