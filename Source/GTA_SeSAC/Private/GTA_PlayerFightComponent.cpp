// Fill out your copyright notice in the Description page of Project Settings.


#include "GTA_PlayerFightComponent.h"
#include "GTA_Player.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GTA_PoliceCharacter.h"
#include "../GTA_SeSACGameModeBase.h"
#include "Yohan/PoliceStars.h"
#include "GTA_PlayerAnimInstance.h"
#include "Components/SphereComponent.h"
#include "Yohan/Pistol.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"


// Sets default values for this component's properties
UGTA_PlayerFightComponent::UGTA_PlayerFightComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGTA_PlayerFightComponent::BeginPlay()
{
	Super::BeginPlay();


	CurrentPistolAmmo = MaxPistolAmmo;


	CrosshairUI = CreateWidget(GetWorld(), CrosshairFactory);
}


// Called every frame
void UGTA_PlayerFightComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGTA_PlayerFightComponent::SetupPlayerInput(UInputComponent* PlayerInputComponent)
{
	// Get the EnhancedInputComponent
	UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComp->BindAction(InputAim, ETriggerEvent::Triggered, this, &UGTA_PlayerFightComponent::OnActionAimPressed);
	EnhancedInputComp->BindAction(InputAim, ETriggerEvent::Completed, this, &UGTA_PlayerFightComponent::OnActionAimReleased);


	EnhancedInputComp->BindAction(InputJap, ETriggerEvent::Triggered, this, &UGTA_PlayerFightComponent::OnActionJap);
	EnhancedInputComp->BindAction(InputStraight, ETriggerEvent::Triggered, this, &UGTA_PlayerFightComponent::OnActionStraight);
	EnhancedInputComp->BindAction(InputShoot, ETriggerEvent::Triggered, this, &UGTA_PlayerFightComponent::OnActionShoot);


	EnhancedInputComp->BindAction(InputHand, ETriggerEvent::Triggered, this, &UGTA_PlayerFightComponent::OnActionHand);
	EnhancedInputComp->BindAction(InputPistol, ETriggerEvent::Triggered, this, &UGTA_PlayerFightComponent::OnActionPistol);


	EnhancedInputComp->BindAction(InputReload, ETriggerEvent::Triggered, this, &UGTA_PlayerFightComponent::OnActionReload);
}

void UGTA_PlayerFightComponent::OnActionAimPressed()
{
	if (ownerPlayer->BPAnim != nullptr)
	{
		ownerPlayer->BPAnim->bIsFighting = true;
		ownerPlayer->GetCharacterMovement()->bOrientRotationToMovement = true;
		if (bHasGun)
		{
			if (ownerPlayer->PlayerController != nullptr)
			{
				CrosshairUI->AddToViewport();
				ownerPlayer->GetCharacterMovement()->bOrientRotationToMovement = false;
				ownerPlayer->CameraComponent->SetFieldOfView(60.f);
			}
		}
		// GetMesh()->UpdateChildTransforms(EUpdateTransformFlags::None);
	}
	/*else if (bHasWeapon && BPAnim != nullptr)
	{
		BPAnim->bIsFighting = true;
		BPAnim->bHasGun = true;
		GetCharacterMovement()->bOrientRotationToMovement = false;
	}*/
}

void UGTA_PlayerFightComponent::OnActionAimReleased()
{
	if (ownerPlayer->BPAnim != nullptr)
	{
		ownerPlayer->BPAnim->bIsFighting = false;
		ownerPlayer->GetCharacterMovement()->bOrientRotationToMovement = true;
		if (bHasGun)
		{
				CrosshairUI->RemoveFromParent();
				ownerPlayer->GetCharacterMovement()->bOrientRotationToMovement = true;
				ownerPlayer->CameraComponent->SetFieldOfView(90.f);
		}
	}
}

void UGTA_PlayerFightComponent::OnActionJap()
{
	if ((ownerPlayer->BPAnim->PunchJap != nullptr) && (ownerPlayer->BPAnim->bIsFighting == true) && (ownerPlayer->BPAnim->bHasGun != true))
	{
		UGameplayStatics::PlaySoundAtLocation(this, PunchSound, ownerPlayer->GetActorLocation());
		bIsJap = true;
		ownerPlayer->LeftFistCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		ownerPlayer->PlayAnimMontage(ownerPlayer->BPAnim->PunchJap, 1.f, TEXT("Default"));
		ownerPlayer->BPAnim->AnimNotify_Jap();
	}
}

void UGTA_PlayerFightComponent::OnActionStraight()
{
	if ((ownerPlayer->BPAnim->PunchStraight != nullptr) && (ownerPlayer->BPAnim->bIsFighting == true) && (ownerPlayer->BPAnim->bHasGun != true))
	{
		UGameplayStatics::PlaySoundAtLocation(this, PunchSound, ownerPlayer->GetActorLocation());
		bIsJap = false;
		bIsStraight = true;
		ownerPlayer->RightFistCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		ownerPlayer->PlayAnimMontage(ownerPlayer->BPAnim->PunchStraight, 1.f, TEXT("Default"));
		ownerPlayer->BPAnim->AnimNotify_Straight();
	}
}

