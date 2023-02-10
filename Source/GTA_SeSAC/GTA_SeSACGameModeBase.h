// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GTA_SeSACGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class GTA_SESAC_API AGTA_SeSACGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI|Police Stars")
	TSubclassOf<class UPoliceStars> PoliceStarWidgetClass;

	UPROPERTY()
	class UPoliceStars* PoliceStarWidget;

	UPROPERTY()
	int32 StarIndex;
};
