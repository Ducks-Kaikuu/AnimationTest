// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateTree/SNSceneStateTreeTaskBase.h"
#include "ATMatchingSceneBase.generated.h"

/**
 * 
 */
UCLASS()
class ANIMATIONTEST_API UATMatchingSceneBase : public USNSceneStateTreeTaskBase
{
	GENERATED_BODY()

public:
	
	static void SetSessionName(const FName& Name);

	static FName GetSessionName();
	
protected:
	
	bool bExit = false;

private:

	static FName MatchingSessionName;
};

FORCEINLINE void UATMatchingSceneBase::SetSessionName(const FName& Name)
{
	MatchingSessionName = Name;
}

FORCEINLINE FName UATMatchingSceneBase::GetSessionName()
{
	return MatchingSessionName;
}
