// Fill out your copyright notice in the Description page of Project Settings.


#include "Yohan/BTTask_WalkTo.h"
#include "AIController.h"
#include "Yohan/YohanCharacter.h"
#include "Kismet/GameplayStatics.h"

UBTTask_WalkTo::UBTTask_WalkTo()
{
	NodeName = TEXT("Walk To");
}

EBTNodeResult::Type UBTTask_WalkTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	FVector OwnerLocation = OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation();

	AYohanCharacter* PlayerPawn = Cast<AYohanCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (PlayerPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	FVector TargetLocation = PlayerPawn->GetActorLocation();

	// if (TargetLocation - OwnerLocation >= 2000.f)

	return EBTNodeResult::Succeeded;
}
