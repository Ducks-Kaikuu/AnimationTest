// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimationTest/Character/Player/ATPlayer.h"

#include "Character/SNPlayerController.h"

void AATPlayer::BeginPlay()
{
	Super::BeginPlay();

	ASNPlayerController* PlayerController(Cast<ASNPlayerController>(GetController()));

	if(PlayerController)
	{
		PlayerController->EnabledInputType(FName(TEXT("Player")));
	}
}
