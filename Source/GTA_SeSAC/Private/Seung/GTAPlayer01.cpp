// Fill out your copyright notice in the Description page of Project Settings.


#include "Seung/GTAPlayer01.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <GameFramework/CharacterMovementComponent.h>

// Sets default values
AGTAPlayer01::AGTAPlayer01()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 01. ĳ���� �޽� ���̱�
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Seung/Characters/Mannequins/Meshes/SKM_Manny.SKM_Manny'"));
	if (tempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(tempMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0,0,-90),FRotator(0,-90,0));
	}

	// 03. SpringArm ����
	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("springArmComp"));
	springArmComp->SetupAttachment(RootComponent);
	// 03. SpringArm ��ġ�� ��������
	springArmComp->SetRelativeLocation(FVector(0,40,100));
	springArmComp->TargetArmLength = 300;
	// 03. Camera ����
	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("cameraComp"));
	cameraComp->SetupAttachment(springArmComp);

	//10. �Է°��� ȸ���� �ݿ�
	bUseControllerRotationYaw = true;
	springArmComp->bUsePawnControlRotation = true;
	cameraComp->bUsePawnControlRotation = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;


}

// Called when the game starts or when spawned
void AGTAPlayer01::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGTAPlayer01::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 09. ������ ����
	FTransform trans(GetControlRotation());
	FVector resultDirection = trans.TransformVector(direction);

	resultDirection.Z = 0;
	resultDirection.Normalize();

	ACharacter::AddMovementInput(resultDirection);

	direction = FVector::ZeroVector;

}

// Called to bind functionality to input
void AGTAPlayer01::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 05. �Է� �����ϱ�
	PlayerInputComponent->BindAxis(TEXT("Horizontal"),this,&AGTAPlayer01::OnAxisHorizontal);
	PlayerInputComponent->BindAxis(TEXT("Vertical"),this,&AGTAPlayer01::OnAxisVertical);
	PlayerInputComponent->BindAxis(TEXT("Look Up"),this,&AGTAPlayer01::OnAxisLookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn Right"),this,&AGTAPlayer01::OnAxisTurnRight);
	PlayerInputComponent->BindAction(TEXT("Jump"),IE_Pressed,this,&AGTAPlayer01::OnActionJump);

}

void AGTAPlayer01::OnAxisHorizontal(float value)
{
	// 08. ������ ����
	direction.Y = value;
}

void AGTAPlayer01::OnAxisVertical(float value)
{
	// 08. ������ ����
	direction.X = value;
}

void AGTAPlayer01::OnAxisLookUp(float value)
{
	// 06. ���Ʒ� ����
	AddControllerPitchInput(value);
}

void AGTAPlayer01::OnAxisTurnRight(float value)
{
	// 06. �¿� ����
	AddControllerYawInput(value);
}

void AGTAPlayer01::OnActionJump()
{
	Jump();
}

