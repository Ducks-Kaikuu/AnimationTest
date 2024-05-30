// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimationTest/Scene/StateTree/ATMatchingSceneBase.h"
#include "ATSyncTask.generated.h"

class USNButton;
/**
 * 
 */
UCLASS()
class ANIMATIONTEST_API UATSyncTask : public UATMatchingSceneBase
{
	GENERATED_BODY()

public:

	//! @{@name 毎フレームの更新処理
	virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) override;
	//! @}
	
	//! @{@name タスクの開始処理
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;
	//! @}
	
	//! @{@name タスクの終了処理
	virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;
	//! @}

	void HudPostLoad() override;

private:
	
	UFUNCTION()
	void OnCreateButtonClicked(USNButton* Button);
	
	UPROPERTY(EditAnywhere, Category="Battle")
	TSoftObjectPtr<UObject> BattleMap;
};
