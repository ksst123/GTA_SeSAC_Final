// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GTA_PoliceBaseComponent.h"
#include "GTA_PoliceHandFightComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GTA_SESAC_API UGTA_PoliceHandFightComponent : public UGTA_PoliceBaseComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGTA_PoliceHandFightComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
