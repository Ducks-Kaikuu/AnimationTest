// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Base/SNCharacterBase.h"

#include "SNDef.h"
#include "Animation/SNAnimInstanceBase.h"
#include "Animation/Components/SNLocomotionComponent.h"
#include "Net/UnrealNetwork.h"
#include "Utility/SNUtility.h"

//----------------------------------------------------------------------//
//
//! @brief デフォルトコンストラクタ
//
//----------------------------------------------------------------------//
ASNCharacterBase::ASNCharacterBase(){
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// レプリケートをON
	SetReplicates(true);
	// 移動、回転などの動きをレプリケート
	SetReplicateMovement(true);
}

//----------------------------------------------------------------------//
//
//! @brief レプリケートするメンバを取得
//
//! @param OutLifetimeProps レプリケートするメンバ
//
//! @note レプリケートするメンバはここで登録しないとレプリケートされない
//
//----------------------------------------------------------------------//
void ASNCharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
//	DOREPLIFETIME(ASNCharacterBase, UppderBodyCurrentState);
//	DOREPLIFETIME(ASNCharacterBase, UppderBodyPreStateName);
//	DOREPLIFETIME(ASNCharacterBase, LowerBodyCurrentState);
//	DOREPLIFETIME(ASNCharacterBase, LowerBodyPreStateName);
//	DOREPLIFETIME(ASNCharacterBase, FullBodyCurrentState);
//	DOREPLIFETIME(ASNCharacterBase, FullBodyPreStateName);
}

//----------------------------------------------------------------------//
//
//! @brief ゲームがスタートしたとき、もしくはアクターがスポーンされたときに呼ばれます。
//
//----------------------------------------------------------------------//
void ASNCharacterBase::BeginPlay(){
	Super::BeginPlay();
	
}

//----------------------------------------------------------------------//
//
//! @brief 毎フレーム呼ばれます。
//
//! @param DeltaTime 経過時間
//
//----------------------------------------------------------------------//
void ASNCharacterBase::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASNCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

//----------------------------------------------------------------------//
//
//! @brief 現在のステートを設定
//
//! @param Name 新しく設定するステート
//! @param Type タイプ
//
//----------------------------------------------------------------------//
void ASNCharacterBase::SetCurrentState(const FName& Name, ECharacterStateType Type){
	
	if(SNUtility::IsServer(GetWorld()))
	{
		InternalSetCurrentState(Name, Type);
		
		SetCurrentState_OnMulticast(Name, Type);
	} else
	{
		SetCurrentState_OnServer(Name, Type);
	}
}

void ASNCharacterBase::SetCurrentState_OnServer_Implementation(const FName& Name, ECharacterStateType Type)
{
	SetCurrentState(Name, Type);
}

bool ASNCharacterBase::SetCurrentState_OnServer_Validate(const FName& Name, ECharacterStateType Type)
{
	return Type > (ECharacterStateType)0 && Type < ECharacterStateType::Num;
}


void ASNCharacterBase::SetCurrentState_OnMulticast_Implementation(const FName& Name, ECharacterStateType Type)
{
	InternalSetCurrentState(Name, Type);
}

bool ASNCharacterBase::SetCurrentState_OnMulticast_Validate(const FName& Name, ECharacterStateType Type)
{
	return Type > (ECharacterStateType)0 && Type < ECharacterStateType::Num;
}

void ASNCharacterBase::SetBlendspaceParam(const FName& Key, const FVector& Param)
{
	if(SNUtility::IsServer(GetWorld()))
	{
		IntervalBlendspaceParam(Key, Param);

		SetBlendspaceParam_OnMulticast(Key, Param);
	} else
	{
		SetBlendspaceParam_OnServer(Key, Param);
	}
}

void ASNCharacterBase::SetBlendspaceParam_OnServer_Implementation(const FName& Key, const FVector& Param)
{
	SetBlendspaceParam(Key, Param);
}

void ASNCharacterBase::SetBlendspaceParam_OnMulticast_Implementation(const FName& Key, const FVector& Param)
{
	IntervalBlendspaceParam(Key, Param);
}

void ASNCharacterBase::IntervalBlendspaceParam(const FName& Key, const FVector& Param)
{
	USNAnimInstanceBase* AnimInstance(Cast<USNAnimInstanceBase>(GetAnimInstance()));
	
	if(AnimInstance != nullptr)
	{
		AnimInstance->SetBlendspaceParam(Key, Param);	
	}
}

