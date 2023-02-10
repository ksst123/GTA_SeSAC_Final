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

	// 02. SpringArm, Camera ����
	UPROPERTY(EditAnywhere)
	class USpringArmComponent* springArmComp;
	UPROPERTY(EditAnywhere)
	class UCameraComponent* cameraComp;

	// 04. �Է� ����
	void OnAxisHorizontal(float value);
	void OnAxisVertical(float value);
	void OnAxisLookUp(float value);
	void OnAxisTurnRight(float value);
	void OnActionJump();

	// 07. ������ ����
	FVector direction;
	float walkSpeed = 300;

	// �� �߰�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* myGunMeshComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* sniperMeshComp;

	//���콺 ���� ��ư�� ������ �Ѿ� ���忡�� �Ѿ��� ���� �ѱ� ��ġ�� ��ġ�ϰ� �ʹ�
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABullet>bulletFactory;

	// �ѽ�� �Է� �߰�
	void OnActionFirePressed();
	void OnActionFireReleased();
	void DoFire();

	// �󸶳� ���� �� ���̳�
	UPROPERTY(EditAnywhere)
	float fireInterval = 0.5f;
	FTimerHandle fireTimerHandle;

	// ������ �������� ���ΰ� ����
	bool bUsingFist = true;
	void ChangeToFist();
	void ChangeToPistol();
	void ChangeToSniper();

	// �������忡�� crosshair&sniper ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> crosshairFactory;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> sniperFactory;

	// �������� ����ִ� ������ ������
	UPROPERTY()
	class UUserWidget* crosshairUI;
	UPROPERTY()
	class UUserWidget* sniperUI;




};
