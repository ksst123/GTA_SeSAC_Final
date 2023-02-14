// Fill out your copyright notice in the Description page of Project Settings.


#include "GTA_PlayerMoveComponent.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "GTA_Player.h"
#include "GameFramework/CharacterMovementComponent.h"



// Sets default values for this component's properties
UGTA_PlayerMoveComponent::UGTA_PlayerMoveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGTA_PlayerMoveComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGTA_PlayerMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGTA_PlayerMoveComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Get the EnhancedInputComponent
	UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	// Bind Input Actions
	EnhancedInputComp->BindAction(InputMoveVertical, ETriggerEvent::Triggered, this, &UGTA_PlayerMoveComponent::OnActionMoveVertical);
	EnhancedInputComp->BindAction(InputMoveHorizontal, ETriggerEvent::Triggered, this, &UGTA_PlayerMoveComponent::OnActionMoveHorizontal);

	EnhancedInputComp->BindAction(InputLookUp, ETriggerEvent::Triggered, this, &UGTA_PlayerMoveComponent::OnActionLookUp);
	EnhancedInputComp->BindAction(InputTurnRight, ETriggerEvent::Triggered, this, &UGTA_PlayerMoveComponent::OnActionTurnRight);

	EnhancedInputComp->BindAction(InputJump, ETriggerEvent::Triggered, this, &UGTA_PlayerMoveComponent::OnActionJump);

	EnhancedInputComp->BindAction(InputRun, ETriggerEvent::Triggered, this, &UGTA_PlayerMoveComponent::OnActionRunPressed);
	EnhancedInputComp->BindAction(InputRun, ETriggerEvent::Completed, this, &UGTA_PlayerMoveComponent::OnActionRunReleased);
}

void UGTA_PlayerMoveComponent::OnActionMoveVertical(const FInputActionValue& Value)
{
	if (ownerPlayer->Controller != nullptr)
	{
		const float MoveValue = Value.Get<float>();
		const FRotator MovementRotation(0.f, ownerPlayer->Controller->GetControlRotation().Yaw, 0.f);

		// Move Vertical
		if (MoveValue != 0.f)
		{
			// Get Forward Vector
			const FVector Direction = MovementRotation.RotateVector(FVector::ForwardVector);

			ownerPlayer->AddMovementInput(Direction, MoveValue);
		}
	}
}

void UGTA_PlayerMoveComponent::OnActionMoveHorizontal(const FInputActionValue& Value)
{
	if (ownerPlayer->Controller != nullptr)
	{
		const float MoveValue = Value.Get<float>();
		const FRotator MovementRotation(0.f, ownerPlayer->Controller->GetControlRotation().Yaw, 0.f);

		// Move Horizontal
		if (MoveValue != 0.f)
		{
			// Get Right Vector
			const FVector Direction = MovementRotation.RotateVector(FVector::RightVector);

			ownerPlayer->AddMovementInput(Direction, MoveValue);
		}
	}
}

void UGTA_PlayerMoveComponent::OnActionLookUp(const FInputActionValue& Value)
{
	if (ownerPlayer->Controller != nullptr)
	{
		const float LookValue = Value.Get<float>();

		if (LookValue != 0.f)
		{
			ownerPlayer->AddControllerYawInput(LookValue * MouseSensitivity);
		}
	}
}

void UGTA_PlayerMoveComponent::OnActionTurnRight(const FInputActionValue& Value)
{
	if (ownerPlayer->Controller != nullptr)
	{
		const float LookValue = Value.Get<float>();

		if (LookValue != 0.f)
		{
			ownerPlayer->AddControllerPitchInput(LookValue * MouseSensitivity);
		}
	}
}

void UGTA_PlayerMoveComponent::OnActionJump()
{
	ownerPlayer->Jump();
}

void UGTA_PlayerMoveComponent::OnActionRunPressed()
{
	ownerPlayer->GetCharacterMovement()->MaxWalkSpeed = RunMultiplier * WalkSpeed;
}

void UGTA_PlayerMoveComponent::OnActionRunReleased()
{
	ownerPlayer->GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void UGTA_PlayerMoveComponent::OnActionStartCover()
{
}

void UGTA_PlayerMoveComponent::OnActionEndCover()
{
}

void UGTA_PlayerMoveComponent::OnActionHand()
{
}

void UGTA_PlayerMoveComponent::OnActionPistol()
{
}

