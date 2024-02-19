// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Diver.generated.h"

class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class TFM_API ADiver : public ACharacter {
	GENERATED_BODY()
	public:
		ADiver();
		virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
		virtual void Tick(float DeltaTime) override;
	protected:	
		virtual void BeginPlay() override;

		UPROPERTY(EditAnywhere, Category = Input)
		UInputMappingContext* DiverContext;

		UPROPERTY(EditAnywhere, Category = Input)
		UInputAction* MovementAction;

		UPROPERTY(EditAnywhere, Category = Input)
		UInputAction* LookAction;

		void Move(const FInputActionValue& Value);
		void Look(const FInputActionValue& Value);
	private:
		UPROPERTY(VisibleAnywhere)
		USpringArmComponent* CameraBoom;

		UPROPERTY(VisibleAnywhere)
		UCameraComponent* ViewCamera;
		
};
