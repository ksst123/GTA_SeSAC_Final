// Copyright Epic Games, Inc. All Rights Reserved.


#include "GTA_SeSACGameModeBase.h"
#include "Public/Yohan/PoliceStars.h"

void AGTA_SeSACGameModeBase::BeginPlay()
{
	PoliceStarWidget = CreateWidget<UPoliceStars>(GetWorld(), PoliceStarWidgetClass);
	if (PoliceStarWidget != nullptr)
	{
		PoliceStarWidget->AddToViewport();
		// PoliceStarWidget->OnVisibleStar();
	}
}