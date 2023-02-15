// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GTA_Player.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FSetupInputDelegate, class UInputComponent*);

UCLASS()
class GTA_SESAC_API AGTA_Player : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGTA_Player();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera Settings")
	class USpringArmComponent* SpringArmComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera Settings")
	class UCameraComponent* CameraComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "My Character Settings")
	class USphereComponent* RightFistCollision;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "My Character Settings")
	class USphereComponent* LeftFistCollision;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputMappingContext* DefaultInputMapping;


	UPROPERTY()
	class UGTA_PlayerAnimInstance* BPAnim;


	UPROPERTY()
	class AGTA_SeSACGameModeBase* GameMode;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Character Settings")
	int32 CurrentHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Character Settings")
	int32 MaxHP = 15;


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UGTA_PlayerMoveComponent* MoveComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UGTA_PlayerFightComponent* FightComponent;


	APlayerController* PlayerController;


	FSetupInputDelegate SetupInputDelegate;
};
