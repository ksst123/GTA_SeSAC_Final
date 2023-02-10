// Fill out your copyright notice in the Description page of Project Settings.


#include "Yohan/BTService_CheckPoliceStar.h"
#include "Yohan/YohanCharacter.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../GTA_SeSACGameModeBase.h"

UBTService_CheckPoliceStar::UBTService_CheckPoliceStar()
{
	NodeName = TEXT("Check If There Is Police Star");
}

void UBTService_CheckPoliceStar::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AYohanCharacter* enemy = Cast<AYohanCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	AAIController* enemyAI = Cast<AAIController>(OwnerComp.GetAIOwner());
	if (enemy == nullptr)
	{
		return;
	}

	if (enemyAI == nullptr)
	{
		return;
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsInt(GetSelectedBlackboardKey(), enemy->GameMode->StarIndex);
}
