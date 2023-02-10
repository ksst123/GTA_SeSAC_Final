// Fill out your copyright notice in the Description page of Project Settings.


#include "Seung/GTAPlayer01Anim.h"
#include "Seung/GTAPlayer01.h"
#include <GameFramework/CharacterMovementComponent.h>


void UGTAPlayer01Anim::NativeUpdateAnimation(float DeltaSeconds)
{
	// 01. ���� �� ��������
	auto ownerPawn = TryGetPawnOwner();
	// 02. �÷��̾��� ���� ���Ͱ� �ʿ�
	auto player = Cast<AGTAPlayer01>(ownerPawn);
	// ĳ���� �����ߴٸ�
	if (player)
	{
		// 03. �̵� �ӵ��� �ʿ�
		FVector velocity = player->GetVelocity();
		// 04. �÷��̾��� ���� ���Ͱ� �ʿ�
		FVector forwardVector = player->GetActorForwardVector();
		// 05. speed�� ��(����) �Ҵ��ϱ�
		speed = FVector::DotProduct(forwardVector, velocity);
		// 06. �¿� �ӵ� �Ҵ��ϱ�
		FVector rightVector = player->GetActorRightVector();
		direction = FVector::DotProduct(rightVector, velocity);

		//�÷��̾ ���� ���߿� �ִ��� ���θ� ����ϰ� �ʹ�
		auto movement = player->GetCharacterMovement();
		isInAir = movement->IsFalling();
	}
}
