// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GTAPlayer02.generated.h"

UCLASS()
class GTA_SESAC_API AGTAPlayer02 : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGTAPlayer02();

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
	void OnAxisHorizontal(float value);
	void OnAxisVertical(float value);
	void OnAxisLookUp(float value);
	void OnAxisTurnRight(float value);
	void OnActionJump();

	// 07. 움직임 설정
	FVector direction;
	float walkSpeed = 300;

	// 총 추가
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* myGunMeshComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* sniperMeshComp;

	//마우스 왼쪽 버튼을 누르면 총알 공장에서 총알을 만들어서 총구 위치에 배치하고 싶다
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABullet>bulletFactory;

	// 총쏘기 입력 추가
	void OnActionFirePressed();
	void OnActionFireReleased();
	void DoFire();

	// 얼마나 총을 쏠 것이냐
	UPROPERTY(EditAnywhere)
	float fireInterval = 0.5f;
	FTimerHandle fireTimerHandle;

	// 무엇을 갖고있을 것인가 변수
	bool bUsingFist = true;
	void ChangeToFist();
	void ChangeToPistol();
	void ChangeToSniper();

	// 위젯공장에서 crosshair&sniper 위젯 생성
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> crosshairFactory;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> sniperFactory;

	// 공장결과를 담고있는 포인터 변수들
	UPROPERTY()
	class UUserWidget* crosshairUI;
	UPROPERTY()
	class UUserWidget* sniperUI;




};
