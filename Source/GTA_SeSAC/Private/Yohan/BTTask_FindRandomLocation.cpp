// Fill out your copyright notice in the Description page of Project Settings.


#include "Yohan/BTTask_FindRandomLocation.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

UBTTask_FindRandomLocation::UBTTask_FindRandomLocation()
{
	NodeName = TEXT("Find Random Location");
}

EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	FVector Origin = OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation();

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (NavSystem == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	FNavLocation NextLocation;

	if (NavSystem->GetRandomReachablePointInRadius(Origin, SearchRadius, NextLocation))
	{
		OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, NextLocation.Location);
	}

	return EBTNodeResult::Succeeded;
}
