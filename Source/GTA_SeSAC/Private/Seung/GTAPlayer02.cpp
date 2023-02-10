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

	// 01. ĳ���� �޽� ���̱�
//	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Seung/OrcaGamesFullAnimBundle/Demo/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'"));
// 	if (tempMesh.Succeeded())
// 	{
// 		GetMesh()->SetSkeletalMesh(tempMesh.Object);
// 		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
// 	}

	// 03. SpringArm ����
	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("springArmComp"));
	springArmComp->SetupAttachment(RootComponent);
	// 03. SpringArm ��ġ�� ��������
	springArmComp->SetRelativeLocation(FVector(0, 40, 100));
	springArmComp->TargetArmLength = 300;
	// 03. Camera ����
	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("cameraComp"));
	cameraComp->SetupAttachment(springArmComp);

	//10. �Է°��� ȸ���� �ݿ�
	bUseControllerRotationYaw = true;
	springArmComp->bUsePawnControlRotation = true;
	cameraComp->bUsePawnControlRotation = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;

// 	// �� ���̷�Ż�޽� ������Ʈ ���
// 	gunMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMeshComp"));
// 	// �θ� ������Ʈ�� Mesh ������Ʈ�� ����
// 	gunMeshComp->SetupAttachment(GetMesh());
// 	// ���̷�Ż�޽� ������ �ε�
// 	ConstructorHelpers::FObjectFinder<USkeletalMesh>TempGunMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Seung/Guns/Pistol04/source/textures.textures'"));
// 	// �����ͷε尡 �����ߴٸ�
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
	
	// �������۰� ����
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

	// 09. ������ ����
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

	// 05. �Է� �����ϱ�
	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &AGTAPlayer02::OnAxisHorizontal);
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &AGTAPlayer02::OnAxisVertical);
	PlayerInputComponent->BindAxis(TEXT("Look Up"), this, &AGTAPlayer02::OnAxisLookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn Right"), this, &AGTAPlayer02::OnAxisTurnRight);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AGTAPlayer02::OnActionJump);
	//�ѽ�� Ű �߰�
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &AGTAPlayer02::OnActionFirePressed);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Released, this, &AGTAPlayer02::OnActionFireReleased);
	//�� �ٲٱ� Ű
	PlayerInputComponent->BindAction(TEXT("Fist"), IE_Pressed, this, &AGTAPlayer02::ChangeToFist);
	PlayerInputComponent->BindAction(TEXT("PistolGun"), IE_Pressed, this, &AGTAPlayer02::ChangeToPistol);
	PlayerInputComponent->BindAction(TEXT("SniperGun"), IE_Pressed, this, &AGTAPlayer02::ChangeToSniper);

}

void AGTAPlayer02::OnAxisHorizontal(float value)
{
	// 08. ������ ����
	direction.Y = value;
}

void AGTAPlayer02::OnAxisVertical(float value)
{
	// 08. ������ ����
	direction.X = value;
}

void AGTAPlayer02::OnAxisLookUp(float value)
{
	// 06. ���Ʒ� ����
	AddControllerPitchInput(value);
}

void AGTAPlayer02::OnAxisTurnRight(float value)
{
	// 06. �¿� ����
	AddControllerYawInput(value);
}

void AGTAPlayer02::OnActionJump()
{
	Jump();
}

void AGTAPlayer02::OnActionFirePressed()
{
	// �ѹ� ��������
	DoFire();
	// �� ������ �޷�� ��������
	GetWorldTimerManager().SetTimer(fireTimerHandle, this, &AGTAPlayer02::DoFire, fireInterval, true);
}

void AGTAPlayer02::OnActionFireReleased()
{
	GetWorldTimerManager().ClearTimer(fireTimerHandle);
}

void AGTAPlayer02::DoFire()
{
	// �� �տ��� �Ѿ��� �������� ����
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

