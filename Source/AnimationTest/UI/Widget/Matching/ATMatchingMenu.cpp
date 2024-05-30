// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimationTest/UI/Widget/Matching/ATMatchingMenu.h"

#include "UI/Widget/SNButton.h"

bool UATMatchingMenu::Initialize()
{
	bool Result = Super::Initialize();

	HostSessionButton = Cast<USNButton>(GetWidgetFromName(TEXT("Host")));
	JoinSessionButton = Cast<USNButton>(GetWidgetFromName(TEXT("Join")));

	return Result;
}

void UATMatchingMenu::BeginDestroy()
{
	Super::BeginDestroy();

	HostSessionButton = nullptr;
	JoinSessionButton = nullptr;
}

