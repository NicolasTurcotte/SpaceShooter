// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SpaceShipPawn.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class AProjectile;

UCLASS()
class SPACESHOOTER_API ASpaceShipPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASpaceShipPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* ShipMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UCameraComponent* Camera;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* MoveForwardAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* TurnAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float MoveSpeed = 800.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float TurnSpeed = 120.0f;

	void MoveForward(const FInputActionValue& Value);
	void Turn(const FInputActionValue& Value);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* ShootAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	TSubclassOf<AProjectile> ProjectileClass;

	void Shoot();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player")
	int32 Lives = 3;
	
	UPROPERTY(BlueprintReadOnly, Category = "Player")
	int32 Score = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float ThrustAcceleration = 700.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float MaxSpeed = 1200.0f;

	FVector CurrentVelocity = FVector::ZeroVector;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void LoseLife();
	void AddScore(int32 Amount);
};
