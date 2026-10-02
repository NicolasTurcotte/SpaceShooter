// Fill out your copyright notice in the Description page of Project Settings.


#include "Asteroid.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "SpaceShipPawn.h"

// Sets default values
AAsteroid::AAsteroid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	AsteroidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AsteroidMesh"));
	RootComponent = AsteroidMesh;
	
	AsteroidMesh->SetGenerateOverlapEvents(true);
	AsteroidMesh->OnComponentBeginOverlap.AddDynamic(
		this,
		&AAsteroid::OnAsteroidOverlap
	);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
	MovementComponent->InitialSpeed = 200.0f;
	MovementComponent->MaxSpeed = 200.0f;
	MovementComponent->ProjectileGravityScale = 0.0f;

	InitialLifeSpan = 10.0f;

}

// Called when the game starts or when spawned
void AAsteroid::BeginPlay()
{
	Super::BeginPlay();
	
	HitsRemaining = FMath::RandRange(MinHitsToDestroy, MaxHitsToDestroy);
	
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

void AAsteroid::OnAsteroidOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	if (AProjectile* Projectile = Cast<AProjectile>(OtherActor))
	{
		Projectile->Destroy();

		HitsRemaining--;

		if (HitsRemaining <= 0)
		{
			if (APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
			{
				if (ASpaceShipPawn* Player = Cast<ASpaceShipPawn>(PlayerPawn))
				{
					Player->AddScore(100);
				}
			}

			PlayDestroyEffect();
		}
	}
	
	if (ASpaceShipPawn* Player = Cast<ASpaceShipPawn>(OtherActor))
	{
		Player->LoseLife();
		Destroy();
	}
}