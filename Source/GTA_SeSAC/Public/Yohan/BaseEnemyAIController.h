// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseEnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class GTA_SESAC_API ABaseEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ABaseEnemyAIController();
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = true))
	class UBehaviorTree* BTBaseEnemy;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = true))
	class UBehaviorTreeComponent* BTCBaseEnemy;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = true))
	class UBlackboardComponent* BBBaseEnemy;

	// 월드에 있는 플레이어를 참조하기 위한 변수
	APawn* PlayerPawn;

	// 플레이어로부터 공격 당했는지 여부
	bool bIsAttacked = false;
};
