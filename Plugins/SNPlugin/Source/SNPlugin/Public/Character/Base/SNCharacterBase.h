// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Character/SNCharacterDef.h"

#include "SNCharacterBase.generated.h"

class USNLocomotionComponent;

// 上半身、下半身の制御をベースに入れるか悩みましたが…。基本機能なので入れました。
// 大したコストでもないし…。
UCLASS()
class SNPLUGIN_API ASNCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASNCharacterBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Returns properties that are replicated for the lifetime of the actor channel */
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	//! @{@name ステートの設定
	void SetCurrentState(const FName& Name, ECharacterStateType Type=ECharacterStateType::Full);
	//! @}
	
	//! @{@name 現在のステートを取得
	UFUNCTION(BlueprintCallable, Category="SN|Character")
	FName GetCurrentState(ECharacterStateType Type=ECharacterStateType::Full) const ;
	//! @}
	
	//! @{@name 1つ前のステートを取得
	UFUNCTION(BlueprintCallable, Category="SN|Character")
	FName GetPrevState(ECharacterStateType Type=ECharacterStateType::Full) const ;
	//! @}
	
	//! @{@name 現在のステートかチェック
	UFUNCTION(BlueprintCallable, Category = "SN|Character", meta=(BlueprintThreadSafe))
	bool IsCurrentState(const FName& State, ECharacterStateType Type=ECharacterStateType::Full) const;
	//! @}
	
	//! @{@name 1つ前のステートかチェック
	UFUNCTION(BlueprintCallable, Category = "SN|Character", meta=(BlueprintThreadSafe))
	bool IsPreState(const FName& State, ECharacterStateType Type=ECharacterStateType::Full) const;
	//! @}
	
	//! @{@name アニメーションインスタンスを取得
	UAnimInstance* GetAnimInstance();
	//! @}
	
	//! @{@name ロコモーションコンポーネントを取得
	USNLocomotionComponent* GetLocomotionComponent();
	//! @}
	
	//! @{@name アニメーションシーケンスを再生
	UFUNCTION(BlueprintCallable, Category="SN|Animation")
	void PlaySequence(const FName& Name, const FName& Slot, float PlayRate=1.0f, float BlendIn = 0.05f, float BlendOut = 0.05f, float StartTime=0.0f, bool bLoop=false);
	//! @}
	
	//! @{@name アニメーションモンタージュを再生
	UFUNCTION(BlueprintCallable, Category="SN|Animation")
	void PlayMontage(const FName& Name, float PlayRate=1.0f, float StartTime=0.0f);
	//! @}

	UFUNCTION(BlueprintCallable, Category="SN|Animation")
	void JumpMontageSection(const FName& Name, const FName& Section);
	
protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(Replicated)
	FName UppderBodyCurrentState = NAME_None;

	UPROPERTY(Replicated)
	FName UppderBodyPreStateName = NAME_None;

	UPROPERTY(Replicated)
	FName LowerBodyCurrentState = NAME_None;

	UPROPERTY(Replicated)
	FName LowerBodyPreStateName = NAME_None;

	UPROPERTY(Replicated)
	FName FullBodyCurrentState = NAME_None;

	UPROPERTY(Replicated)
	FName FullBodyPreStateName = NAME_None;
};
