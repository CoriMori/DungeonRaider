// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Loot.h"
#include "CustomComponents/Grabber.h"

// Sets default values
ALoot::ALoot()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->OnComponentHit.AddDynamic(this, &ALoot::OnHit);		// set up a notification for when this component hits something blocking
	SetRootComponent(StaticMeshComponent);

	ScoreComponent = CreateDefaultSubobject<UScoreComponent>(TEXT("ScoreComponent"));
	AudioPlayerComponent = CreateDefaultSubobject<UAudioPlayer>(TEXT("AudioPlayerComponent"));
}


void ALoot::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherComp->GetClass() != UGrabber::StaticClass() && !ActorHasTag("Grabbed")) {
		AudioPlayerComponent->OnDropped.Broadcast();
	}
}

// Called when the game starts or when spawned
void ALoot::BeginPlay()
{
	Super::BeginPlay();
	AssignScoreValue();
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

