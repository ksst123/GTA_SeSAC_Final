// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GTA_PlayerVehicleMoveComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GTA_SESAC_API UGTA_PlayerVehicleMoveComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGTA_PlayerVehicleMoveComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Car Input Settings")
	class UInputMappingContext* DrivingInputMapping;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Car Input Settings")
	class UInputAction* InputThrottle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Car Input Settings")
	class UInputAction* InputSteering;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Car Input Settings")
	class UInputAction* InputBreak;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Car Input Settings")
	class UInputAction* InputExitCar;


	void OnActionThrottle(const struct FInputActionValue& Value);
	void OnActionBreak(const struct FInputActionValue& Value);
	void OnActionSteering(const struct FInputActionValue& Value);
	void OnActionExitCar();


	void OnActionEnteringCar();
	void OnActionExitingCar();


	void OnActionInteract();


	void ChangeInputMapping();
};
