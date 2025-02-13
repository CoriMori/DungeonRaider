// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Loot.h"

// Sets default values
ALoot::ALoot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SetRootComponent(StaticMeshComponent);

	StaticMeshComponent->OnComponentHit.AddDynamic(this, &ALoot::OnHit);		// set up a notification for when this component hits something blocking
	ScoreComponent = CreateDefaultSubobject<UScoreComponent>(TEXT("ScoreComponent"));

	AudioPlayerComponent = CreateDefaultSubobject<UAudioPlayer>(TEXT("AudioPlayerComponent"));

}

void ALoot::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (WasPickedUp) {
		CheckOnGround();
		AudioPlayerComponent->PlayDropSound();
	}
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

void ALoot::CheckOnGround()
{
	//calculate start and end positions for the trace
	FVector startPos = GetActorLocation();
	FVector endPos = startPos + FVector(0.0f, 0.0f, 1.0f) * 100.0f;

	//send the trace out and return the results
	FHitResult result;
	GetWorld()->LineTraceSingleByChannel(result, startPos, endPos, ECollisionChannel::ECC_WorldStatic);

	DrawDebugLine(GetWorld(), startPos, endPos, FColor::Cyan, true);
	FString resultMsg = result.bBlockingHit ? "Blocking hit True" : "Blocking hit False";
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("Result: %s"), *resultMsg));
	if (!result.bBlockingHit) {
		WasPickedUp = true;
	}
	else {
		WasPickedUp = false;
	}
}

