// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AsteroidSpawner.generated.h"

class AAsteroid;

UCLASS()
class SPACESHOOTER_API AAsteroidSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAsteroidSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	TSubclassOf<AAsteroid> AsteroidClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	float MinSpawnDelay = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	float MaxSpawnDelay = 3.0f;

	void SpawnAsteroid();
	void ScheduleNextSpawn();

	FTimerHandle SpawnTimerHandle;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
