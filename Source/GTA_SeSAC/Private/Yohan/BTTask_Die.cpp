// Fill out your copyright notice in the Description page of Project Settings.


#include "Yohan/BTTask_Die.h"
#include "Yohan/YohanCharacter.h"
#include "AIController.h"

UBTTask_Die::UBTTask_Die()
{
	NodeName = TEXT("Die");
}

EBTNodeResult::Type UBTTask_Die::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	AYohanCharacter* enemy = Cast<AYohanCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	AAIController* enemyAI = Cast<AAIController>(OwnerComp.GetAIOwner());
	if (enemy == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	enemyAI->StopMovement();

	return EBTNodeResult::Succeeded;
}
