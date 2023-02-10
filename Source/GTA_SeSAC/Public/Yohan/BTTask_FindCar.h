// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_FindCar.generated.h"

/**
 * 
 */
UCLASS()
class GTA_SESAC_API UBTTask_FindCar : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTTask_FindCar();

	TArray<class AInteractableCar*> Cars;

	float Distance;

	class AInteractableCar* FindNearestCar(FVector Origin, const TArray<class AInteractableCar*>& ActorsToCheck, float& dist);

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


};
