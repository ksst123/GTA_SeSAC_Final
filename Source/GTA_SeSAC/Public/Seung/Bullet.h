// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class GTA_SESAC_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// �浹 ������Ʈ
	UPROPERTY (EditAnywhere, BlueprintReadWrite)
	class USphereComponent* sphereComp;
	// �ܰ� ������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* meshComp;
	// �̵� ������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UProjectileMovementComponent* movementComp;
	// �Ѿ� ���ֱ�
	UFUNCTION()
	void OnDie();




};
