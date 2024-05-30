// Fill out your copyright notice in the Description page of Project Settings.


#include "ATMatchingJoinMenu.h"

#include "AnimationTest/UI/Widget/ATRoomItem.h"
#include "UI/Widget/SNButton.h"

//----------------------------------------------------------------------//
//
//! @brief 初期化処理
//
//! @retval true  正常終了
//! @retval false 異常終了
//
//----------------------------------------------------------------------//
bool UATMatchingJoinMenu::Initialize(){
	
	bool Result = Super::Initialize();
	
	for(int i=0 ; i<10 ; ++i){
		// ルーム名を生成
		FString Name = FString::Printf(TEXT("Room%02d"), i);
		// ルーム情報表示用のWidgetを取得
		UATRoomItem* RoomItem = Cast<UATRoomItem>(GetWidgetFromName(FName(*Name)));
		
		if(RoomItem != nullptr){
			// 最初は非表示
			RoomItem->SetVisibility(ESlateVisibility::Hidden);
			// リストに追加
			RoomItemList.Add(RoomItem);
		}
	}
	
	return Result;
}

//----------------------------------------------------------------------//
//
//! @brief ルーム情報を表示
//
//! @param SessionName   セッション名
//! @param ConnectionNum 接続数
//
//! @retval 表示するWidgetへのポインタ
//
//----------------------------------------------------------------------//
UATRoomItem* UATMatchingJoinMenu::ShowRoomItem(const FString& SessionName, int ConnectionNum){
	
	if(RoomCount >= RoomItemList.Num()){
		return nullptr;
	}
	// ルーム情報を取得
	UATRoomItem* RoomItem = RoomItemList[RoomCount];
	// ルーム情報を設定
	RoomItem->SetRoom(SessionName, ConnectionNum);
	// 接続ボタンを押された際のデリゲートを設定
	if(USNButton* Button = RoomItem->GetJoinButton()){
		Button->OnClickedDelegate.AddDynamic(this, &UATMatchingJoinMenu::OnJoinButtonClicked);
	}
	// 情報を表示
	RoomItem->SetVisibility(ESlateVisibility::Visible);
	// ルーム数をカウントアップ
	++RoomCount;
	
	return RoomItem;
}

//----------------------------------------------------------------------//
//
//! @brief 接続ボタンを押された際のデリゲート
//
//! @param Button 押されたボタンのポインタ
//
//----------------------------------------------------------------------//
void UATMatchingJoinMenu::OnJoinButtonClicked(USNButton* Button){
	// ルーム情報用Widgetを取得
	UATRoomItem* RoomItem = Cast<UATRoomItem>(Button->GetRootWidget());

	if(RoomItem != nullptr){
		// デリゲートを実行
		OnJoinButtonClickedDelegate.ExecuteIfBound(*RoomItem->GetSessionName());
	}
}

