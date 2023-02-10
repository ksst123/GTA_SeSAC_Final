// Fill out your copyright notice in the Description page of Project Settings.


#include "Yohan/YohanCharacter.h"
#include "EnhancedInput/Public/InputMappingContext.h"
#include "EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
// #include "EnhancedInput/Public/InputActionValue.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimInstance.h"
#include "Yohan/EnemyAnimInstance.h"
#include "Yohan/InteractableCar.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Yohan/Pistol.h"
#include "Yohan/BulletActor.h"
#include "Yohan/InteractableCar.h"
#include "Components/SphereComponent.h"
#include "AIController.h"
#include "../GTA_SeSACGameModeBase.h"
#include "DrawDebugHelpers.h"
#include "Blueprint/UserWidget.h"

// Sets default values
AYohanCharacter::AYohanCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempSkeletal(TEXT("/Script/Engine.SkeletalMesh'/Game/Yohan/Characters/Mannequins/Meshes/SKM_Manny.SKM_Manny'"));

	if (TempSkeletal.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(TempSkeletal.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -90.f), FRotator(0.f, -90.f, 0.f));
	}

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spinrg Arm Component"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = SpringArmLength;
	// Rotate the arm based on the controller
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->SetRelativeLocationAndRotation(FVector(-150.f, 0.f, 150.f), FRotator::ZeroRotator);
	// Camera does not rotate relative to arm
	CameraComponent->bUsePawnControlRotation = false;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	// Character moves in the direction of input
	GetCharacterMovement()->bOrientRotationToMovement = true;

	RightFistCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Right Fist Collision"));
	RightFistCollision->SetupAttachment(GetMesh(), TEXT("hand_rFistSocket"));
	RightFistCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LeftFistCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Left Fist Collision"));
	LeftFistCollision->SetupAttachment(GetMesh(), TEXT("hand_lFistSocket"));
	LeftFistCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);


	// Character movement settings
	GetCharacterMovement()->JumpZVelocity = JumpValue;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	GetCharacterMovement()->MinAnalogWalkSpeed = MinWalkSpeed;
	GetCharacterMovement()->BrakingDecelerationWalking = WalkDecelerationValue;
}

// Called when the game starts or when spawned
void AYohanCharacter::BeginPlay()
{
	Super::BeginPlay();

	RightFistCollision->OnComponentBeginOverlap.AddDynamic(this, &AYohanCharacter::OnFistBeginOverlap);
	RightFistCollision->OnComponentEndOverlap.AddDynamic(this, &AYohanCharacter::OnFistEndOverlap);
	LeftFistCollision->OnComponentBeginOverlap.AddDynamic(this, &AYohanCharacter::OnFistBeginOverlap);
	LeftFistCollision->OnComponentEndOverlap.AddDynamic(this, &AYohanCharacter::OnFistEndOverlap);

	// Get the player controller
	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	if (PlayerController != nullptr)
	{
		// Get the local player subsystem
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		if (Subsystem != nullptr)
		{
			// Clear out existing mapping, and add our mapping
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(DefaultInputMapping, 0);
		}
	}

	// 애니메이션 블루프린트
	BPAnim = Cast<UEnemyAnimInstance>(GetMesh()->GetAnimInstance());

	CurrentPistolAmmo = MaxPistolAmmo;
	CurrentHP = MaxHP;

	GameMode = Cast<AGTA_SeSACGameModeBase>(GetWorld()->GetAuthGameMode());

	CrosshairUI = CreateWidget(GetWorld(), CrosshairFactory);
	HitUI = CreateWidget(GetWorld(), HitUIFactory);
}

// Called every frame
void AYohanCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*if (bIsDriving)
	{
		PlayAnimMontage(DrivingCar, 2.f, TEXT("Default"));
	}*/
}

