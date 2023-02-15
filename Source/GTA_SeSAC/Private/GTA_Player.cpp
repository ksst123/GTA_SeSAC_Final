// Fill out your copyright notice in the Description page of Project Settings.


#include "GTA_Player.h"

#include "GTA_PlayerAnimInstance.h"
#include "GTA_PlayerFightComponent.h"
#include "GTA_PlayerMoveComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "Components/SphereComponent.h"


// Sets default values
AGTA_Player::AGTA_Player()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spinrg Arm Component"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;


	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->SetRelativeLocationAndRotation(FVector(-150.f, 0.f, 150.f), FRotator::ZeroRotator);
	CameraComponent->bUsePawnControlRotation = false;


	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;


	MoveComponent = CreateDefaultSubobject<UGTA_PlayerMoveComponent>(TEXT("Move Component"));
	FightComponent = CreateDefaultSubobject<UGTA_PlayerFightComponent>(TEXT("Fight Component"));


	RightFistCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Right Fist Collision"));
	RightFistCollision->SetupAttachment(GetMesh(), TEXT("hand_rFistSocket"));
	RightFistCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LeftFistCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Left Fist Collision"));
	LeftFistCollision->SetupAttachment(GetMesh(), TEXT("hand_lFistSocket"));
	LeftFistCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);



}

// Called when the game starts or when spawned
void AGTA_Player::BeginPlay()
{
	Super::BeginPlay();

	// Get the player controller
	PlayerController = Cast<APlayerController>(GetController());

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


	CurrentHP = MaxHP;


	// 애니메이션 블루프린트
	BPAnim = Cast<UGTA_PlayerAnimInstance>(GetMesh()->GetAnimInstance());
}

// Called every frame
void AGTA_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGTA_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	SetupInputDelegate.Broadcast(PlayerInputComponent);
}

