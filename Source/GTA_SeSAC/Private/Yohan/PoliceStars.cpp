// Fill out your copyright notice in the Description page of Project Settings.


#include "Yohan/PoliceStars.h"
#include "Components/Image.h"




void UPoliceStars::NativeConstruct()
{
	Super::NativeConstruct();

	PoliceStarImages.Add(PoliceStarImage1);
	PoliceStarImages.Add(PoliceStarImage2);
	PoliceStarImages.Add(PoliceStarImage3);
	PoliceStarImages.Add(PoliceStarImage4);
	PoliceStarImages.Add(PoliceStarImage5);

	for (int32 i = 0; i < 5; i++)
	{
		PoliceStarImages[i]->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UPoliceStars::OnVisibleStar(int32 index)
{
	PoliceStarImages[index]->SetVisibility(ESlateVisibility::Visible);
}

void UPoliceStars::OffVisibleStar(int32 index)
{
	PoliceStarImages[index]->SetVisibility(ESlateVisibility::Hidden);
}
