// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimationTest/Scene/StateTree/ATJoinSessionTask.h"

#include "OnlineSessionSettings.h"
#include "SNDef.h"
#include "AnimationTest/UI/Widget/Matching/ATMatchingJoinMenu.h"
#include "Online/OnlineSessionNames.h"
#include "Online/SNOnlineSystem.h"
#include "Utility/SNUtility.h"

EStateTreeRunStatus UATJoinSessionTask::Tick(FStateTreeExecutionContext& Context, const float DeltaTime)
{
	EStateTreeRunStatus Result = Super::Tick(Context, DeltaTime);

	if(bExit == true)
	{
		return (bSucceed == true) ? EStateTreeRunStatus::Succeeded : EStateTreeRunStatus::Failed;
	}
	
	return Result;
}

EStateTreeRunStatus UATJoinSessionTask::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition)
{
	EStateTreeRunStatus Result = Super::EnterState(Context, Transition);

	USNOnlineSystem* OnlineSystem(SNUtility::GetOnlineSystem<USNOnlineSystem>());

	if(OnlineSystem != nullptr)
	{
		OnlineSystem->OnCompleteFindSession.AddDynamic(this, &UATJoinSessionTask::OnCompleteSearchSession);

		OnlineSystem->OnCompleteJoinSession.AddDynamic(this, &UATJoinSessionTask::OnCompleteJoinSession);
		
		OnlineSystem->FindSession();
	}
		
	return Result;
}

void UATJoinSessionTask::ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition)
{
	Super::ExitState(Context, Transition);

	USNOnlineSystem* OnlineSystem(SNUtility::GetOnlineSystem<USNOnlineSystem>());

	if(OnlineSystem != nullptr)
	{
		OnlineSystem->OnCompleteFindSession.Clear();

		OnlineSystem->OnCompleteJoinSession.Clear();
	}
}

void UATJoinSessionTask::HudPostLoad()
{
	if(UATMatchingJoinMenu* Menu = GetHudWidget<UATMatchingJoinMenu>())
	{
		Menu->OnJoinButtonClickedDelegate.BindDynamic(this, &UATJoinSessionTask::OnStartSearchSession);

		SetVisibleWidget(EWidgetLayer::Layer3, Menu);
	}
}

void UATJoinSessionTask::OnStartSearchSession(const FString& Name)
{
	USNOnlineSystem* OnlineSystem(SNUtility::GetOnlineSystem<USNOnlineSystem>());

	if(OnlineSystem != nullptr)
	{
		const TSharedPtr<FOnlineSessionSearch>& SessionList(OnlineSystem->GetSearchSessionList());

		for(auto& Result:SessionList->SearchResults)
		{
			const FOnlineSessionSetting& Setting(Result.Session.SessionSettings.Settings[SEARCH_KEYWORDS]);

			FString RoomName = Setting.Data.ToString();

			if(RoomName == Name)
			{
				OnlineSystem->JoinSession(Result);

				return;
			}
		}
	}
	// ここまで処理が来た場合は接続に失敗
	bSucceed = false;
	// 処理を終了
	bExit = true;
}


void UATJoinSessionTask::OnCompleteSearchSession(bool bResult)
{
	USNOnlineSystem* OnlineSystem(SNUtility::GetOnlineSystem<USNOnlineSystem>());

	const TSharedPtr<FOnlineSessionSearch>& SessionList(OnlineSystem->GetSearchSessionList());

	if(SessionList != nullptr)
	{
		// 検索結果が0の場合は終了
		// リトライをいれるべきか...
		if(SessionList->SearchResults.Num() <= 0)
		{
			SNPLUGIN_LOG(TEXT("Host Session is not Found."))
			// 接続失敗判定
			bSucceed = false;
			// 処理を終了
			bExit = true;
			
			return;
		}
		
		UATMatchingJoinMenu* Menu = GetHudWidget<UATMatchingJoinMenu>();

		if(Menu != nullptr)
		{
			for(auto& Result:SessionList->SearchResults)
			{
				const FOnlineSessionSetting& Setting(Result.Session.SessionSettings.Settings[SEARCH_KEYWORDS]);

				FString RoomName = Setting.Data.ToString();

				Menu->ShowRoomItem(RoomName, Result.Session.NumOpenPublicConnections);
			}
		}
	}
}

void UATJoinSessionTask::OnCompleteJoinSession(FName SessionName, bool bResult)
{
	bSucceed = bResult;

	bExit = true;

	if(bSucceed == true)
	{
		UATMatchingSceneBase::SetSessionName(SessionName);
	}
}