void ASNCharacterBase::InternalSetCurrentState(const FName& Name, ECharacterStateType Type){
	
	TFunction<bool(FName&, FName&, const FName&)> Function = [this](FName& PreState, FName& CurrentState, const FName& Input) -> bool
	{
		bool bChanged = false;
		
		if(CurrentState != Input){
			// 現在のステートを保存
			PreState = CurrentState;
			// ステートを変更
			CurrentState = Input;
			// 変更フラグをON
			bChanged = true;
		}
		
		return bChanged;
	};
	// 全身
	if(Type == ECharacterStateType::Full){
		
		if(Function(FullBodyPreStateName, FullBodyCurrentState, Name) == true){
			SNPLUGIN_LOG(TEXT("Full State : %s"), *FullBodyCurrentState.ToString());
		}
	} else 
	// 上半身
	if(Type == ECharacterStateType::Upper){
		
		if(Function(UppderBodyPreStateName, UppderBodyCurrentState, Name) == true){
			SNPLUGIN_LOG(TEXT("Upper State : %s"), *UppderBodyCurrentState.ToString());
		}
	} else
	// 下半身
	if(Type == ECharacterStateType::Lower){
		
		if(Function(LowerBodyPreStateName, LowerBodyCurrentState, Name) == true){
			SNPLUGIN_LOG(TEXT("Lower State : %s"), *LowerBodyCurrentState.ToString());
		}
	}
}

//----------------------------------------------------------------------//
//
//! @brief 現在のステートを取得
//
//! @param Type タイプ
//
//! @retval 現在のステート
//
//----------------------------------------------------------------------//
FName ASNCharacterBase::GetCurrentState(ECharacterStateType Type) const {
	
	if(Type == ECharacterStateType::Upper){
		return UppderBodyCurrentState;
	} else
	if(Type == ECharacterStateType::Lower){
		return LowerBodyCurrentState;
	}
	
	return FullBodyCurrentState;
}

//----------------------------------------------------------------------//
//
//! @brief 1つ前のステートを取得
//
//! @param Type タイプ
//
//! @retval 1つ前のステート
//
//----------------------------------------------------------------------//
FName ASNCharacterBase::GetPrevState(ECharacterStateType Type) const {
	
	if(Type == ECharacterStateType::Upper){
		return UppderBodyPreStateName;
	} else
	if(Type == ECharacterStateType::Lower){
		return LowerBodyPreStateName;
	}
	
	return FullBodyPreStateName;
}

//----------------------------------------------------------------------//
//
//! @brief 現在のステートかチェック
//
//! @param State ステート
//! @param Type  タイプ
//
//! @retval true  現在のステート
//! @retval false 現在のステートではない
//
//----------------------------------------------------------------------//
bool ASNCharacterBase::IsCurrentState(const FName& State, ECharacterStateType Type) const {
	
	if(Type == ECharacterStateType::Upper){
		return (UppderBodyCurrentState == State) ? true : false;
	} else
	if(Type == ECharacterStateType::Lower){
		return (LowerBodyCurrentState == State) ? true : false;
	}
	
	return (FullBodyCurrentState == State) ? true : false;
}

//----------------------------------------------------------------------//
//
//! @brief 1つ前のステートかチェック
//
//! @param State ステート
//! @param Type  タイプ
//
//! @retval true  1つ前ののステート
//! @retval false 1つ前のステートではない
//
//----------------------------------------------------------------------//
bool ASNCharacterBase::IsPreState(const FName& State, ECharacterStateType Type) const {
	
	if(Type == ECharacterStateType::Upper){
		return (UppderBodyPreStateName == State) ? true : false;
	} else
	if(Type == ECharacterStateType::Lower){
		return (LowerBodyPreStateName == State) ? true : false;
	}
	
	return (FullBodyPreStateName == State) ? true : false;
}

UAnimInstance* ASNCharacterBase::GetAnimInstance()
{
	USkeletalMeshComponent* SkeletalMeshComponent(GetMesh());

	if(SkeletalMeshComponent != nullptr)
	{
		return SkeletalMeshComponent->GetAnimInstance();
	}

	return nullptr;
}

