// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GTAPlayer.generated.h"

UCLASS()
class GTA_SESAC_API AGTAPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGTAPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	// 02. SpringArm, Camera ����
	UPROPERTY (EditAnywhere)
	class USpringArmComponent* springArmComp;
	UPROPERTY (EditAnywhere)
	class UCameraComponent* cameraComp;


	// 04. �Է� ����
	void OnAxisHorizontal (float value);
	void OnAxisVertical (float value);
	void OnAxisLookUp (float value);
	void OnAxisTurnRight (float value);
	void OnActionJump();


	// 07. ������ ����
	FVector direction;
	float walkSpeed = 300;

};
