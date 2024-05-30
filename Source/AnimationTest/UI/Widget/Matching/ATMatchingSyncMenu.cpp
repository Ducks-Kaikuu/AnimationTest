// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimationTest/UI/Widget/Matching/ATMatchingSyncMenu.h"

#include "Components/TextBlock.h"
#include "UI/Widget/SNButton.h"

bool UATMatchingSyncMenu::Initialize()
{
	bool bResult = Super::Initialize();

	SessionName = Cast<UTextBlock>(GetWidgetFromName(FName(TEXT("MatchingSessionName"))));

	StartButton = Cast<USNButton>(GetWidgetFromName(TEXT("Start")));
	
	return bResult;
}

void UATMatchingSyncMenu::SetSessionName(const FName& Name)
{
	if(SessionName != nullptr)
	{
		SessionName->SetText(FText::FromString(Name.ToString()));
	}
}