// Called to bind functionality to input
void AYohanCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	// Get the EnhancedInputComponent
	UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	// Bind Input Actions
	EnhancedInputComp->BindAction(InputMoveVertical, ETriggerEvent::Triggered, this, &AYohanCharacter::OnActionMoveVertical);
	EnhancedInputComp->BindAction(InputMoveHorizontal, ETriggerEvent::Triggered, this, &AYohanCharacter::OnActionMoveHorizontal);

	EnhancedInputComp->BindAction(InputLookUp, ETriggerEvent::Triggered, this, &AYohanCharacter::OnActionLookUp);
	EnhancedInputComp->BindAction(InputTurnRight, ETriggerEvent::Triggered, this, &AYohanCharacter::OnActionTurnRight);

	EnhancedInputComp->BindAction(InputJump, ETriggerEvent::Triggered, this, &AYohanCharacter::OnActionJump);

	EnhancedInputComp->BindAction(InputRun, ETriggerEvent::Triggered, this, &AYohanCharacter::OnActionRunPressed);
	EnhancedInputComp->BindAction(InputRun, ETriggerEvent::Completed, this, &AYohanCharacter::OnActionRunReleased);

	EnhancedInputComp->BindAction(InputAim, ETriggerEvent::Triggered, this, &AYohanCharacter::OnActionAimPressed);
	EnhancedInputComp->BindAction(InputAim, ETriggerEvent::Completed, this, &AYohanCharacter::OnActionAimReleased);

	EnhancedInputComp->BindAction(InputJap, ETriggerEvent::Triggered, this, &AYohanCharacter::OnActionJap);
	EnhancedInputComp->BindAction(InputStraight, ETriggerEvent::Triggered, this, &AYohanCharacter::OnActionStraight);

	EnhancedInputComp->BindAction(InputInteract, ETriggerEvent::Triggered, this, &AYohanCharacter::OnActionInteract);

	EnhancedInputComp->BindAction(InputHand, ETriggerEvent::Triggered, this, &AYohanCharacter::OnActionHand);
	EnhancedInputComp->BindAction(InputPistol, ETriggerEvent::Triggered, this, &AYohanCharacter::OnActionPistol);

	EnhancedInputComp->BindAction(InputCover, ETriggerEvent::Triggered, this, &AYohanCharacter::OnActionStartCover);
	EnhancedInputComp->BindAction(InputCover, ETriggerEvent::Completed, this, &AYohanCharacter::OnActionEndCover);

	EnhancedInputComp->BindAction(InputReload, ETriggerEvent::Triggered, this, &AYohanCharacter::OnActionReload);
}

void AYohanCharacter::OnActionMoveVertical(const FInputActionValue& Value)
{
	if (Controller != nullptr)
	{
		const float MoveValue = Value.Get<float>();
		const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);

		// Move Vertical
		if (MoveValue != 0.f)
		{
			// Get Forward Vector
			const FVector Direction = MovementRotation.RotateVector(FVector::ForwardVector);

			AddMovementInput(Direction, MoveValue);
		}
	}
}

void AYohanCharacter::OnActionMoveHorizontal(const FInputActionValue& Value)
{
	if (Controller != nullptr)
	{
		const float MoveValue = Value.Get<float>();
		const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);

		// Move Horizontal
		if (MoveValue != 0.f)
		{
			// Get Right Vector
			const FVector Direction = MovementRotation.RotateVector(FVector::RightVector);

			AddMovementInput(Direction, MoveValue);
		}
	}
}

void AYohanCharacter::OnActionLookUp(const FInputActionValue& Value)
{
	if (Controller != nullptr)
	{
		const float LookValue = Value.Get<float>();

		if (LookValue != 0.f)
		{
			AddControllerYawInput(LookValue * MouseSensitivity);
		}
	}
}

void AYohanCharacter::OnActionTurnRight(const FInputActionValue& Value)
{
	if (Controller != nullptr)
	{
		const float LookValue = Value.Get<float>();

		if (LookValue != 0.f)
		{
			AddControllerPitchInput(LookValue * MouseSensitivity);
		}
	}
}

void AYohanCharacter::OnActionJump()
{
	Jump();
}

void AYohanCharacter::OnActionRunReleased()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void AYohanCharacter::OnActionRunPressed()
{
	GetCharacterMovement()->MaxWalkSpeed = RunMultiplier * WalkSpeed;
}

