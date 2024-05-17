// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Base/SNCharacterBase.h"

#include "SNDef.h"
#include "Animation/SNAnimInstanceBase.h"
#include "Animation/Components/SNLocomotionComponent.h"

// Sets default values
ASNCharacterBase::ASNCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASNCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASNCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASNCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ASNCharacterBase::SetCurrentState(const FName& Name)
{
	if(CurrentState != Name)
	{
		PreState = CurrentState;
		
		CurrentState = Name;

		SNPLUGIN_LOG(TEXT("State : %s"), *CurrentState.ToString());
	}
}

FName ASNCharacterBase::GetCurrentState() const {
	return CurrentState;
}

FName ASNCharacterBase::GetPrevState() const {
	return PreState;
}

bool ASNCharacterBase::IsCurrentState(const FName& State) const {
	return (CurrentState == State) ? true : false;
}

bool ASNCharacterBase::IsPreState(const FName& State) const {
	return (PreState == State) ? true : false;
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
	USNAnimInstanceBase* AnimInstance(Cast<USNAnimInstanceBase>(GetAnimInstance()));

	if(AnimInstance != nullptr)
	{
		AnimInstance->PlayAnimationSequence(Name, Slot, PlayRate, BlendIn, BlendOut, StartTime, bLoop);
	}
}

void ASNCharacterBase::PlayMontage(const FName& Name, float PlayRate, float StartTime)
{
	USNAnimInstanceBase* AnimInstance(Cast<USNAnimInstanceBase>(GetAnimInstance()));

	if(AnimInstance != nullptr)
	{
		AnimInstance->PlayAnimationMontage(Name, PlayRate, StartTime);
	}
}

void ASNCharacterBase::JumpMontageSection(const FName& Name, const FName& Section)
{
	USNAnimInstanceBase* AnimInstance(Cast<USNAnimInstanceBase>(GetAnimInstance()));

	if(AnimInstance != nullptr)
	{
		AnimInstance->JumpAnimationMontageSection(Name, Section);
	}
}


