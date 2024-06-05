// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimationTest/Character/Player/Action/ATActionMove.h"

#include "Animation/SNAnimInstanceBase.h"
#include "Animation/Components/SNLocomotionComponent.h"
#include "AnimationTest/Character/Player/ATPlayer.h"
#include "Curves/CurveVector.h"

void UATActionMove::ExecAction(const FInputActionValue& InputActionValue)
{
	Super::ExecAction(InputActionValue);

	AATPlayer* Player(GetOwner<AATPlayer>());

	if(Player != nullptr)
	{
		float Mag =InputActionValue.GetMagnitude();
		
		if(Mag < 0.1f)
		{
			Player->SetCurrentState(FName(TEXT("NormalIdle")), ECharacterStateType::Lower);	
		} else
		{
			Player->SetCurrentState(FName(TEXT("LandMove")), ECharacterStateType::Lower);
			
			Player->SetBlendspaceParam(FName(TEXT("LandMove")), FVector(InputActionValue[0] * 100.0f, InputActionValue[1] * 100.0f, 0.0f));

			if(USNLocomotionComponent* LocomotionComponent = Player->GetLocomotionComponent()){

				float MaxSpeed = LocomotionComponent->GetMaxSpeed();
				
				FVector2D Value(InputActionValue[0] * MaxSpeed, InputActionValue[1]*MaxSpeed);
				
				LocomotionComponent->MoveGround(Value);
			} else
			{
				FRotator ControlRotation(Player->GetControlRotation());
				
				FVector FrontRear = FRotationMatrix(FRotator(0.0, ControlRotation.Yaw, 0.0)).GetUnitAxis(EAxis::X);
				
				float SignX = (InputActionValue[1] > 0) ? 1.0f : -1.0f;
				
				FVector SpeedX(VelocityCurve->GetVectorValue(FMath::Abs(InputActionValue[1])));
				
				Player->AddMovementInput(FrontRear, SpeedX.X* 100.0f * SignX);

				FVector RightLeft = FRotationMatrix(FRotator(0.0, ControlRotation.Yaw, 0.0)).GetUnitAxis(EAxis::Y);
				
				float SignY = (InputActionValue[0] > 0) ? 1.0f : -1.0f;
				
				FVector SpeedY(VelocityCurve->GetVectorValue(FMath::Abs(InputActionValue[0])));
				
				Player->AddMovementInput(RightLeft, SpeedY.X * 100.0f * SignY);
			}
		}
	}
}
