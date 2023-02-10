// Fill out your copyright notice in the Description page of Project Settings.


#include "Yohan/InteractableCar.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInput/Public/InputMappingContext.h"
#include "EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "ChaosVehicleMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Yohan/YohanCharacter.h"
//#include "Kismet/GameplayStatics.h"
//#include "../GTA_SeSACGameModeBase.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"


AInteractableCar::AInteractableCar()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	SpringArm->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(SpringArm);

	GetIntoCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Get Into Collision"));
	GetIntoCollision->SetupAttachment(RootComponent);
	GetIntoCollision->SetGenerateOverlapEvents(true);
}

void AInteractableCar::BeginPlay()
{
	Super::BeginPlay();



	GetIntoCollision->OnComponentBeginOverlap.AddDynamic(this, &AInteractableCar::OnCarBeginOverlap);
	GetIntoCollision->OnComponentEndOverlap.AddDynamic(this, &AInteractableCar::OnCarEndOverlap);
}

void AInteractableCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void AInteractableCar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComp->BindAction(InputThrottle, ETriggerEvent::Triggered, this, &AInteractableCar::OnActionThrottle);
	EnhancedInputComp->BindAction(InputThrottle, ETriggerEvent::Completed, this, &AInteractableCar::OnActionThrottle);
	
	EnhancedInputComp->BindAction(InputBreak, ETriggerEvent::Triggered, this, &AInteractableCar::OnActionBreak);
	EnhancedInputComp->BindAction(InputBreak, ETriggerEvent::Completed, this, &AInteractableCar::OnActionBreak);

	EnhancedInputComp->BindAction(InputSteering, ETriggerEvent::Triggered, this, &AInteractableCar::OnActionSteering);
	EnhancedInputComp->BindAction(InputSteering, ETriggerEvent::Completed, this, &AInteractableCar::OnActionSteering);

	EnhancedInputComp->BindAction(InputExitCar, ETriggerEvent::Triggered, this, &AInteractableCar::OnActionExitCar);
}

void AInteractableCar::OnActionThrottle(const FInputActionValue& Value)
{
	// GetVehicleMovementComponent()->SetThrottleInput(Value.GetMagnitude());
	GetVehicleMovementComponent()->SetThrottleInput(Value.Get<float>());
	UE_LOG(LogTemp, Warning, TEXT("Throttle: %f"), Value.GetMagnitude());
}

void AInteractableCar::OnActionBreak(const FInputActionValue& Value)
{
	// GetVehicleMovementComponent()->SetBrakeInput(Value.GetMagnitude());
	GetVehicleMovementComponent()->SetBrakeInput(Value.Get<float>());
	UE_LOG(LogTemp, Warning, TEXT("Break: %f"), Value.GetMagnitude());
}

void AInteractableCar::OnActionSteering(const FInputActionValue& Value)
{
	// GetVehicleMovementComponent()->SetSteeringInput(Value.GetMagnitude());
	GetVehicleMovementComponent()->SetSteeringInput(Value.Get<float>());
	UE_LOG(LogTemp, Warning, TEXT("Steering: %f"), Value.GetMagnitude());
}

void AInteractableCar::OnActionExitCar()
{
	FTimerHandle AnimTimerHandle;

	player->bIsOverlappingIntoCar = false;

	auto controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	controller->Possess(player);

	player->OnActionExitingCar();
	player->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	player->SetActorEnableCollision(true);
	player->SetActorRotation(FRotator::ZeroRotator);
	player->bIsDriving = false;
	GetWorldTimerManager().ClearTimer(AnimTimerHandle);
	player->ChangeInputMapping();
	GetVehicleMovement()->StopMovementImmediately();
	player->SetActorTransform(GetMesh()->GetSocketTransform(TEXT("ExitingPosition")));
}

void AInteractableCar::OnCarBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Begin Overlap"));
	player = Cast<AYohanCharacter>(OtherActor);	

	player->bIsOverlappingIntoCar = true;
	player->vehicle = this;
}

void AInteractableCar::OnCarEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("End Overlap"));
	player = Cast<AYohanCharacter>(OtherActor);

	player->bIsOverlappingIntoCar = false;
}

void AInteractableCar::ChangeInputMapping()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	if (PlayerController != nullptr)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		if (Subsystem != nullptr)
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(DrivingInputMapping, 0);
		}
	}
}
