// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimationTest/Character/Player/Action/ATActionAim.h"

#include "AnimationTest/Character/Player/ATPlayer.h"

void UATActionAim::ExecAction(const FInputActionValue& InputActionValue)
{
	Super::ExecAction(InputActionValue);

	AATPlayer* Player(GetOwner<AATPlayer>());

	if(Player != nullptr)
	{
		if(InputActionValue.Get<bool>() == true)
		{
			Player->SetCurrentState(TEXT("LandAim"), ECharacterStateType::Upper);
		} else
		{
			Player->SetCurrentState(TEXT(""), ECharacterStateType::Upper);
		}
	}
}
