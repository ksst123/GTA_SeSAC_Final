// Fill out your copyright notice in the Description page of Project Settings.


#include "GTA_CitizenCharacter.h"

// Sets default values
AGTA_CitizenCharacter::AGTA_CitizenCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGTA_CitizenCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGTA_CitizenCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGTA_CitizenCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

