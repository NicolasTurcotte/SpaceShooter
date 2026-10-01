// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShipPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "InputAction.h"

// Sets default values
ASpaceShipPawn::ASpaceShipPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	ShipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	RootComponent = ShipMesh;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);

	Camera->SetRelativeLocation(FVector(-1000.0f, 0.0f, 1000.0f));
	Camera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));

}

// Called when the game starts or when spawned
void ASpaceShipPawn::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
				LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				if (InputMappingContext)
				{
					Subsystem->AddMappingContext(InputMappingContext, 0);
				}
			}
		}
	}
	
}

// Called every frame
void ASpaceShipPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASpaceShipPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput =
		Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (MoveAction)
		{
			EnhancedInput->BindAction(
				MoveAction,
				ETriggerEvent::Triggered,
				this,
				&ASpaceShipPawn::Move
			);
		}
	}
}

void ASpaceShipPawn::Move(const FInputActionValue& Value)
{
	const FVector2D Movement = Value.Get<FVector2D>();

	const FVector Direction(
		Movement.Y,
		Movement.X,
		0.0f
	);

	AddActorWorldOffset(Direction * MoveSpeed * GetWorld()->GetDeltaSeconds(), true);
}