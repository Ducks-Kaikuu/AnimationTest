// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimationTest/Scene/ATSceneDirector.h"

// Sets default values
AATSceneDirector::AATSceneDirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AATSceneDirector::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AATSceneDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

