// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/SNUserWidgetBase.h"
#include "ATMatchingJoinMenu.generated.h"

class USNButton;
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnJoinButtonClicked, const FString&, SessionName);

class UATRoomItem;
/**
 * 
 */
UCLASS()
class ANIMATIONTEST_API UATMatchingJoinMenu : public USNUserWidgetBase
{
	GENERATED_BODY()

public:
	
	//! @{@name 初期化処理
	bool Initialize() override;
	//! @}
	
	//! @{@name ルーム情報を表示
	UATRoomItem* ShowRoomItem(const FString& SessionName, int ConnectionNum);
	//! @}
	
	//! @{@name 接続ボタンを押された際のデリゲータ
	FOnJoinButtonClicked OnJoinButtonClickedDelegate;
	//! @}
	
private:
	
	//! @{@name 接続ボタンを押された際のデリゲート
	UFUNCTION()
	void OnJoinButtonClicked(USNButton* Button);
	//! @}
	
	//!< ルーム情報表示用Widgetリスト
	UPROPERTY()
	TArray<TObjectPtr<UATRoomItem>> RoomItemList;
	
	//!< 表示しているルーム数
	int RoomCount = 0;

};
