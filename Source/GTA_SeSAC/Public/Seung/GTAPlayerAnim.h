// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GTAPlayerAnim.generated.h"

/**
 * 
 */
UCLASS()
class GTA_SESAC_API UGTAPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerAnim)
	float speed = 0;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

};
