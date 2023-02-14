// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GTA_PlayerBaseComponent.h"
#include "GTA_PlayerFireComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GTA_SESAC_API UGTA_PlayerFireComponent : public UGTA_PlayerBaseComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGTA_PlayerFireComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputAction* InputShoot;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputAction* InputAim;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputAction* InputReload;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Fire Settings")
	int32 PistolDamage = 10;


	UPROPERTY(EditAnywhere)
	class UUserWidget* CrosshairUI;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> CrosshairFactory;


	UPROPERTY(EditAnywhere, Category = "My Fire Settings")
	class UParticleSystem* BulletEffect;
	UPROPERTY(EditAnywhere, Category = "My Fire Settings")
	class UParticleSystem* PistolEffect;


	UPROPERTY(EditAnywhere)
	class USoundBase* PistolSound;


	void OnActionShoot();
	void OnActionReload();

	void DoFire();
};
