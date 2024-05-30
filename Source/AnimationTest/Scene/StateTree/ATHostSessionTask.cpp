// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimationTest/Scene/StateTree/ATHostSessionTask.h"

#include "AnimationTest/UI/Widget/Matching/ATMatchingHostSessionMenu.h"
#include "Online/SNOnlineSystem.h"
#include "System/SNGameInstance.h"
#include "UI/Widget/SNButton.h"
#include "Utility/SNUtility.h"

EStateTreeRunStatus UATHostSessionTask::Tick(FStateTreeExecutionContext& Context, const float DeltaTime)
{
	EStateTreeRunStatus Result = Super::Tick(Context, DeltaTime);

	if(bCancel == true)
	{
		FinishTask();

		return EStateTreeRunStatus::Failed;
	}

	if(bExit == true)
	{
		FinishTask();

		return (bSucceed == true) ? EStateTreeRunStatus::Succeeded : EStateTreeRunStatus::Failed;
	}

	return Result;
}

EStateTreeRunStatus UATHostSessionTask::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition)
{
	EStateTreeRunStatus Result = Super::EnterState(Context, Transition);

	return Result;
}

void UATHostSessionTask::ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition)
{
	Super::ExitState(Context, Transition);

	USNOnlineSystem* OnlineSystem(SNUtility::GetOnlineSystem<USNOnlineSystem>());

	if(OnlineSystem != nullptr)
	{
		OnlineSystem->OnCompleteHostSession.Clear();
	}

	if(LobbyMap.IsNull() == false)
	{
		UGameplayStatics::OpenLevel(GetWorld(), *LobbyMap.GetAssetName(), true, TEXT("listen"));
	}
}

void UATHostSessionTask::HudPostLoad()
{
	Super::HudPostLoad();

	UATMatchingHostSessionMenu* Menu = GetHudWidget<UATMatchingHostSessionMenu>();

	if(Menu != nullptr)
	{
		if(USNButton* Button = Menu->GetCreateButton())
		{
			Button->OnClickedDelegate.AddDynamic(this, &UATHostSessionTask::OnCreateButtonClicked);
		}

		if(USNButton* Button = Menu->GetCancelButton())
		{
			Button->OnClickedDelegate.AddDynamic(this, &UATHostSessionTask::OnCancelButtonClicked);
		}

		SetVisibleWidget(EWidgetLayer::Layer3, Menu);
	}
}

void UATHostSessionTask::OnCreateButtonClicked(USNButton* Button)
{
	USNOnlineSystem* OnlineSystem(SNUtility::GetOnlineSystem<USNOnlineSystem>());

	if(OnlineSystem != nullptr)
	{
		OnlineSystem->OnCompleteHostSession.AddDynamic(this, &UATHostSessionTask::OnCompleteHostSession);

		FName Name(TEXT("Session"));

		int ConnectionNum = -1;

		if(UATMatchingHostSessionMenu* Menu = GetHudWidget<UATMatchingHostSessionMenu>())
		{
			Name = Menu->GetSessionName();

			ConnectionNum = Menu->GetConnectionNum();
		}

		if(ConnectionNum > 0)
		{
			OnlineSystem->HostSession(ConnectionNum, Name);
		}
	}
}

void UATHostSessionTask::OnCancelButtonClicked(USNButton* Button)
{
	bCancel = true;
}


void UATHostSessionTask::OnCompleteHostSession(FName SessionName, bool bWasSuccessful)
{
	bSucceed = bWasSuccessful;

	bExit = true;

	if(bWasSuccessful == true)
	{
		UATMatchingSceneBase::SetSessionName(SessionName);
	}

	USNOnlineSystem* OnlineSystem(SNUtility::GetOnlineSystem<USNOnlineSystem>());

	if(OnlineSystem != nullptr)
	{
		OnlineSystem->OnCompleteHostSession.Clear();
	}
}




