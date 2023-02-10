// Fill out your copyright notice in the Description page of Project Settings.


#include "Yohan/BTService_HasPlayerGun.h"
#include "Kismet/GameplayStatics.h"
#include "Yohan/YohanCharacter.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_HasPlayerGun::UBTService_HasPlayerGun()
{
	NodeName = ("Check If Player Has Gun");
}

void UBTService_HasPlayerGun::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AYohanCharacter* PlayerPawn = Cast<AYohanCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (PlayerPawn == nullptr)
	{
		return;
	}

	if (OwnerComp.GetAIOwner() == nullptr)
	{
		return;
	}

	if (OwnerComp.GetAIOwner()->LineOfSightTo(PlayerPawn))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), PlayerPawn->bHasGun);
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	}
}
