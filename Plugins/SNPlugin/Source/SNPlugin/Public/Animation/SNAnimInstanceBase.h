// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SNAnimInstanceBase.generated.h"

class USNRelevantDataAsset;
/**
 * 
 */
UCLASS()
class SNPLUGIN_API USNAnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()
public:

	virtual void NativeInitializeAnimation() override;

	UFUNCTION(BlueprintCallable, Category="SN|Animation", meta=(BlueprintThreadSafe))
	const UAnimationAsset* GetAnimationAsset(const FName& Name) const ;

	UFUNCTION(BlueprintCallable, Category="SN|Animation", meta=(BlueprintThreadSafe))
	const UAnimSequence* GetAnimationSequence(const FName& Name) const ;
	
	UFUNCTION(BlueprintCallable, Category="SN|Animation", meta=(BlueprintThreadSafe))
	const UAnimMontage* GetAnimationMontage(const FName& Name) const ;
	
	UFUNCTION(BlueprintCallable, Category="SN|Animation", meta=(BlueprintThreadSafe))
	const UBlendSpace* GetBlendSpace(const FName& Name) const ;
	
private:

	void FinishLoadedAnimationAsset();
	
	UPROPERTY(EditAnywhere, Category="Asset")
	TObjectPtr<USNRelevantDataAsset> AnimationAssetList = nullptr;

	UPROPERTY()
	FName CurrentSequence;
};