void AYohanCharacter::OnActionAimPressed()
{
	if (BPAnim != nullptr)
	{
		BPAnim->bIsFighting = true;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		if (bHasGun)
		{
			CrosshairUI->AddToViewport();
			GetCharacterMovement()->bOrientRotationToMovement = false;
			CameraComponent->SetFieldOfView(60.f);
		}
		// GetMesh()->UpdateChildTransforms(EUpdateTransformFlags::None);
	}
	/*else if (bHasWeapon && BPAnim != nullptr)
	{
		BPAnim->bIsFighting = true;
		BPAnim->bHasGun = true;
		GetCharacterMovement()->bOrientRotationToMovement = false;
	}*/
}

void AYohanCharacter::OnActionAimReleased()
{
	if (BPAnim != nullptr)
	{
		BPAnim->bIsFighting = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		if (bHasGun)
		{
			CrosshairUI->RemoveFromParent();
			GetCharacterMovement()->bOrientRotationToMovement = true;
			CameraComponent->SetFieldOfView(90.f);
		}
	}
}

void AYohanCharacter::OnActionJap()
{
	if ((BPAnim->PunchJap != nullptr) && (BPAnim->bIsFighting == true) && (BPAnim->bHasGun != true))
	{
		bIsJap = true;
		LeftFistCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		PlayAnimMontage(BPAnim->PunchJap, 1.f, TEXT("Default"));
		BPAnim->AnimNotify_JapEnd();
	}
	else if ((Pistol != nullptr) && (BPAnim->bIsFighting == true) && (BPAnim->bHasGun == true))
	{
		if (CurrentPistolAmmo > 0)
		{
			CurrentPistolAmmo--;
		}
		else
		{
			return;
		}

		/*FHitResult HitInfo;
		FVector StartTrace = Pistol->PistolMesh->GetSocketTransform(TEXT("FirePosition")).GetLocation();
		FVector EndTrace = StartTrace + Pistol->PistolMesh->GetForwardVector() * 10000;
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this);*/

		FHitResult HitInfo;
		// FVector StartTrace = CameraComponent->GetComponentLocation();
		FVector Location;
		FRotator Rotation;
		GetController()->GetPlayerViewPoint(Location, Rotation);
		FVector StartTrace = Pistol->PistolMesh->GetSocketTransform(TEXT("FirePosition")).GetLocation();
		FVector EndTrace = Location + CameraComponent->GetForwardVector() * 10000;
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this);

		DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Red, true, 5.f, 0, 2.f);

		bool bHit = GetWorld()->LineTraceSingleByChannel(HitInfo, StartTrace, EndTrace, ECollisionChannel::ECC_Visibility, CollisionParams);

		if (bHit)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BulletEffect, HitInfo.ImpactPoint);

			AYohanCharacter* enemy = Cast<AYohanCharacter>(HitInfo.GetActor());
			if (enemy != nullptr)
			{
				if (enemy->CurrentHP > 0)
				{
					enemy->OnDamagedJap();
				}
				else
				{
					enemy->GetMesh()->SetSimulatePhysics(true);
					enemy->GetMesh()->SetAllBodiesSimulatePhysics(true);
					enemy->bIsDead = true;
					GameMode->PoliceStarWidget->OnVisibleStar(GameMode->StarIndex++);
				}
			}

			UPrimitiveComponent* HitComp = HitInfo.GetComponent();
		}
		DoFire();
	}

}

void AYohanCharacter::OnActionStraight()
{
	if ((BPAnim->PunchStraight != nullptr) && (BPAnim->bIsFighting == true) && (BPAnim->bHasGun != true))
	{
		bIsJap = false;
		bIsStraight = true;
		RightFistCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		PlayAnimMontage(BPAnim->PunchStraight, 1.f, TEXT("Default"));
		BPAnim->AnimNotify_StraightEnd();
	}
}

void AYohanCharacter::OnActionEnteringCar()
{
	if ((BPAnim->EnteringCar != nullptr))
	{
		PlayAnimMontage(BPAnim->EnteringCar, 2.f, TEXT("Default"));
	}
}

void AYohanCharacter::OnActionExitingCar()
{
	if (BPAnim->ExitingCar != nullptr)
	{
		PlayAnimMontage(BPAnim->ExitingCar, 2.f, TEXT("Default"));
	}

	if (vehicle != nullptr)
	{

	}
}

