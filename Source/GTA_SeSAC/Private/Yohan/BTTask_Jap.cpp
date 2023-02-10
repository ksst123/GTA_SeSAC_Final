// Fill out your copyright notice in the Description page of Project Settings.


#include "Yohan/BTTask_Jap.h"
#include "Yohan/YohanCharacter.h"
#include "AIController.h"

UBTTask_Jap::UBTTask_Jap()
{
	NodeName = TEXT("Jap");
}

EBTNodeResult::Type UBTTask_Jap::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	AYohanCharacter* enemy = Cast<AYohanCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (enemy == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	enemy->OnActionHand();
	enemy->OnActionAimPressed();
	enemy->OnActionJap();
	UE_LOG(LogTemp, Warning, TEXT("Jap"));

	return EBTNodeResult::Succeeded;
}