// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/SNActionBase.h"
#include "ATActionJump.generated.h"

/**
 * 
 */
UCLASS()
class ANIMATIONTEST_API UATActionJump : public USNActionBase
{
	GENERATED_BODY()

public:
	virtual void ExecAction(const FInputActionValue& InputActionValue) override;

	UFUNCTION()
	void OnLanded(const FHitResult& HitResult);

private:
	
	bool bDoJump = false;
};
