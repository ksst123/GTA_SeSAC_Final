// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PoliceStars.generated.h"

/**
 * 
 */
UCLASS()
class GTA_SESAC_API UPoliceStars : public UUserWidget
{
	GENERATED_BODY()
	

public:
	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Police Stars", meta = (BindWidget))
	TArray<class UImage*> PoliceStarImages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Police Stars", meta = (BindWidget))
	class UImage* PoliceStarImage1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Police Stars", meta = (BindWidget))
	class UImage* PoliceStarImage2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Police Stars", meta = (BindWidget))
	class UImage* PoliceStarImage3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Police Stars", meta = (BindWidget))
	class UImage* PoliceStarImage4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Police Stars", meta = (BindWidget))
	class UImage* PoliceStarImage5;
		
	UFUNCTION()
	void OnVisibleStar(int32 index);
	UFUNCTION()
	void OffVisibleStar(int32 index);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Police Stars")
	int32 StarCount = 5;

};
