// Fill out your copyright notice in the Description page of Project Settings.


#include "Yohan/BaseEnemyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

ABaseEnemyAIController::ABaseEnemyAIController()
{
	// 비헤비어 트리 애셋 읽기
	ConstructorHelpers::FObjectFinder<UBehaviorTree> BTAsset(TEXT("/Script/AIModule.BehaviorTree'/Game/Yohan/AI/BT_BaseEnemy.BT_BaseEnemy'"));
	// 비헤비어 트리 애셋 읽기 성공했다면
	if (BTAsset.Succeeded())
	{
		// 읽어온 애셋을 비헤비어 트리 포인터 변수에 할당
		BTBaseEnemy = BTAsset.Object;
	}

	// Behavior Tree Component 생성
	BTCBaseEnemy = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Tree Component"));

	// Blackboard Component 생성
	// BBBaseEnemy = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));
	// BBBaseEnemy = GetBlackboardComponent();
}

void ABaseEnemyAIController::BeginPlay()
{
	// 베이스 클래스의 함수를 그대로 실행
	Super::BeginPlay();

	// 월드에 있는 플레이어를 참조하기 위해 변수에 담는다.
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);


	if (PlayerPawn != nullptr)
	{
		// 비헤비어 트리 애셋이 비헤비어 트리 포인터 변수에 잘 할당됐다면
		if (BTBaseEnemy != nullptr)
		{
			// BTBaseEnemy 비헤비어 트리 애셋을 실행(?)
			RunBehaviorTree(BTBaseEnemy);
			// BTCBaseEnemy 비헤비어 트리 컴포넌트를 통해BTBaseEnemy 비헤비어 트리의 루트부터 실행
			// BTCBaseEnemy->StartTree(*BTBaseEnemy);


			// Blackboard에 플레이어의 위치를 담은 Vector Key 추가
			GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
			// Blackboard에 플레이어로부터 공격 당했는지 여부를 담은 Bool Key 추가
			GetBlackboardComponent()->SetValueAsBool(TEXT("IsAttacked"), bIsAttacked);

			// Blackboard에 AI의 시작 위치를 담은 Vector Key 추가
			GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());

			// GetBlackboardComponent()->SetValueAsInt(TEXT("PoliceStar"), 0);
		}
	}
}

void ABaseEnemyAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//if (PlayerPawn != nullptr)
	//{
	//	// LineOfSight를 가지고 있다면
	//	if (LineOfSightTo(PlayerPawn))
	//	{
	//		// AI가 플레이어를 바라본다 
	//		SetFocus(PlayerPawn);
	//		// AI가 플레이어를 추격한다
	//		MoveToActor(PlayerPawn, AcceptanceRadius);
	//	}
	//	else
	//	{
	//		ClearFocus(EAIFocusPriority::Gameplay);
	//		StopMovement();
	//	}
	//}

	//if (PlayerPawn != nullptr)
	//{
	//	if (LineOfSightTo(PlayerPawn))
	//	{
	//		// Setting PlayerLocation
	//		SetFocus(PlayerPawn);
	//		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
	//		// Setting LastKnownPlayerLocation
	//		GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());
	//	}
	//	else
	//	{
	//		// Clear PlayerLocation
	//		GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
	//		// Clear Focus to Player
	//		ClearFocus(EAIFocusPriority::Gameplay);
	//	}
	//}
}

void ABaseEnemyAIController::OnPossess(APawn* InPawn)
{
	// 베이스 클래스의 함수를 그대로 실행
	Super::OnPossess(InPawn);

	// 비헤비어 트리 애셋과 블랙보드 컴포넌트가 모두 해당 변수에 잘 할당됐다면
	/*if (BBBaseEnemy != nullptr && BTBaseEnemy != nullptr)
	{
		BBBaseEnemy->InitializeBlackboard(*BTBaseEnemy->BlackboardAsset);
	}*/
}
