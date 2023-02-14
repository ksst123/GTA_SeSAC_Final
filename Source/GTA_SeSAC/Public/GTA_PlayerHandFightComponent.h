// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GTA_PlayerBaseComponent.h"
#include "GTA_PlayerHandFightComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GTA_SESAC_API UGTA_PlayerHandFightComponent : public UGTA_PlayerBaseComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGTA_PlayerHandFightComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputAction* InputFocus;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputAction* InputJap;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputAction* InputStraight;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Character Settings")
	int32 FistDamage = 5;


	UPROPERTY(EditAnywhere)
	class USoundBase* PunchSound;


	void OnActionFocusPressed();
	void OnActionFocusReleased();

	void OnActionJap();
	void OnActionStraight();
};
