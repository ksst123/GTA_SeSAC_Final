// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Jap.generated.h"

/**
 * 
 */
UCLASS()
class GTA_SESAC_API UBTTask_Jap : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_Jap();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
