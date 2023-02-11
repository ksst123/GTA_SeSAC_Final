// Fill out your copyright notice in the Description page of Project Settings.


#include "Yohan/BTService_IsDriving.h"
#include "Yohan/YohanCharacter.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

UBTService_IsDriving::UBTService_IsDriving()
{
	NodeName = TEXT("Is Player Driving");
}

void UBTService_IsDriving::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AYohanCharacter* enemy = Cast<AYohanCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	AAIController* enemyAI = Cast<AAIController>(OwnerComp.GetAIOwner());

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AYohanCharacter* player = Cast<AYohanCharacter>(PlayerController->GetOwner());

	if (enemy == nullptr)
	{
		return;
	}

	if (enemyAI == nullptr)
	{
		return;
	}

	if(player == nullptr)
	{
		return ;
	}



	OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), player->bIsDriving);
}
