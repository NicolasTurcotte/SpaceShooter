// Fill out your copyright notice in the Description page of Project Settings.


#include "AsteroidSpawner.h"
#include "Asteroid.h"
#include "TimerManager.h"

// Sets default values
AAsteroidSpawner::AAsteroidSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAsteroidSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	ScheduleNextSpawn();
	
}

// Called every frame
void AAsteroidSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAsteroidSpawner::ScheduleNextSpawn()
{
	const float Delay = FMath::RandRange(MinSpawnDelay, MaxSpawnDelay);

	GetWorldTimerManager().SetTimer(
		SpawnTimerHandle,
		this,
		&AAsteroidSpawner::SpawnAsteroid,
		Delay,
		false
	);
}

void AAsteroidSpawner::SpawnAsteroid()
{
	if (!AsteroidClass)
	{
		ScheduleNextSpawn();
		return;
	}

	const FVector Center = GetActorLocation();

	const float HorizontalOffset = 1000.0f;
	const float VerticalOffset = 550.0f;

	FVector SpawnLocation = Center;

	const int32 Side = FMath::RandRange(0, 3);

	switch (Side)
	{
	case 0: // Haut
		SpawnLocation += FVector(
			FMath::RandRange(-VerticalOffset, VerticalOffset),
			HorizontalOffset,
			0.0f
		);
		break;

	case 1: // Bas
		SpawnLocation += FVector(
			FMath::RandRange(-VerticalOffset, VerticalOffset),
			-HorizontalOffset,
			0.0f
		);
		break;

	case 2: // Gauche
		SpawnLocation += FVector(
			-HorizontalOffset,
			FMath::RandRange(-VerticalOffset, VerticalOffset),
			0.0f
		);
		break;

	case 3: // Droite
		SpawnLocation += FVector(
			HorizontalOffset,
			FMath::RandRange(-VerticalOffset, VerticalOffset),
			0.0f
		);
		break;
	}

	FActorSpawnParameters SpawnParams;

	GetWorld()->SpawnActor<AAsteroid>(
		AsteroidClass,
		SpawnLocation,
		FRotator::ZeroRotator,
		SpawnParams
	);

	ScheduleNextSpawn();
}