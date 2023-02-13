// Fill out your copyright notice in the Description page of Project Settings.


#include "GTA_CitizenBaseComponent.h"

// Sets default values for this component's properties
UGTA_CitizenBaseComponent::UGTA_CitizenBaseComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGTA_CitizenBaseComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGTA_CitizenBaseComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGTA_CitizenBaseComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

