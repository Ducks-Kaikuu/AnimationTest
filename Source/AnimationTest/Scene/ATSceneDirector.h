// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Scene/SNSceneBase.h"
#include "ATSceneDirector.generated.h"

UCLASS()
class ANIMATIONTEST_API AATSceneDirector : public ASNSceneBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AATSceneDirector();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
