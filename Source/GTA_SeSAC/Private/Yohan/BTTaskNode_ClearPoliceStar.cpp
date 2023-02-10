// Fill out your copyright notice in the Description page of Project Settings.


#include "Yohan/BTTaskNode_ClearPoliceStar.h"
#include "Yohan/YohanCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../GTA_SeSACGameModeBase.h"
#include "AIController.h"
#include "Yohan/PoliceStars.h"


UBTTaskNode_ClearPoliceStar::UBTTaskNode_ClearPoliceStar()
{
	NodeName = TEXT("Clear Police Star");
}

EBTNodeResult::Type UBTTaskNode_ClearPoliceStar::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AYohanCharacter* enemy = Cast<AYohanCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (enemy == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	if (enemy->GameMode->StarIndex > 0)
	{
		enemy->GameMode->PoliceStarWidget->OffVisibleStar(enemy->GameMode->StarIndex-1);
	}

	return EBTNodeResult::Succeeded;
}
