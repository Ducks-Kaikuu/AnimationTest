// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/SNAnimInstanceBase.h"

#include "AnimNodes/AnimNode_RandomPlayer.h"
#include "Data/SNRelevantDataAsset.h"

void USNAnimInstanceBase::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if(AnimationAssetList != nullptr)
	{
		AnimationAssetList->GetAssetLoadFinishedEvent().AddUObject(this, &USNAnimInstanceBase::FinishLoadedAnimationAsset);

		AnimationAssetList->Setup();
	}
}

void USNAnimInstanceBase::FinishLoadedAnimationAsset()
{
	if(CurrentSequence != NAME_None)
	{
		UAnimationAsset* AnimationAsset(Cast<UAnimationAsset>(AnimationAssetList->GetAsset(CurrentSequence)));

		if(AnimationAsset != nullptr)
		{
			
		}
	}
}

const UAnimationAsset* USNAnimInstanceBase::GetAnimationAsset(const FName& Name) const
{
	UAnimationAsset* AnimationAsset(nullptr);
	
	if(AnimationAssetList != nullptr)
	{
		AnimationAsset = Cast<UAnimationAsset>(AnimationAssetList->GetAsset(Name));	
	}

	return AnimationAsset;
}

const UAnimSequence* USNAnimInstanceBase::GetAnimationSequence(const FName& Name) const
{
	return Cast<UAnimSequence>(GetAnimationAsset(Name));
}

const UAnimMontage* USNAnimInstanceBase::GetAnimationMontage(const FName& Name) const
{
	return Cast<UAnimMontage>(GetAnimationAsset(Name));
}

const UBlendSpace* USNAnimInstanceBase::GetBlendSpace(const FName& Name) const
{
	return Cast<UBlendSpace>(GetAnimationAsset(Name));
}


