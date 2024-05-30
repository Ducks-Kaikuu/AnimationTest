// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimationTest/Scene/StateTree/ATMatchingTask.h"

#include "AnimationTest/UI/Widget/Matching/ATMatchingMenu.h"
#include "UI/Widget/SNButton.h"

EStateTreeRunStatus UATMatchingTask::Tick(FStateTreeExecutionContext& Context, const float DeltaTime)
{
	EStateTreeRunStatus Result = Super::Tick(Context, DeltaTime);

	if(MatchingState != EMatchingState::None)
	{
		FinishTask();

		return EStateTreeRunStatus::Succeeded;
	}

	return Result;
}

EStateTreeRunStatus UATMatchingTask::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition)
{
	EStateTreeRunStatus Result = Super::EnterState(Context, Transition);

	return Result;
}

void UATMatchingTask::ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition)
{
	Super::ExitState(Context, Transition);
}

void UATMatchingTask::HudPostLoad()
{
	Super::HudPostLoad();

	UATMatchingMenu* Menu = GetHudWidget<UATMatchingMenu>();

	if(Menu != nullptr)
	{
		if(USNButton* Button = Menu->GetHostSessionButton())
		{
			Button->OnClickedDelegate.AddDynamic(this, &UATMatchingTask::OnClickHostSession);
		}

		if(USNButton* Button = Menu->GetJoinSessionButton())
		{
			Button->OnClickedDelegate.AddDynamic(this, &UATMatchingTask::OnClickJoinSession);
		}

		SetVisibleWidget(EWidgetLayer::Layer3, Menu);
	}
}

void UATMatchingTask::OnClickHostSession(USNButton* Button)
{
	MatchingState = EMatchingState::Host;
}

void UATMatchingTask::OnClickJoinSession(USNButton* Button)
{
	MatchingState = EMatchingState::Join;
}





