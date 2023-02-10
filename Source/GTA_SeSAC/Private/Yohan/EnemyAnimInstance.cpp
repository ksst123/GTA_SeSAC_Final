// Fill out your copyright notice in the Description page of Project Settings.


#include "Yohan/EnemyAnimInstance.h"
#include "Yohan/YohanCharacter.h"
#include "GameFrameWork/CharacterMovementComponent.h"
#include "Components/SphereComponent.h"
#include "AIController.h"

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	owner = Cast<AYohanCharacter>(TryGetPawnOwner());

	if (owner != nullptr)
	{
		FVector velocity = owner->GetVelocity();
		Speed = FVector::DotProduct(owner->GetActorForwardVector(), velocity);

		bIsJumping = owner->GetCharacterMovement()->IsFalling();
	}
}

void UEnemyAnimInstance::AnimNotify_JapEnd()
{


	owner->LeftFistCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UEnemyAnimInstance::AnimNotify_StraightEnd()
{

	owner->RightFistCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UEnemyAnimInstance::AnimNotify_DamagedJapEnd()
{	
	owner->CurrentHP -= owner->FistDamage;
	UE_LOG(LogTemp, Warning, TEXT("Jap -> %d"), owner->CurrentHP);
}

void UEnemyAnimInstance::AnimNotify_DamagedStraightEnd()
{

	owner->CurrentHP -= owner->FistDamage;
	UE_LOG(LogTemp, Warning, TEXT("Straight -> %d"), owner->CurrentHP);
}

void UEnemyAnimInstance::AnimNotify_DamagedFistDie()
{
	UE_LOG(LogTemp, Warning, TEXT("Dead"));
}
