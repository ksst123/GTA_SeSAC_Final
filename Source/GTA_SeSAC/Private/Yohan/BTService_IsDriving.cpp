// Fill out your copyright notice in the Description page of Project Settings.


#include "Yohan/BTService_IsDriving.h"
#include "Yohan/YohanCharacter.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_IsDriving::UBTService_IsDriving()
{

}

void UBTService_IsDriving::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), enemy->bIsDriving);
}
