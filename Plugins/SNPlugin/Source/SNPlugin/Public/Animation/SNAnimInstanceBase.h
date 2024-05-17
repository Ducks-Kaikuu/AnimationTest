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

	UFUNCTION(BlueprintCallable, Category = "SN|Animation|State", meta=(BlueprintThreadSafe))
	bool IsCurrentState(const FName& State) const;

	UFUNCTION(BlueprintCallable, Category = "SN|Animation|State", meta=(BlueprintThreadSafe))
	bool IsPreState(const FName& State) const;

	UFUNCTION(BlueprintPure, Category="SN|Animation|Blendspace", meta=(BlueprintThreadSafe))
	FVector GetBlendspaceParam(const FName& Key);

	UFUNCTION(BlueprintCallable, Category="SN|Animation", meta=(BlueprintThreadSafe))
	void PlayAnimationSequence(const FName& Name, const FName& Slot, float PlayRate=1.0f, float BlendIn = 0.05f, float BlendOut = 0.05f, float StartTime=0.0f, bool bLoop=false);
	
	UFUNCTION(BlueprintCallable, Category="SN|Animation", meta=(BlueprintThreadSafe))
	void PlayAnimationMontage(const FName& Name, float PlayRate=1.0f, float StartTime=0.0f);

	UFUNCTION(BlueprintCallable, Category="SN|Animation", meta=(BlueprintThreadSafe))
	void JumpAnimationMontageSection(const FName& Name, const FName& Section);

	void SetBlendspaceParam(const FName& Key, const FVector& param);

private:

	UAnimationAsset* GetAnimationAsset(const FName& Name);

	UAnimSequence* GetAnimationSequence(const FName& Name);

	UAnimMontage* GetAnimationMontage(const FName& Name);
	
	void FinishLoadedAnimationAsset();
	
	UPROPERTY(EditAnywhere, Category="Asset")
	TObjectPtr<USNRelevantDataAsset> AnimationAssetList = nullptr;

	UPROPERTY()
	TMap<FName, FVector> BlendspaceParam;
};

FORCEINLINE UAnimSequence* USNAnimInstanceBase::GetAnimationSequence(const FName& Name)
{
	return Cast<UAnimSequence>(GetAnimationAsset(Name));
}

FORCEINLINE UAnimMontage* USNAnimInstanceBase::GetAnimationMontage(const FName& Name)
{
	return Cast<UAnimMontage>(GetAnimationAsset(Name));
}