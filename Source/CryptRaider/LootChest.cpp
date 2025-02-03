// Fill out your copyright notice in the Description page of Project Settings.

#include "LootChest.h"
#include "RaiderPlayerState.h"

// Sets default values
ALootChest::ALootChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALootChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALootChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (placedActor != nullptr) {
		CalculateScore();
	}

}

void ALootChest::CalculateScore()
{
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Green, TEXT("Calculating Score"));
	if (!CanBeScored()) { return; }
	//get playerstate so we can access player score
	ARaiderPlayerState* playerState = Cast<ARaiderPlayerState>(GetWorld()->GetFirstPlayerController()->PlayerState);

	//access the score component and add it to the player state score
	int32 actorScore = GetScoreComponent()->GetScore();
	int32 playerScore = playerState->GetPlayerScore();

	playerState->SetPlayerScore(playerScore + actorScore); //update the total score

	//play particles
	if(!IsValid(particleComponent)){
		particleComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(
			particleSystemAsset,
			RootComponent,
			NAME_None,
			FVector(0.0f, 0.0f, 15.0f),
			FRotator::ZeroRotator,
			FVector::OneVector,
			EAttachLocation::KeepRelativeOffset,
			true,
			ENCPoolMethod::None,
			true,
			true
		);
	}

	
	//hide the actor and mark it for disposal
	placedActor->SetActorHiddenInGame(true);
	placedActor->Destroy();
	placedActor = nullptr;
}

void ALootChest::CheckLoot(AActor* placedObj)
{
	placedActor = placedObj;
}

bool ALootChest::CanBeScored()
{
	//if the key is still being held and has a score component-> keep checking
	if (placedActor->ActorHasTag("Grabbed") && GetScoreComponent()) return false;

	//if the actor doesn't have a score component, set placed actor to null to stop checking
	if (!GetScoreComponent()) {
		placedActor = nullptr;
		return false;
	}

	return true;
}

UScoreComponent* ALootChest::GetScoreComponent()
{
	return placedActor->GetComponentByClass<UScoreComponent>();
}

