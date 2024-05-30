// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimationTest/UI/Widget/Matching/ATMatchingHostSessionMenu.h"

#include "Components/ComboBoxString.h"
#include "Components/EditableTextBox.h"
#include "UI/Widget/SNButton.h"

bool UATMatchingHostSessionMenu::Initialize()
{
	bool Result = Super::Initialize();

	SessionName = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("Name")));

	ConnectionNum = Cast<UComboBoxString>(GetWidgetFromName(TEXT("ConnectNum")));

	CreateButton = Cast<USNButton>(GetWidgetFromName(TEXT("Create")));

	CancelButton = Cast<USNButton>(GetWidgetFromName(TEXT("Cancel")));
	
	return Result;
}

FName UATMatchingHostSessionMenu::GetSessionName() const
{
	if(SessionName == nullptr)
	{
		return NAME_None;
	}

	FText Text(SessionName->GetText());

	return *Text.ToString();
}

int UATMatchingHostSessionMenu::GetConnectionNum() const
{
	if(ConnectionNum == nullptr)
	{
		return -1;
	}

	int index = ConnectionNum->GetSelectedIndex();

	FString option = ConnectionNum->GetSelectedOption();

	int num = FCString::Atoi(*option);
	
	return num;	
}


