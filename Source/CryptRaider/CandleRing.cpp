// Fill out your copyright notice in the Description page of Project Settings.


#include "CandleRing.h"

// Sets default values
ACandleRing::ACandleRing()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACandleRing::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACandleRing::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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


