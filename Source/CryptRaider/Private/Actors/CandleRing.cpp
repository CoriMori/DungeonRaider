// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/CandleRing.h"

// Sets default values
ACandleRing::ACandleRing()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SetRootComponent(StaticMeshComponent);

}

// Called when the game starts or when spawned
void ACandleRing::BeginPlay()
{
	Super::BeginPlay();

	SpawnCandles();
}

//spawn candles in a circle
void ACandleRing::SpawnCandles()
{
	TArray<FVector> candleLocations = GetCandleLocation(candleQuantity, circleRadius);
	for (int32 i = 0; i < candleLocations.Num(); i++) {
		TSubclassOf<AActor> candleType = GetRandomCandleVariant();
		AActor* candle = GetWorld()->SpawnActor<AActor>(candleType, candleLocations[i], FRotator{}, FActorSpawnParameters{});
		candle->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform); // attach to the root compoenent
	}
}

//get a random class from the Candle Variations array
TSubclassOf<AActor> ACandleRing::GetRandomCandleVariant()
{
	int32 randIndex = FMath::RandRange(0, CandleVariations.Num() - 1);

	return CandleVariations[randIndex];
}

//returns positions around a cirlce
TArray<FVector> ACandleRing::GetCandleLocation(int32 quantity, int32 radius) const
{
	TArray<FVector> positions;
	float angle = 360.0f / quantity;

	for (int32 i = 0; i < quantity; i++)
	{
		float tX = GetActorLocation().X + (radius * FMath::Cos((angle * i) * (PI / 180.0)));
		float tY = GetActorLocation().Y + (radius * FMath::Sin((angle * i) * (PI / 180.0)));
		positions.Add(FVector(tX, tY, GetActorLocation().Z));
	}

	return positions;
}


