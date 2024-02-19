// Fill out your copyright notice in the Description page of Project Settings.


#include "Diver.h"
#include "Components/InputComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ADiver::ADiver() {
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 300.f;
	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(CameraBoom);
}

// Called when the game starts or when spawned
void ADiver::BeginPlay() {
	Super::BeginPlay();
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller)) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
			Subsystem->AddMappingContext(DiverContext, 0);
		}
	}
}

void ADiver::Move(const FInputActionValue& Value) {
	const FVector2D MovementVector = Value.Get<FVector2D>();
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator CameraRotation(Rotation.Pitch, Rotation.Yaw, Rotation.Roll);
	const FVector ForwardDirection = UKismetMathLibrary::GetForwardVector(CameraRotation);
	const FVector RightDirection = UKismetMathLibrary::GetRightVector(CameraRotation);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Some variable values: x: %f, y: %f"), ForwardDirection.X, ForwardDirection.Z));
	AddMovementInput(ForwardDirection, MovementVector.Y * 2.f, true);
	AddMovementInput(RightDirection, MovementVector.X * 2.f, true);
}

void ADiver::Look(const FInputActionValue& Value) {
	const FVector2D LookAxisVector = Value.Get<FVector2D>();
	AddControllerPitchInput(LookAxisVector.Y);
	AddControllerYawInput(LookAxisVector.X);
}

// Called every frame
void ADiver::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADiver::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &ADiver::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ADiver::Look);
	}
}

