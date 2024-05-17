// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SNCharacterBase.generated.h"

class USNLocomotionComponent;

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
	
	//! @{@name ステートの設定
	void SetCurrentState(const FName& Name);
	//! @}
	
	//! @{@name 現在のステートを取得
	UFUNCTION(BlueprintCallable, Category="SN|Character")
	FName GetCurrentState() const ;
	//! @}
	
	//! @{@name 1つ前のステートを取得
	UFUNCTION(BlueprintCallable, Category="SN|Character")
	FName GetPrevState() const ;
	//! @}
	
	//! @{@name 現在のステートかチェック
	UFUNCTION(BlueprintCallable, Category = "SN|Character", meta=(BlueprintThreadSafe))
	bool IsCurrentState(const FName& State) const;
	//! @}
	
	//! @{@name 1つ前のステートかチェック
	UFUNCTION(BlueprintCallable, Category = "SN|Character", meta=(BlueprintThreadSafe))
	bool IsPreState(const FName& State) const;
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
	
	FName CurrentState = NAME_None;
	
	FName PreState = NAME_None;
};
