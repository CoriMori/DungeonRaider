// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Loot.h"

// Sets default values
ALoot::ALoot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
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

//assign a random value for the loot if the score isn't already set
void ALoot::AssignScoreValue()
{
	if (!ScoreComponent) return;
	if (ScoreComponent->GetScore() != 0) return; // prevent us from overwritting any custom score values
	
	int32 randomScore = FMath::RandRange(100, 500);
	if (ActorHasTag("LowerDungeon")) { // adjust the range for loot in the lower part of the dungeon
		randomScore = FMath::RandRange(500, 1000);
	}
	ScoreComponent->SetScore(randomScore);
}

