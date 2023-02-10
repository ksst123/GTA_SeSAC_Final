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
	// 플레이어 이동속도 설정
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Player02Anim)
	float speed = 0;

	
	
	// 매 프레임 갱신되는 함수
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	// 플레이어가 공중에 있는지 여부
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Player02Anim)
	bool isInAir = false;

};
