// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "SNSceneStateTreeTaskBase.generated.h"

struct FStreamableHandle;
class  USNUserWidgetBase;

//----------------------------------------------------------------------//
//
//! @brief シーン用のステートツリーベースクラス
//
//----------------------------------------------------------------------//
UCLASS()
class SNPLUGIN_API USNSceneStateTreeTaskBase : public UStateTreeTaskBlueprintBase
{
	GENERATED_BODY()
	
protected:
	
	//! @{@name タスク開始
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;
	//! @}
	
	//! @{@name タスク終了
	virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;
	//! @}
	
	//! @{@name ウィジェットへのポインタを取得
	USNUserWidgetBase* GetHudWidget(UClass* Class);
	//! @}
	
protected:
	
	//! @{@name ウィジェットクラスのロード後に呼ばれる処理
	virtual void HudPostLoad();
	//! @}
	
private:
	
	//! @{@name ウィジェットクラスの非同期ロード処理
	void LoadHudClassASync();
	//! @}
	
	//! @{@name ウィジェットクラスのロード後に呼ばれる処理
	void FinishLoadHudClass();
	//! @}
	
	//!< ウィジェットのクラス情報リスト
	UPROPERTY(EditAnywhere, Category="Scene|UI")
	TArray<TSoftClassPtr<USNUserWidgetBase>> HudClassList;
	
	//!< ウィジェットのインスタンスリスト
	UPROPERTY()
	TArray<TObjectPtr<USNUserWidgetBase>> HudInsntaceList;
	
	//!< 非同期ロード用のハンドル
	TSharedPtr<FStreamableHandle> HudStreamHundle = nullptr;
};
