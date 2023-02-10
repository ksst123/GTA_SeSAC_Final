// Fill out your copyright notice in the Description page of Project Settings.


#include "Seung/GTAPlayerAnim.h"
#include "Seung/GTAPlayer.h"

void UGTAPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	auto ownerPawn = TryGetPawnOwner();
	auto player = Cast<AGTAPlayer>(ownerPawn);

	if (player)
	{
		FVector velocity = player->GetVelocity();
		FVector forwardVector = player->GetActorForwardVector();

		speed = FVector::DotProduct(forwardVector, velocity);
	}
}
