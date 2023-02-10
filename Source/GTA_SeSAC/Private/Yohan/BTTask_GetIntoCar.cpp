// Fill out your copyright notice in the Description page of Project Settings.


#include "Yohan/BTTask_GetIntoCar.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Yohan/YohanCharacter.h"

UBTTask_GetIntoCar::UBTTask_GetIntoCar()
{
	NodeName = TEXT("Get Into Car");
}

EBTNodeResult::Type UBTTask_GetIntoCar::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	AYohanCharacter* enemy = Cast<AYohanCharacter>(OwnerComp.GetAIOwner()->GetPawn());

	if(enemy == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	AAIController* EnemyController = enemy->GetController<AAIController>();

	enemy->DoAIInteract(EnemyController);

	return EBTNodeResult::Succeeded;
}
