// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimationTest/Character/Player/Action/ATActionJump.h"

#include "AnimationTest/Character/Player/ATPlayer.h"

void UATActionJump::ExecAction(const FInputActionValue& InputActionValue)
{
	Super::ExecAction(InputActionValue);

	AATPlayer* Player(GetOwner<AATPlayer>());

	if(Player != nullptr)
	{
		if(bDoJump == false)
		{
			Player->LandedDelegate.AddDynamic(this, &UATActionJump::OnLanded);
			
			Player->Jump();

			Player->SetCurrentState(TEXT("LandIdleJump"));

			Player->PlayMontage(TEXT("LandIdleJump"));
			
			bDoJump = true;
		}
	}
}

void UATActionJump::OnLanded(const FHitResult& HitResult)
{
	bDoJump = false;
	
	AATPlayer* Player(GetOwner<AATPlayer>());
	
	if(Player != nullptr){
		
		Player->JumpMontageSection(TEXT("LandIdleJump"), TEXT("End"));
		
		Player->LandedDelegate.RemoveDynamic(this, &UATActionJump::OnLanded);

		Player->SetCurrentState(TEXT("NormalIdle"));
	}
}

