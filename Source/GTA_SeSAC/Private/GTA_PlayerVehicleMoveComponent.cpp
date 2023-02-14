// Fill out your copyright notice in the Description page of Project Settings.


#include "GTA_PlayerVehicleMoveComponent.h"

// Sets default values for this component's properties
UGTA_PlayerVehicleMoveComponent::UGTA_PlayerVehicleMoveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGTA_PlayerVehicleMoveComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGTA_PlayerVehicleMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGTA_PlayerVehicleMoveComponent::OnActionThrottle(const FInputActionValue& Value)
{
}

void UGTA_PlayerVehicleMoveComponent::OnActionBreak(const FInputActionValue& Value)
{
}

void UGTA_PlayerVehicleMoveComponent::OnActionSteering(const FInputActionValue& Value)
{
}

void UGTA_PlayerVehicleMoveComponent::OnActionExitCar()
{
}

void UGTA_PlayerVehicleMoveComponent::OnActionEnteringCar()
{
}

void UGTA_PlayerVehicleMoveComponent::OnActionExitingCar()
{
}

void UGTA_PlayerVehicleMoveComponent::OnActionInteract()
{
}

void UGTA_PlayerVehicleMoveComponent::ChangeInputMapping()
{
}

