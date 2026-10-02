// Fill out your copyright notice in the Description page of Project Settings.


#include "WrapZone.h"
#include "Components/BoxComponent.h"
#include "Engine/Engine.h"

// Sets default values
AWrapZone::AWrapZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox;

	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
}

// Called when the game starts or when spawned
void AWrapZone::BeginPlay()
{
	Super::BeginPlay();
	
	TriggerBox->OnComponentBeginOverlap.AddDynamic(
	this,
	&AWrapZone::OnTriggerBeginOverlap
);
	
}

// Called every frame
void AWrapZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWrapZone::OnTriggerBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			2.0f,
			FColor::Green,
			TEXT("WRAP OVERLAP")
		);
	}

	if (OtherActor && TargetActor)
	{
		OtherActor->SetActorLocation(TargetActor->GetActorLocation());
	}
}