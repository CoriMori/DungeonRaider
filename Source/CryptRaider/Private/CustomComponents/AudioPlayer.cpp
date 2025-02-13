// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomComponents/AudioPlayer.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UAudioPlayer::UAudioPlayer()
{

}

void UAudioPlayer::PlayDropSound()
{
	if (DropSound == nullptr) return;
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), DropSound, GetOwner()->GetActorLocation());
}

void UAudioPlayer::PlayPickupSound()
{
	if (PickupSound == nullptr) return;
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), PickupSound, GetOwner()->GetActorLocation());
}


// Called when the game starts
void UAudioPlayer::BeginPlay()
{
	Super::BeginPlay();
}