USNLocomotionComponent* ASNCharacterBase::GetLocomotionComponent()
{
	return Cast<USNLocomotionComponent>(GetComponentByClass(USNLocomotionComponent::StaticClass()));
}

void ASNCharacterBase::PlaySequence(const FName& Name, const FName& Slot, float PlayRate, float BlendIn, float BlendOut, float StartTime, bool bLoop)
{
	if(SNUtility::IsServer(GetWorld()))
	{
		InternalPlaySequence(Name, Slot, PlayRate, BlendIn, BlendOut, StartTime, bLoop);

		PlaySequence_OnMulticast(Name, Slot, PlayRate, BlendIn, BlendOut, StartTime, bLoop);
	} else
	{
		PlaySequence_OnServer(Name, Slot, PlayRate, BlendIn, BlendOut, StartTime, bLoop);
	}
}

void ASNCharacterBase::PlaySequence_OnServer_Implementation(const FName& Name, const FName& Slot, float PlayRate, float BlendIn, float BlendOut, float StartTime, bool bLoop)
{
	PlaySequence(Name, Slot, PlayRate, BlendIn, BlendOut, StartTime, bLoop);
}

void ASNCharacterBase::PlaySequence_OnMulticast_Implementation(const FName& Name, const FName& Slot, float PlayRate, float BlendIn, float BlendOut, float StartTime, bool bLoop)
{
	InternalPlaySequence(Name, Slot, PlayRate, BlendIn, BlendOut, StartTime, bLoop);
}
void ASNCharacterBase::InternalPlaySequence(const FName& Name, const FName& Slot, float PlayRate, float BlendIn, float BlendOut, float StartTime, bool bLoop)
{
	USNAnimInstanceBase* AnimInstance(Cast<USNAnimInstanceBase>(GetAnimInstance()));

	if(AnimInstance != nullptr)
	{
		AnimInstance->PlayAnimationSequence(Name, Slot, PlayRate, BlendIn, BlendOut, StartTime, bLoop);
	}
}

void ASNCharacterBase::PlayMontage(const FName& Name, float PlayRate, float StartTime)
{
	if(SNUtility::IsServer(GetWorld()))
	{
		InternalPlayMontage(Name, PlayRate, StartTime);

		PlayMontage_OnMulticast(Name, PlayRate, StartTime);
	} else
	{
		PlayMontage_OnServer(Name, PlayRate, StartTime);
	}
}

void ASNCharacterBase::PlayMontage_OnServer_Implementation(const FName& Name, float PlayRate, float StartTime)
{
	PlayMontage(Name, PlayRate, StartTime);	
}

void ASNCharacterBase::PlayMontage_OnMulticast_Implementation(const FName& Name, float PlayRate, float StartTime)
{
	InternalPlayMontage(Name, PlayRate, StartTime);
}

void ASNCharacterBase::InternalPlayMontage(const FName& Name, float PlayRate, float StartTime)
{
	USNAnimInstanceBase* AnimInstance(Cast<USNAnimInstanceBase>(GetAnimInstance()));

	if(AnimInstance != nullptr)
	{
		AnimInstance->PlayAnimationMontage(Name, PlayRate, StartTime);
	}
}

void ASNCharacterBase::JumpMontageSection(const FName& Name, const FName& Section)
{
	if(SNUtility::IsServer(GetWorld()))
	{
		InternalJumpMontageSection(Name, Section);

		JumpMontageSection_OnMulticast(Name, Section);
	} else
	{
		JumpMontageSection_OnServer(Name, Section);
	}
}

void ASNCharacterBase::JumpMontageSection_OnServer_Implementation(const FName& Name, const FName& Section)
{
	JumpMontageSection(Name, Section);
}

void ASNCharacterBase::JumpMontageSection_OnMulticast_Implementation(const FName& Name, const FName& Section)
{
	InternalJumpMontageSection(Name, Section);
}

void ASNCharacterBase::InternalJumpMontageSection(const FName& Name, const FName& Section)
{
	USNAnimInstanceBase* AnimInstance(Cast<USNAnimInstanceBase>(GetAnimInstance()));

	if(AnimInstance != nullptr)
	{
		AnimInstance->JumpAnimationMontageSection(Name, Section);
	}
}



