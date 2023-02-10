// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GTAPlayer01.generated.h"

UCLASS()
class GTA_SESAC_API AGTAPlayer01 : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGTAPlayer01();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 02. SpringArm, Camera 선언
	UPROPERTY(EditAnywhere)
	class USpringArmComponent* springArmComp;
	UPROPERTY(EditAnywhere)
	class UCameraComponent* cameraComp;

	// 04. 입력 설정
	void OnAxisHorizontal (float value);
	void OnAxisVertical (float value);
	void OnAxisLookUp (float value);
	void OnAxisTurnRight (float value);
	void OnActionJump ();

	// 07. 움직임 설정
	FVector direction;
	float walkSpeed = 300;

};
