// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomComponents/AudioPlayer.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UAudioPlayer::UAudioPlayer()
{
	OnPickedUp.AddDynamic(this, &UAudioPlayer::PlayPickupSound);
	OnDropped.AddDynamic(this, &UAudioPlayer::PlayDropSound);
}

void UAudioPlayer::PlayDropSound()
{
	if (DropSound == nullptr) return;
	if (DropSFXPlayed || PickedUp) return;
	DropSFXPlayed = true;
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), DropSound, GetOwner()->GetActorLocation());

}

void UAudioPlayer::PlayPickupSound()
{
	DropSFXPlayed = false;
	if (PickupSound == nullptr) return;
	PickedUp = true;
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), PickupSound, GetOwner()->GetActorLocation());

	FTimerHandle PickedUpHandle;
	FTimerDelegate PickedUpDel;
	PickedUpDel.BindUFunction(this, FName("SetPickedUp"), false);
	GetOwner()->GetWorldTimerManager().SetTimer(PickedUpHandle, PickedUpDel, 0.1, false);
}


// Called when the game starts
void UAudioPlayer::BeginPlay()
{
	Super::BeginPlay();
}


