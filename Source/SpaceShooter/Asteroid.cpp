// Fill out your copyright notice in the Description page of Project Settings.


#include "Asteroid.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAsteroid::AAsteroid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	AsteroidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AsteroidMesh"));
	RootComponent = AsteroidMesh;

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
	MovementComponent->InitialSpeed = 400.0f;
	MovementComponent->MaxSpeed = 400.0f;
	MovementComponent->ProjectileGravityScale = 0.0f;

	InitialLifeSpan = 10.0f;

}

// Called when the game starts or when spawned
void AAsteroid::BeginPlay()
{
	Super::BeginPlay();
	
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (PlayerPawn && MovementComponent)
	{
		const FVector Direction =
			(PlayerPawn->GetActorLocation() - GetActorLocation()).GetSafeNormal();

		MovementComponent->Velocity = Direction * MovementComponent->InitialSpeed;
	}
	
}

// Called every frame
void AAsteroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

