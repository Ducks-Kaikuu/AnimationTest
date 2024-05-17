// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/SNAnimInstanceBase.h"
#include "ATAnimLayerBase.generated.h"

struct FAnimNodeReference;
/**
 * 
 */
UCLASS()
class ANIMATIONTEST_API UATAnimLayerBase : public USNAnimInstanceBase
{
	GENERATED_BODY()

public:

	virtual void NativeInitializeAnimation() override;
	
	UFUNCTION(Category="StateNodeFunctions", BlueprintCallable, meta=(BlueprintThreadSafe))
	void OnBecaomeRelevantIdle(const FAnimUpdateContext& Context, const FAnimNodeReference& Node);
	
private:
	UFUNCTION()
	bool TestTransition();
	
	UPROPERTY(EditAnywhere, Category="Layer|Idle")
	TObjectPtr<UAnimationAsset> Idle = nullptr;
};