void AYohanCharacter::ChangeInputMapping()
{
	// Get the player controller
	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	if (PlayerController != nullptr)
	{
		// Get the local player subsystem
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		if (Subsystem != nullptr)
		{
			// Clear out existing mapping, and add our mapping
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(DefaultInputMapping, 0);
		}
	}
}

void AYohanCharacter::OnActionInteract()
{
	FTimerHandle AnimTimerHandle;
	UE_LOG(LogTemp, Warning, TEXT("Interactable"));
	if (bIsOverlappingIntoCar && !bIsDriving)
	{
		// GetWorldTimerManager().SetTimer(AnimTimerHandle, this, &AYohanCharacter::OnActionEnteringCar, 2.f, false);
		OnActionEnteringCar();
		GetCharacterMovement()->StopMovementImmediately();
		SetActorEnableCollision(false);
		AttachToActor(vehicle, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		SetActorTransform(vehicle->GetMesh()->GetSocketTransform(TEXT("DrivingPosition")));
		bIsDriving = true;
		auto controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);

		// controller->UnPossess();
		controller->Possess(vehicle);
		vehicle->ChangeInputMapping();
	}
}

void AYohanCharacter::OnActionReload()
{
	if (!bHasGun)
	{
		return;
	}
	PlayAnimMontage(BPAnim->PistolReload, 1, TEXT("PistolReload"));
	CurrentPistolAmmo = MaxPistolAmmo;
}

void AYohanCharacter::OnActionHand()
{
	if (Pistol == nullptr)
	{
		return;
	}

	BPAnim->bHasGun = false;
	bHasGun = BPAnim->bHasGun;
	Pistol->Destroy();

}

void AYohanCharacter::OnActionPistol()
{
	Pistol = GetWorld()->SpawnActor<APistol>(PistolClass);
	BPAnim->bHasGun = true;
	bHasGun = BPAnim->bHasGun;

	Pistol->SetActorRelativeLocation(FVector(-11.f, 3.f, 5.f));
	Pistol->SetActorRelativeRotation(FRotator(-1.5f, -90.f, 13.f));
	Pistol->SetActorRelativeScale3D(FVector(0.5f));
	Pistol->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("GunSocket"));
	Pistol->SetOwner(this);
}

void AYohanCharacter::DoFire()
{
	//if (Pistol != nullptr)
	//{
	//	FTransform FirePosition = Pistol->PistolMesh->GetSocketTransform(TEXT("FirePosition"));

	//	GetWorld()->SpawnActor<ABulletActor>(BulletFactory, FirePosition);
	//}
}

void AYohanCharacter::DoAIInteract(class AAIController* enemyController)
{
	OnActionEnteringCar();
	GetCharacterMovement()->StopMovementImmediately();
	SetActorEnableCollision(false);
	AttachToActor(vehicle, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	SetActorTransform(vehicle->GetMesh()->GetSocketTransform(TEXT("DrivingPosition")));
	bIsDriving = true;

	enemyController->Possess(vehicle);
	vehicle->ChangeInputMapping();
}

void AYohanCharacter::OnActionStartCover()
{
	FHitResult HitInfo;
	FVector StartTrace = GetActorLocation();
	FVector EndTrace = GetActorForwardVector() * 100.f + StartTrace;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitInfo, StartTrace, EndTrace, ECollisionChannel::ECC_GameTraceChannel1, CollisionParams);

	if (bHit)
	{
		PlaneNormal = HitInfo.Normal;

		GetCharacterMovement()->SetPlaneConstraintEnabled(true);
		GetCharacterMovement()->SetPlaneConstraintOrigin(PlaneNormal);
		bUseControllerRotationYaw = false;
		bIsInCover = true;
		DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Red, true, 5.f);
	}


}

void AYohanCharacter::OnActionEndCover()
{
	GetCharacterMovement()->SetPlaneConstraintEnabled(false);
	bUseControllerRotationYaw = true;
	bIsInCover = false;
}

