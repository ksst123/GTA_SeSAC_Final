// Fill out your copyright notice in the Description page of Project Settings.


#include "Seung/GTAPlayer02.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Seung/Bullet.h"
#include "Components/SkeletalMeshComponent.h"
#include "Blueprint/UserWidget.h"

// Sets default values
AGTAPlayer02::AGTAPlayer02()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 01. 캐릭터 메시 붙이기
//	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Seung/OrcaGamesFullAnimBundle/Demo/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'"));
// 	if (tempMesh.Succeeded())
// 	{
// 		GetMesh()->SetSkeletalMesh(tempMesh.Object);
// 		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
// 	}

	// 03. SpringArm 생성
	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("springArmComp"));
	springArmComp->SetupAttachment(RootComponent);
	// 03. SpringArm 위치랑 길이조절
	springArmComp->SetRelativeLocation(FVector(0, 40, 100));
	springArmComp->TargetArmLength = 300;
	// 03. Camera 생성
	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("cameraComp"));
	cameraComp->SetupAttachment(springArmComp);

	//10. 입력값을 회전에 반영
	bUseControllerRotationYaw = true;
	springArmComp->bUsePawnControlRotation = true;
	cameraComp->bUsePawnControlRotation = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;

// 	// 총 스켈레탈메시 컴포넌트 등록
// 	gunMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMeshComp"));
// 	// 부모 컴포넌트를 Mesh 컴포넌트로 설정
// 	gunMeshComp->SetupAttachment(GetMesh());
// 	// 스켈레탈메시 데이터 로드
// 	ConstructorHelpers::FObjectFinder<USkeletalMesh>TempGunMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Seung/Guns/Pistol04/source/textures.textures'"));
// 	// 데이터로드가 성공했다면
// 	if (TempGunMesh.Succeeded())
// 	{
// 		gunMeshComp->SetSkeletalMesh(TempGunMesh.Object);
// //		gunMeshComp->SetRelativeLocation(FVector(-14,52,120));
// 		
// 	}

	myGunMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMeshComp"));
	myGunMeshComp->SetupAttachment(GetMesh());
	ConstructorHelpers::FObjectFinder<USkeletalMesh>tempGunMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Seung/Guns/Pistol04/source/textures.textures'"));
	if (tempGunMesh.Succeeded())
	{
		myGunMeshComp->SetSkeletalMesh(tempGunMesh.Object);
		myGunMeshComp->SetRelativeLocationAndRotation(FVector(-14,52,120),FRotator(0,270,0));
	}
	
	// 스나이퍼건 생성
	sniperMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("sniperMeshComp"));
	sniperMeshComp->SetupAttachment(GetMesh());
	ConstructorHelpers::FObjectFinder<UStaticMesh>tempSniper(TEXT("/Script/Engine.StaticMesh'/Game/Seung/Guns/SniperGun/sniper1.sniper1'"));
	if (tempSniper.Succeeded())
	{
		sniperMeshComp->SetStaticMesh(tempSniper.Object);
		sniperMeshComp->SetRelativeLocationAndRotation(FVector(0,80,130),FRotator(0,0,0));
		sniperMeshComp->SetRelativeScale3D(FVector(0.15f));
	}

}

// Called when the game starts or when spawned
void AGTAPlayer02::BeginPlay()
{
	Super::BeginPlay();
	
	ChangeToFist();
}

// Called every frame
void AGTAPlayer02::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 09. 움직임 적용
	FTransform trans(GetControlRotation());
	FVector resultDirection = trans.TransformVector(direction);

	resultDirection.Z = 0;
	resultDirection.Normalize();

	ACharacter::AddMovementInput(resultDirection);

	direction = FVector::ZeroVector;

}

// Called to bind functionality to input
void AGTAPlayer02::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 05. 입력 적용하기
	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &AGTAPlayer02::OnAxisHorizontal);
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &AGTAPlayer02::OnAxisVertical);
	PlayerInputComponent->BindAxis(TEXT("Look Up"), this, &AGTAPlayer02::OnAxisLookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn Right"), this, &AGTAPlayer02::OnAxisTurnRight);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AGTAPlayer02::OnActionJump);
	//총쏘기 키 추가
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &AGTAPlayer02::OnActionFirePressed);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Released, this, &AGTAPlayer02::OnActionFireReleased);
	//총 바꾸기 키
	PlayerInputComponent->BindAction(TEXT("Fist"), IE_Pressed, this, &AGTAPlayer02::ChangeToFist);
	PlayerInputComponent->BindAction(TEXT("PistolGun"), IE_Pressed, this, &AGTAPlayer02::ChangeToPistol);
	PlayerInputComponent->BindAction(TEXT("SniperGun"), IE_Pressed, this, &AGTAPlayer02::ChangeToSniper);

}

void AGTAPlayer02::OnAxisHorizontal(float value)
{
	// 08. 움직임 적용
	direction.Y = value;
}

void AGTAPlayer02::OnAxisVertical(float value)
{
	// 08. 움직임 적용
	direction.X = value;
}

void AGTAPlayer02::OnAxisLookUp(float value)
{
	// 06. 위아래 적용
	AddControllerPitchInput(value);
}

void AGTAPlayer02::OnAxisTurnRight(float value)
{
	// 06. 좌우 적용
	AddControllerYawInput(value);
}

void AGTAPlayer02::OnActionJump()
{
	Jump();
}

void AGTAPlayer02::OnActionFirePressed()
{
	// 한발 나가도록
	DoFire();
	// 꾹 누르면 쭈루룩 나가도록
	GetWorldTimerManager().SetTimer(fireTimerHandle, this, &AGTAPlayer02::DoFire, fireInterval, true);
}

void AGTAPlayer02::OnActionFireReleased()
{
	GetWorldTimerManager().ClearTimer(fireTimerHandle);
}

void AGTAPlayer02::DoFire()
{
	// 총 앞에서 총알이 나가도록 하자
	FVector t = myGunMeshComp->GetSocketLocation(TEXT("FirePosition"));
	FRotator r = GetViewRotation();
	// FRotator r = myGunMeshComp->GetSocketRotation(TEXT("FirePosition"));
	GetWorld()->SpawnActor<ABullet>(bulletFactory, t,r);
}

void AGTAPlayer02::ChangeToFist()
{
	bUsingFist = true;
	myGunMeshComp->SetVisibility(false);
	sniperMeshComp->SetVisibility(false);
}

void AGTAPlayer02::ChangeToPistol()
{
	bUsingFist = false;
	myGunMeshComp->SetVisibility(true);
	sniperMeshComp->SetVisibility(false);
}

void AGTAPlayer02::ChangeToSniper()
{
	bUsingFist = false;
	myGunMeshComp->SetVisibility(false);
	sniperMeshComp->SetVisibility(true);
}

