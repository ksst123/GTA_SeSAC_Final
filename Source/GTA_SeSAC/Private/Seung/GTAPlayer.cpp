// Fill out your copyright notice in the Description page of Project Settings.


#include "Seung/GTAPlayer.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <GameFramework/CharacterMovementComponent.h>

// Sets default values
AGTAPlayer::AGTAPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//01. 캐릭터 메시 붙이기
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Seung/Character/Mesh/Ch06_nonPBR.Ch06_nonPBR'"));
	if (tempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(tempMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0,0,-90),FRotator(0,-90,0));
	}

	// 03. SpringArm, Camera 생성
	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("springArmComp"));
	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("cameraComp"));
	springArmComp->SetupAttachment(RootComponent);
	cameraComp->SetupAttachment(springArmComp);
	springArmComp->SetRelativeLocation(FVector(0,40,100));
	springArmComp->TargetArmLength = 300;

	
	//10. 입력값을 회전에 반영
	bUseControllerRotationYaw = true;
	springArmComp->bUsePawnControlRotation = true;
	cameraComp->bUsePawnControlRotation = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;



}

// Called when the game starts or when spawned
void AGTAPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGTAPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//09. 움직임 적용
	FTransform trans(GetControlRotation());
	FVector resultDirection = trans.TransformVector(direction);

	resultDirection.Z = 0;
	resultDirection.Normalize();

	AddMovementInput(resultDirection);

	direction = FVector::ZeroVector;


}

// Called to bind functionality to input
void AGTAPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 05. 입력 적용하기
	PlayerInputComponent->BindAxis(TEXT("Horizontal"),this,&AGTAPlayer::OnAxisHorizontal);
	PlayerInputComponent->BindAxis(TEXT("Vertical"),this,&AGTAPlayer::OnAxisVertical);
	PlayerInputComponent->BindAxis(TEXT("Look Up"),this,&AGTAPlayer::OnAxisLookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn Right"),this,&AGTAPlayer::OnAxisTurnRight);
	PlayerInputComponent->BindAction(TEXT("Jump"),IE_Pressed,this,&AGTAPlayer::OnActionJump);
}

void AGTAPlayer::OnAxisHorizontal(float value)
{
	// 08. 움직임 적용
	direction.Y = value;
}

void AGTAPlayer::OnAxisVertical(float value)
{
	// 08. 움직임 적용
	direction.X = value;
}

void AGTAPlayer::OnAxisLookUp(float value)
{
	// 06. 위아래 적용
	AddControllerPitchInput(value);
}

void AGTAPlayer::OnAxisTurnRight(float value)
{
	// 06. 좌우 적용
	AddControllerYawInput(value);
}

void AGTAPlayer::OnActionJump()
{
	Jump();
}

