// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class GTA_SESAC_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsJumping;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	bool bIsFighting = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	bool bHasGun = false;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim Montages")
	class UAnimMontage* PunchJap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim Montages")
	class UAnimMontage* PunchStraight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim Montages")
	class UAnimMontage* EnteringCar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim Montages")
	class UAnimMontage* ExitingCar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim Montages")
	class UAnimMontage* DrivingCar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim Montages")
	class UAnimMontage* PistolReload;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim Montages")
	class UAnimMontage* Damaged;

	UPROPERTY()
	class AYohanCharacter* owner;

	UFUNCTION()
	void AnimNotify_JapEnd();

	UFUNCTION()
	void AnimNotify_StraightEnd();

	UFUNCTION()
	void AnimNotify_DamagedJapEnd();

	UFUNCTION()
	void AnimNotify_DamagedStraightEnd();

	UFUNCTION()
	void AnimNotify_DamagedFistDie();
};
