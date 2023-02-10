// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "InteractableCar.generated.h"

/**
 * 
 */
UCLASS()
class GTA_SESAC_API AInteractableCar : public AWheeledVehiclePawn
{
	GENERATED_BODY()

	AInteractableCar();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Car Settings")
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Car Settings")
	class UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Car Settings")
	class UBoxComponent* GetIntoCollision;

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


	UFUNCTION()
	void OnCarBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnCarEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void ChangeInputMapping();

private:

	class AYohanCharacter* player;

	void OnActionThrottle(const struct FInputActionValue& Value);
	void OnActionBreak(const struct FInputActionValue& Value);
	void OnActionSteering(const struct FInputActionValue& Value);
	void OnActionExitCar();
	


};
