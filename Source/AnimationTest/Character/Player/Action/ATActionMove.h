// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/SNActionBase.h"
#include "ATActionMove.generated.h"

class UCurveVector;
/**
 * 
 */
UCLASS()
class ANIMATIONTEST_API UATActionMove : public USNActionBase
{
	GENERATED_BODY()

public:
	
	virtual void ExecAction(const FInputActionValue& InputActionValue) override;

private:
	UPROPERTY(EditAnywhere, Category="Move")
	TObjectPtr<UCurveVector> VelocityCurve;
};
