// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GTAPlayer02Anim.generated.h"

/**
 * 
 */
UCLASS()
class GTA_SESAC_API UGTAPlayer02Anim : public UAnimInstance
{
	GENERATED_BODY()


public:
	// �÷��̾� �̵��ӵ� ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Player02Anim)
	float speed = 0;

	
	
	// �� ������ ���ŵǴ� �Լ�
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	// �÷��̾ ���߿� �ִ��� ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Player02Anim)
	bool isInAir = false;

};
