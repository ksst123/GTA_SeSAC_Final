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

	// �浹ü ���
	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("sphereComp"));
	// �浹�������� ����
	SetRootComponent(sphereComp);
	// �浹ü ũ�� ����
	sphereComp->SetSphereRadius(0.5);
	// ��Ʈ�� ���
	sphereComp->SetCollisionProfileName(TEXT("BlockAll"));

	// �ܰ� ������Ʈ ���
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	// �θ� ������Ʈ ����
	meshComp->SetupAttachment(RootComponent);
	// �浹 ��Ȱ��ȭ
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// �ܰ� ũ�� ����
	meshComp->SetRelativeScale3D(FVector(0.5));


	// �߻�ü ������Ʈ
	movementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("movementComp"));
	// movement ������Ʈ�� ���Ž�ų ������Ʈ ����
	movementComp->SetUpdatedComponent(sphereComp);
	// �ʱ�ӵ�
	movementComp->InitialSpeed = 10000;
	// �ִ�ӵ�
	movementComp->MaxSpeed = 10000;
	// ���� ����
	movementComp->bShouldBounce = true;
	// �ݵ� ��
	movementComp->Bounciness = 0.3f;

}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();

	// �Ѿ� ���ֱ�
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
	//�Ѿ� ���ֱ�
	Destroy();
}

