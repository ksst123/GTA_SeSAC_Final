// Fill out your copyright notice in the Description page of Project Settings.


#include "Yohan/BTTask_ClearPoliceStarBB.h"
#include "Yohan/YohanCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../GTA_SeSACGameModeBase.h"
#include "AIController.h"
#include "Yohan/PoliceStars.h"

UBTTask_ClearPoliceStarBB::UBTTask_ClearPoliceStarBB()
{
	NodeName = TEXT("Clear Police Star BB");
}

EBTNodeResult::Type UBTTask_ClearPoliceStarBB::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AYohanCharacter* enemy = Cast<AYohanCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (enemy == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	if (enemy->GameMode->StarIndex > 0)
	{
		enemy->GameMode->StarIndex -= 1;
		enemy->GameMode->PoliceStarWidget->OffVisibleStar(enemy->GameMode->StarIndex);
		OwnerComp.GetBlackboardComponent()->SetValueAsInt(GetSelectedBlackboardKey(), enemy->GameMode->StarIndex);
	}

	return EBTNodeResult::Succeeded;
}