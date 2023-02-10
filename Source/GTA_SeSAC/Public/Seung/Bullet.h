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

	// 충돌 컴포넌트
	UPROPERTY (EditAnywhere, BlueprintReadWrite)
	class USphereComponent* sphereComp;
	// 외관 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* meshComp;
	// 이동 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UProjectileMovementComponent* movementComp;
	// 총알 없애기
	UFUNCTION()
	void OnDie();




};
