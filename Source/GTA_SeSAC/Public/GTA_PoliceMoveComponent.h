// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GTA_PoliceBaseComponent.h"
#include "GTA_PoliceMoveComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GTA_SESAC_API UGTA_PoliceMoveComponent : public UGTA_PoliceBaseComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGTA_PoliceMoveComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
