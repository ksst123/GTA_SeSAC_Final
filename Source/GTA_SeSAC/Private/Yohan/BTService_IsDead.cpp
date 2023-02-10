// Fill out your copyright notice in the Description page of Project Settings.


#include "Yohan/BTService_IsDead.h"
#include "Yohan/YohanCharacter.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTService_IsDead::UBTService_IsDead()
{
	NodeName = TEXT("Is Player Dead");
}

void UBTService_IsDead::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), enemy->bIsDead);
}
