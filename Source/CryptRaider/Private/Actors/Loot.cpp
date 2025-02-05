// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Loot.h"

// Sets default values
ALoot::ALoot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SetRootComponent(StaticMeshComponent);

	ScoreComponent = CreateDefaultSubobject<UScoreComponent>(TEXT("ScoreComponent"));

}

// Called when the game starts or when spawned
void ALoot::BeginPlay()
{
	Super::BeginPlay();
	AssignScoreValue();
}

// Called every frame
void ALoot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALoot::AssignScoreValue()
{
	if (!ScoreComponent) return;
	if (!ScoreComponent->GetScore()) { // prevent us from overwritting any custom score values
		int32 randomScore = FMath::RandRange(100, 500);
		if (ActorHasTag("LowerDungeon")) {
			randomScore = FMath::RandRange(500, 1000);
		}
		ScoreComponent->SetScore(randomScore);

	}
}

