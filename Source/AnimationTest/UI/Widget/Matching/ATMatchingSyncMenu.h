// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/SNUserWidgetBase.h"
#include "ATMatchingSyncMenu.generated.h"

class UTextBlock;
class USNButton;
/**
 * 
 */
UCLASS()
class ANIMATIONTEST_API UATMatchingSyncMenu : public USNUserWidgetBase
{
	GENERATED_BODY()

public:

	bool Initialize() override;

	void SetSessionName(const FName& Name);

	USNButton* GetStartButton() const;

private:
		
	UPROPERTY()
	TObjectPtr<UTextBlock> SessionName = nullptr;

	UPROPERTY()
	TObjectPtr<USNButton>	StartButton = nullptr;
};

FORCEINLINE USNButton* UATMatchingSyncMenu::GetStartButton() const
{
	return StartButton;
}