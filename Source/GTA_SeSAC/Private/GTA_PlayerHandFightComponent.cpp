// Fill out your copyright notice in the Description page of Project Settings.


#include "GTA_PlayerHandFightComponent.h"

// Sets default values for this component's properties
UGTA_PlayerHandFightComponent::UGTA_PlayerHandFightComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGTA_PlayerHandFightComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGTA_PlayerHandFightComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGTA_PlayerHandFightComponent::OnActionFocusPressed()
{
}

void UGTA_PlayerHandFightComponent::OnActionFocusReleased()
{
}

void UGTA_PlayerHandFightComponent::OnActionJap()
{
}

void UGTA_PlayerHandFightComponent::OnActionStraight()
{
}