void UGTA_PlayerFightComponent::OnActionShoot()
{
	if ((Pistol != nullptr) && (ownerPlayer->BPAnim->bIsFighting == true) && (ownerPlayer->BPAnim->bHasGun == true))
	{
		UGameplayStatics::PlaySoundAtLocation(this, PistolSound, ownerPlayer->GetActorLocation());
		if (CurrentPistolAmmo > 0)
		{
			if (ownerPlayer->PlayerController != nullptr)
			{
				CurrentPistolAmmo--;
				OnMyPistolAmmoUpdate(CurrentPistolAmmo, MaxPistolAmmo);
				UE_LOG(LogTemp, Warning, TEXT("CurrentAmmo: %d"), CurrentPistolAmmo);
			}
		}
		else
		{
			return;
		}

		/*FHitResult HitInfo;
		FVector StartTrace = Pistol->PistolMesh->GetSocketTransform(TEXT("FirePosition")).GetLocation();
		FVector EndTrace = StartTrace + Pistol->PistolMesh->GetForwardVector() * 10000;
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this);*/

		FHitResult HitInfo;
		FVector Location;
		FRotator Rotation;
		ownerPlayer->GetController()->GetPlayerViewPoint(Location, Rotation);
		FVector StartTrace = Pistol->PistolMesh->GetSocketTransform(TEXT("FirePosition")).GetLocation();
		FVector EndTrace = Location + ownerPlayer->CameraComponent->GetForwardVector() * 10000;
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(ownerPlayer);

		DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::FColor(255, 200, 0), false, 0.1f, 0, 0.5f);

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PistolEffect, StartTrace);

		bool bHit = GetWorld()->LineTraceSingleByChannel(HitInfo, StartTrace, EndTrace, ECollisionChannel::ECC_Visibility, CollisionParams);

		if (bHit)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BulletEffect, HitInfo.ImpactPoint);

			AGTA_PoliceCharacter* enemy = Cast<AGTA_PoliceCharacter>(HitInfo.GetActor());
			if (enemy == nullptr)
			{
				return;
			}
			/*if (enemy != nullptr)
			{
				if (enemy->CurrentHP > 0)
				{
					enemy->OnDamagedJap();
					if (enemy->GetController() != nullptr)
					{

						if (ownerPlayer->PlayerController != nullptr)
						{
							enemy->HitUI->AddToViewport();
							FTimerHandle th;
							ownerPlayer->GetWorldTimerManager().SetTimer(th, enemy, &AGTA_PoliceCharacter::OnHitUI, 0.1f, false);
						}
					}
				}
				else
				{
					enemy->GetMesh()->SetSimulatePhysics(true);
					enemy->GetMesh()->SetAllBodiesSimulatePhysics(true);
					enemy->bIsDead = true;
					if (ownerPlayer->PlayerController == nullptr)
					{
						ownerPlayer->GameMode->PoliceStarWidget->OnVisibleStar(ownerPlayer->GameMode->StarIndex++);
					}
					else
					{
						enemy->OnGameOverUI();
					}
				}
			}*/

			UPrimitiveComponent* HitComp = HitInfo.GetComponent();
		}
		DoFire();
	}
}

void UGTA_PlayerFightComponent::DoFire()
{
}

void UGTA_PlayerFightComponent::OnActionReload()
{
	if (!bHasGun)
	{
		return;
	}
	ownerPlayer->PlayAnimMontage(ownerPlayer->BPAnim->PistolReload, 1, TEXT("PistolReload"));
	CurrentPistolAmmo = MaxPistolAmmo;

	if (ownerPlayer->PlayerController != nullptr)
	{
		OnMyPistolAmmoUpdate(CurrentPistolAmmo, MaxPistolAmmo);
	}
}

void UGTA_PlayerFightComponent::OnActionHand()
{
	if (Pistol == nullptr)
	{
		return;
	}


	Pistol->Destroy();


	if (ownerPlayer->PlayerController == nullptr)
	{
		return;
	}
	ownerPlayer->BPAnim->bHasGun = false;
	bHasGun = ownerPlayer->BPAnim->bHasGun;
}

void UGTA_PlayerFightComponent::OnActionPistol()
{
	Pistol = GetWorld()->SpawnActor<APistol>(PistolClass);


	Pistol->SetActorRelativeLocation(FVector(-11.f, 3.f, 5.f));
	Pistol->SetActorRelativeRotation(FRotator(-1.5f, -90.f, 13.f));
	Pistol->SetActorRelativeScale3D(FVector(0.5f));
	Pistol->AttachToComponent(ownerPlayer->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("GunSocket"));
	Pistol->SetOwner(ownerPlayer);


	if (ownerPlayer->PlayerController == nullptr)
	{
		return;
	}
	ownerPlayer->BPAnim->bHasGun = true;
	bHasGun = ownerPlayer->BPAnim->bHasGun;
}

