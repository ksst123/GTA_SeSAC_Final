// Fill out your copyright notice in the Description page of Project Settings.


#include "Yohan/BTTask_FindCar.h"

#include "AIController.h"
#include "Yohan/InteractableCar.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/BoxComponent.h"


UBTTask_FindCar::UBTTask_FindCar()
{
	NodeName = TEXT("Find Car");
}

AInteractableCar* UBTTask_FindCar::FindNearestCar(FVector Origin, const TArray<AInteractableCar*>& ActorsToCheck, float& dist)
{

	AInteractableCar* NearestCar = nullptr;
	float DistanceFromNearestActor = dist = TNumericLimits<float>::Max();

	for (AInteractableCar* ActorToCheck : ActorsToCheck)
	{
		if (ActorToCheck)
		{
			const float DistanceFromActorToCheck = (Origin - ActorToCheck->GetActorLocation()).SizeSquared();
			if (DistanceFromActorToCheck < DistanceFromNearestActor)
			{
				NearestCar = ActorToCheck;
				DistanceFromNearestActor = DistanceFromActorToCheck;
			}
		}
	}

	if (NearestCar)
	{
		dist = FMath::Sqrt(DistanceFromNearestActor);
	}

	return NearestCar;
}

EBTNodeResult::Type UBTTask_FindCar::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	for (TActorIterator<AInteractableCar> it(GetWorld()); it; ++it)
	{
		Cars.Add(*it);
	}

	/*if (Cars == nullptr)
	{
		return EBTNodeResult::Failed;
	}*/

	AInteractableCar* NearestCar = FindNearestCar(OwnerComp.GetOwner()->GetActorLocation(), Cars, Distance);

	if(NearestCar == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), NearestCar->GetIntoCollision->GetComponentLocation());

	return EBTNodeResult::Succeeded;
}
