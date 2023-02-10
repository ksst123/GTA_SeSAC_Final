// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_ClearPoliceStar.generated.h"

/**
 * 
 */
UCLASS()
class GTA_SESAC_API UBTTaskNode_ClearPoliceStar : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTaskNode_ClearPoliceStar();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
