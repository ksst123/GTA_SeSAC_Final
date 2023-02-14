// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GTA_PlayerBaseComponent.h"
#include "GTA_PlayerMoveComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GTA_SESAC_API UGTA_PlayerMoveComponent : public UGTA_PlayerBaseComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGTA_PlayerMoveComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputAction* InputMoveVertical;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputAction* InputMoveHorizontal;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputAction* InputLookUp;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputAction* InputTurnRight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputAction* InputJump;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputAction* InputRun;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputAction* InputInteract;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputAction* InputHand;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputAction* InputCover;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputAction* InputPistol;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Movement Settings")
	float RunMultiplier = 2.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Movement Settings")
	float JumpValue = 450.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Movement Settings")
	float WalkSpeed = 300.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Movement Settings")
	float MouseSensitivity = 0.2f;


	void OnActionMoveVertical(const struct FInputActionValue& Value);
	void OnActionMoveHorizontal(const struct FInputActionValue& Value);
	void OnActionLookUp(const struct FInputActionValue& Value);
	void OnActionTurnRight(const struct FInputActionValue& Value);

	void OnActionJump();
	void OnActionRunPressed();
	void OnActionRunReleased();

	void OnActionStartCover();
	void OnActionEndCover();

	UFUNCTION(BlueprintCallable)
	void OnActionHand();
	UFUNCTION(BlueprintCallable)
	void OnActionPistol();
};
