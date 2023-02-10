// Fill out your copyright notice in the Description page of Project Settings.


#include "Yohan/BaseEnemy.h"

// Sets default values
ABaseEnemy::ABaseEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 에너미 외형에 해당하는 애셋 읽기
	ConstructorHelpers::FObjectFinder<USkeletalMesh> EnemySkeletal(TEXT("/Script/Engine.SkeletalMesh'/Game/Yohan/Characters/Mannequins/Meshes/SKM_Manny.SKM_Manny'"));

	// 에너미 외형 애셋 읽기를 성공했다면
	if (EnemySkeletal.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(EnemySkeletal.Object);
	}

	// 에너미 Transform 수정
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -90.f), FRotator(0.f, -90.f, 0.f));

	// 에너미 속도 낮추기
	// GetCharacterMovement()->MaxWalkSpeed = 300.f;
}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseEnemy::OnActionShoot()
{

}

