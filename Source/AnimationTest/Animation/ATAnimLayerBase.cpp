// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimationTest/Animation/ATAnimLayerBase.h"

#include "Animation/AnimNodeReference.h"
#include "Animation/AnimNode_SequencePlayer.h"

void UATAnimLayerBase::OnBecaomeRelevantIdle(const FAnimUpdateContext& Context, const FAnimNodeReference& Node)
{
	
	const FAnimNode_SequencePlayerBase& SequencePlayer(Node.GetAnimNode<FAnimNode_SequencePlayerBase>());

	UAnimationAsset* AnimationAsset(SequencePlayer.GetSequence());

	if(AnimationAsset != nullptr)
	{
		FString name = AnimationAsset->GetName();
	}
}
