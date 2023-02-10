// Fill out your copyright notice in the Description page of Project Settings.


#include "Seung/Bullet.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "../GTA_SeSAC.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 충돌체 등록
	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("sphereComp"));
	// 충돌프로파일 설정
	SetRootComponent(sphereComp);
	// 충돌체 크기 설정
	sphereComp->SetSphereRadius(0.5);
	// 루트로 등록
	sphereComp->SetCollisionProfileName(TEXT("BlockAll"));

	// 외관 컴포넌트 등록
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	// 부모 컴포넌트 지정
	meshComp->SetupAttachment(RootComponent);
	// 충돌 비활성화
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// 외관 크기 설정
	meshComp->SetRelativeScale3D(FVector(0.5));


	// 발사체 컴포넌트
	movementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("movementComp"));
	// movement 컴포넌트가 갱신시킬 컴포넌트 지정
	movementComp->SetUpdatedComponent(sphereComp);
	// 초기속도
	movementComp->InitialSpeed = 10000;
	// 최대속도
	movementComp->MaxSpeed = 10000;
	// 번동 여부
	movementComp->bShouldBounce = true;
	// 반동 값
	movementComp->Bounciness = 0.3f;

}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();

	// 총알 없애기
	FTimerHandle dieTimerHandle;
	GetWorldTimerManager().SetTimer(dieTimerHandle, FTimerDelegate::CreateLambda([this]()->void {this->Destroy(); }), 2, false);
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet::OnDie()
{
	//총알 없애기
	Destroy();
}

