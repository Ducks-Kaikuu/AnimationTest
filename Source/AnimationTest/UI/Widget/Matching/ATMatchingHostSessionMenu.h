// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/SNUserWidgetBase.h"
#include "ATMatchingHostSessionMenu.generated.h"

class UComboBoxString;
class UEditableTextBox;
class USNButton;

/**
 * 
 */
UCLASS()
class ANIMATIONTEST_API UATMatchingHostSessionMenu : public USNUserWidgetBase
{
	GENERATED_BODY()
public:

	bool Initialize() override;

	FName GetSessionName() const ;

	int GetConnectionNum() const ;

	USNButton* GetCreateButton() const;

	USNButton* GetCancelButton() const;
	
private:
	UPROPERTY()
	TObjectPtr<UEditableTextBox> SessionName = nullptr;

	UPROPERTY()
	TObjectPtr<UComboBoxString> ConnectionNum = nullptr;

	UPROPERTY()
	TObjectPtr<USNButton>		CreateButton = nullptr;

	UPROPERTY()
	TObjectPtr<USNButton>		CancelButton = nullptr;
};

FORCEINLINE USNButton* UATMatchingHostSessionMenu::GetCreateButton() const
{
	return CreateButton;
}

FORCEINLINE USNButton* UATMatchingHostSessionMenu::GetCancelButton() const
{
	return CancelButton;
}
