// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GTAPlayer01Anim.generated.h"

/**
 * 
 */
UCLASS()
class GTA_SESAC_API UGTAPlayer01Anim : public UAnimInstance
{
	GENERATED_BODY()
	

public:
	// �÷��̾� �̵��ӵ� ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Player01Anim)
	float speed = 0;
	// �÷��̾� �¿� �̵� �ӵ�
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerAnim)
	float direction = 0;


	// �� ������ ���ŵǴ� �Լ�
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	// �÷��̾ ���߿� �ִ��� ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Player01Anim)
	bool isInAir = false;

};

