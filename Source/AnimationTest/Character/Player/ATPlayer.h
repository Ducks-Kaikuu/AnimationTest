// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Base/SNPlayerBase.h"
#include "ATPlayer.generated.h"

/**
 * 
 */
UCLASS()
class ANIMATIONTEST_API AATPlayer : public ASNPlayerBase
{
	GENERATED_BODY()

protected:
	
	virtual void BeginPlay() override;
};
