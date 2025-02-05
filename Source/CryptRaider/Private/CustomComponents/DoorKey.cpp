// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomComponents/DoorKey.h"

// Sets default values for this component's properties
UDoorKey::UDoorKey()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UDoorKey::BeginPlay()
{
	Super::BeginPlay();

	if (!CheckDoor(door)) return; // make sure we have a door before setting the mover
	SetMover(door->GetComponentByClass<UMover>()); // set the mover so we can unlock the door
}


// Called every frame
void UDoorKey::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//if we have an actor to check, try to unlock the door
	if (placedActor != nullptr) {
		UnlockDoor();
	}
}

//unlock the door
void UDoorKey::UnlockDoor()
{
	if (!CanUnlock()) return; // check if it can be unlocked
	OnKeyCorrectDelegate.Broadcast();
	isLocked = false; // set the door as unlocked
	moverComp->SetShouldMove(true); // trigger the door movement
	placedActor = nullptr; // reset the placed actor so we don't keep trying to unlock the door
}

//toggles whether or not we should check the key
void UDoorKey::CheckKey(AActor* placedObj)
{
	if (!isLocked) return; //don't kick anything off if the door is already unlocked
	placedActor = placedObj;
}

//sets the mover componenet from the door reference -> sends out an error log if the mover component is missing from the door
void UDoorKey::SetMover(UMover* mover)
{
	if (mover != nullptr) { 
		moverComp = mover;
		return;
	}

	UE_LOG(LogTemp, Error, TEXT("Door Actor has no valid mover compoenent."));
}


//check if we can unlock the door or not
bool UDoorKey::CanUnlock()
{
	//if the key is still being held, but it has the right tag -> keep checking
	if (placedActor->ActorHasTag("Grabbed") && placedActor->ActorHasTag(doorKey)) return false;

	//otherwise if the mover is missing or the key is wrong, set the placed actor to null to stop checking
	if (moverComp == nullptr || !placedActor->ActorHasTag(doorKey)) { 
		placedActor = nullptr;
		return false;
	}

	return true;
}

//check if we have a valid door -> sends out an error log if it hasn't been assigned
bool UDoorKey::CheckDoor(AActor* doorToCheck) const
{
	if (doorToCheck != nullptr) return true;

	UE_LOG(LogTemp, Error, TEXT("No door has been set."));
	return false;
}


