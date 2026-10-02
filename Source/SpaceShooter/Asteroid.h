// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/Actor.h"
#include "Asteroid.generated.h"

UCLASS()
class SPACESHOOTER_API AAsteroid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAsteroid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* AsteroidMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	class UProjectileMovementComponent* MovementComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	int32 MinHitsToDestroy = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	int32 MaxHitsToDestroy = 3;

	int32 HitsRemaining;
	
	UFUNCTION()
	void OnAsteroidOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Effects")
	void PlayDestroyEffect();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
