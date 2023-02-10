// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_HasPlayerGun.generated.h"

/**
 * 
 */
UCLASS()
class GTA_SESAC_API UBTService_HasPlayerGun : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTService_HasPlayerGun();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
