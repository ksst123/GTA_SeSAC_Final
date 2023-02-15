// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GTA_PlayerBaseComponent.h"
#include "GTA_PlayerFightComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GTA_SESAC_API UGTA_PlayerFightComponent : public UGTA_PlayerBaseComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGTA_PlayerFightComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void SetupPlayerInput(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputAction* InputAim;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputAction* InputShoot;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputAction* InputJap;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputAction* InputStraight;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputAction* InputHand;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputAction* InputPistol;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputAction* InputReload;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentPistolAmmo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxPistolAmmo = 12;


	UPROPERTY(EditAnywhere)
	class UUserWidget* CrosshairUI;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> CrosshairFactory;


	UPROPERTY(EditAnywhere)
	class USoundBase* PunchSound;
	UPROPERTY(EditAnywhere)
	class USoundBase* PistolSound;


	UPROPERTY(EditAnywhere, Category = "My Character Settings")
	class UParticleSystem* BulletEffect;
	UPROPERTY(EditAnywhere, Category = "My Character Settings")
	class UParticleSystem* PistolEffect;


	UPROPERTY()
	class APistol* Pistol;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class APistol> PistolClass;


	UPROPERTY()
	bool bHasGun;
	UPROPERTY()
	bool bIsJap;
	UPROPERTY()
	bool bIsStraight;
	UPROPERTY()
	bool bIsDead;


	// ===========================================================================
	// ===========================================================================


	void OnActionAimPressed();
	void OnActionAimReleased();


	void OnActionJap();
	void OnActionStraight();
	void OnActionShoot();
	void DoFire();


	void OnActionReload();


	UFUNCTION(BlueprintCallable)
	void OnActionHand();
	UFUNCTION(BlueprintCallable)
	void OnActionPistol();


	UFUNCTION(BlueprintImplementableEvent)
	void OnMyPistolAmmoUpdate(int32 current, int32 max);
};