void AYohanCharacter::TraceCover()
{
	FHitResult HitInfoCoverRight;

	FVector TempRightVector = GetCharacterMovement()->GetPlaneConstraintNormal() * -1.f;
	FRotator TempRightRotator = UKismetMathLibrary::MakeRotFromX(TempRightVector);
	FVector RightVec = UKismetMathLibrary::GetRightVector(TempRightRotator);
	RightVec *= 45.f;
	RightVec += GetActorLocation();

	FVector RightCoverStart = RightVec;
	FVector RightCoverEnd = RightCoverStart + TempRightVector * 200.f;
	FCollisionQueryParams RightCollisionParams;
	RightCollisionParams.AddIgnoredActor(this);

	bool RightHit = GetWorld()->LineTraceSingleByChannel(HitInfoCoverRight, RightCoverStart, RightCoverEnd, ECollisionChannel::ECC_GameTraceChannel1, RightCollisionParams);


	FHitResult HitInfoCoverLeft;

	FVector TempLeftVector = GetCharacterMovement()->GetPlaneConstraintNormal();
	FRotator TempLeftRotator = UKismetMathLibrary::MakeRotFromX(TempLeftVector);
	FVector LeftVec = UKismetMathLibrary::GetRightVector(TempLeftRotator);
	LeftVec *= 45.f;
	LeftVec += GetActorLocation();

	FVector LeftCoverStart = LeftVec;
	FVector LeftCoverEnd = LeftCoverStart + TempLeftVector * 200.f;
	FCollisionQueryParams LeftCollisionParams;
	LeftCollisionParams.AddIgnoredActor(this);

	bool LeftHit = GetWorld()->LineTraceSingleByChannel(HitInfoCoverLeft, LeftCoverStart, LeftCoverEnd, ECollisionChannel::ECC_GameTraceChannel1, LeftCollisionParams);


	if (LeftHit && RightHit)
	{

	}

}

void AYohanCharacter::OnDamagedJap()
{
	PlayAnimMontage(BPAnim->Damaged, 1.f, (FName)TEXT("DamagedJap"));
	HitUI->AddToViewport();
	FTimerHandle th;
	GetWorldTimerManager().SetTimer(th, this, &AYohanCharacter::OnHitUI, 0.1f, false);
	
	
}

void AYohanCharacter::OnDamagedStraight()
{
	PlayAnimMontage(BPAnim->Damaged, 1.f, (FName)TEXT("DamagedStraight"));
}

void AYohanCharacter::OnFistDamagedDie()
{
	PlayAnimMontage(BPAnim->Damaged, 3.f, (FName)TEXT("DamagedDie"));
}

void AYohanCharacter::OnHitUI()
{
	HitUI->RemoveFromParent();
}

void AYohanCharacter::OnFistBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AYohanCharacter* player = Cast<AYohanCharacter>(OtherActor);
	AAIController* AIowner = Cast<AAIController>(player->GetController());
	if (player == nullptr)
	{
		return;
	}

	if (bDoOnce)
	{
		return;
	}
	bDoOnce = true;

	if (bIsJap)
	{
		player->BPAnim->AnimNotify_DamagedJapEnd();

		if (player->CurrentHP > 0)
		{
			player->OnDamagedJap();
		}
		else
		{
			player->OnFistDamagedDie();
			player->GetMesh()->SetSimulatePhysics(true);
			player->bIsDead = true;
			GameMode->PoliceStarWidget->OnVisibleStar(GameMode->StarIndex++);
		}

	}
	else
	{
		player->BPAnim->AnimNotify_DamagedStraightEnd();

		if (player->CurrentHP > 0)
		{
			player->OnDamagedStraight();
		}
		else
		{
			player->OnFistDamagedDie();
			player->GetMesh()->SetSimulatePhysics(true);
			player->bIsDead = true;
			GameMode->PoliceStarWidget->OnVisibleStar(GameMode->StarIndex++);
		}
	}

}

void AYohanCharacter::OnFistEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AYohanCharacter* player = Cast<AYohanCharacter>(OtherActor);

	if (player == nullptr)
	{
		return;
	}

	bIsJap = false;
	bIsStraight = false;

	player->bDoOnce = false;
}
