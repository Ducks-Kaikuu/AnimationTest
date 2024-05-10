// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SNCharacterBase.generated.h"

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

	UFUNCTION(BlueprintCallable, Category="SN|Character", meta=(NotBlueprintThreadSafe))
	void SetAnimationState(const FName& Name);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	FName CurrentAnimationState = NAME_None;
};
