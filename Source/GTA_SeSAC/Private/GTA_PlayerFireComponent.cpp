// Fill out your copyright notice in the Description page of Project Settings.


#include "GTA_PlayerFireComponent.h"

// Sets default values for this component's properties
UGTA_PlayerFireComponent::UGTA_PlayerFireComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGTA_PlayerFireComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGTA_PlayerFireComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGTA_PlayerFireComponent::OnActionShoot()
{
}

void UGTA_PlayerFireComponent::OnActionReload()
{
}

void UGTA_PlayerFireComponent::DoFire()
{
}

