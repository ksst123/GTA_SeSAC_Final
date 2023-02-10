// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "YohanCharacter.generated.h"

UCLASS()
class GTA_SESAC_API AYohanCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AYohanCharacter();

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
		class UInputAction* InputAim;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
		class UInputAction* InputJap;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
		class UInputAction* InputStraight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
		class UInputAction* InputInteract;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
		class UInputAction* InputHand;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
		class UInputAction* InputCover;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
		class UInputAction* InputPistol;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
		class UInputAction* InputReload;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Car Settings")
		bool bIsOverlappingIntoCar = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Car Settings")
		bool bIsDriving = false;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Character Settings")
		float RunMultiplier = 2.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Character Settings")
		float JumpValue = 450.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Character Settings")
		float WalkSpeed = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Character Settings")
		float MinWalkSpeed = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Character Settings")
		float WalkDecelerationValue = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Character Settings")
		float SpringArmLength = 400.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Character Settings")
		float MouseSensitivity = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Character Settings")
		bool bHasWeapon = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Character Settings")
		bool bIsInCover = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Character Settings")
		class USoundWave* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Character Settings")
		int32 CurrentHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Character Settings")
		int32 MaxHP = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Character Settings")
		int32 FistDamage = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Character Settings")
		int32 PistolDamage = 10;

	UPROPERTY(EditAnywhere, Category = "My Character Settings")
		class UParticleSystem* BulletEffect;

	UPROPERTY(EditAnywhere, Category = "My Character Settings")
		TSubclassOf<class ABulletActor> BulletFactory;

	void OnActionEnteringCar();
	void OnActionExitingCar();

	void ChangeInputMapping();

	void OnActionMoveVertical(const struct FInputActionValue& Value);
	void OnActionMoveHorizontal(const struct FInputActionValue& Value);
	void OnActionLookUp(const struct FInputActionValue& Value);
	void OnActionTurnRight(const struct FInputActionValue& Value);

	void OnActionJump();

	void OnActionRunPressed();
	void OnActionRunReleased();

	void OnActionAimPressed();
	void OnActionAimReleased();

	void OnActionJap();
	void OnActionStraight();

	void OnActionInteract();

	void OnActionReload();

	UFUNCTION(BlueprintCallable)
	void OnActionHand();
	UFUNCTION(BlueprintCallable)
	void OnActionPistol();

	void DoFire();

	void DoAIInteract(class AAIController* enemyController);

	void OnActionStartCover();
	void OnActionEndCover();
	void TraceCover();

	void OnDamagedJap();
	void OnDamagedStraight();
	void OnFistDamagedDie();

	void OnHitUI();

	UPROPERTY()
	class AInteractableCar* vehicle;

	UPROPERTY()
	class UEnemyAnimInstance* BPAnim;

	UPROPERTY()
	bool bHasGun;

	UPROPERTY()
	bool bIsAttackSucceeded;

	UPROPERTY()
	bool bIsJap;

	UPROPERTY()
	bool bIsStraight;

	UPROPERTY()
	bool bDoOnce;

	UPROPERTY()
	bool bIsDead;

	static int StarIndex;

	UPROPERTY()
	class AGTA_SeSACGameModeBase* GameMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentPistolAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxPistolAmmo = 12;

	UPROPERTY(EditAnywhere)
	class UUserWidget* CrosshairUI;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> CrosshairFactory;

	UPROPERTY(EditAnywhere)
	class UUserWidget* HitUI;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> HitUIFactory;

	UFUNCTION()
	void OnFistBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnFistEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class APistol> PistolClass;

	UPROPERTY()
	class APistol* Pistol;



	FVector PlaneNormal;
};
