// Fill out your copyright notice in the Description page of Project Settings.


#include "Seung/GTAPlayer01Anim.h"
#include "Seung/GTAPlayer01.h"
#include <GameFramework/CharacterMovementComponent.h>


void UGTAPlayer01Anim::NativeUpdateAnimation(float DeltaSeconds)
{
	// 01. 소유 폰 가져오기
	auto ownerPawn = TryGetPawnOwner();
	// 02. 플레이어의 전방 벡터가 필요
	auto player = Cast<AGTAPlayer01>(ownerPawn);
	// 캐스팅 성공했다면
	if (player)
	{
		// 03. 이동 속도가 필요
		FVector velocity = player->GetVelocity();
		// 04. 플레이어의 전방 벡터가 필요
		FVector forwardVector = player->GetActorForwardVector();
		// 05. speed에 값(내적) 할당하기
		speed = FVector::DotProduct(forwardVector, velocity);
		// 06. 좌우 속도 할당하기
		FVector rightVector = player->GetActorRightVector();
		direction = FVector::DotProduct(rightVector, velocity);

		//플레이어가 현재 공중에 있는지 여부를 기억하고 싶다
		auto movement = player->GetCharacterMovement();
		isInAir = movement->IsFalling();
	}
}
