// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomComponents/Grabber.h"
#include "Actors/Loot.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UpdateTargetLocationAndRotation();
}

//grab an object
void UGrabber::Grab()
{
	if (GetPhysicsHandle() == nullptr) return; // skip everything if we're missing the physics handle

	FHitResult result;
	if (!GeomTrace(result)) return; //do nothing if we didn't hit anything
	
	//try to play pick up sound
	UAudioPlayer* AudioPlayer = result.GetActor()->GetComponentByClass<UAudioPlayer>();
	if (AudioPlayer != nullptr) {
		AudioPlayer->OnPickedUp.Broadcast();
	}
	UPrimitiveComponent* heldComp = result.GetComponent(); // get the component we hit
	heldComp->GetOwner()->Tags.Add("Grabbed"); // assign the grabbed tag to the components owner
	heldComp->WakeAllRigidBodies(); // wake up the rigid bodies in case they went to sleep
	GetPhysicsHandle()->GrabComponentAtLocationWithRotation(heldComp, NAME_None, result.ImpactPoint, GetComponentRotation()); // grab the component
	GetOwningPlayer()->bHoldingObject = true; //let the owner of the grabber to know that we grabbed something
}

//release a held object if we have one
void UGrabber::Release()
{
	if (GetPhysicsHandle()->GetGrabbedComponent() == nullptr) return;
	GetPhysicsHandle()->GetGrabbedComponent()->GetOwner()->Tags.Remove("Grabbed"); //remove the grabbed tag
	GetPhysicsHandle()->GetGrabbedComponent()->WakeAllRigidBodies(); // wake the rigid bodies again in case they went to sleep
	GetPhysicsHandle()->ReleaseComponent(); // release the held object
	GetOwningPlayer()->bHoldingObject = false; //update the player
}

//Apply an impulse to the held object to throw it
void UGrabber::Throw()
{
	if (GetPhysicsHandle()->GetGrabbedComponent() == nullptr) return;
	FVector dir = GetForwardVector() * throwForce; //calculate the impulse direction
	GetPhysicsHandle()->GetGrabbedComponent()->AddImpulse(dir, NAME_None, true); // add the impulse on the held object
	Release(); // then release the object
}



//update the grabbed objects location and rotation
void UGrabber::UpdateTargetLocationAndRotation()
{

	if (GetPhysicsHandle() == nullptr || GetPhysicsHandle()->GetGrabbedComponent() == nullptr) return;
	FRotator targetRot;
	FVector targetPos;
	if (GetOwningPlayer()->bRotatingObject) { // check if we're trying to rotate the object
		//get the objects rotation
		GetPhysicsHandle()->GetTargetLocationAndRotation(targetPos, targetRot); //putting targetPos in as a placeholder, it will be reassigned later
		
		//update the rotation with the hijacked look values
		targetRot.Roll = GetOwningPlayer()->LookAxisVector.X + targetRot.Roll;
		targetRot.Pitch = GetOwningPlayer()->LookAxisVector.Y + targetRot.Pitch;
	}
	else { //otherwise just use the grabbers rotation
		targetRot = GetComponentRotation();
	}

	targetPos = GetComponentLocation() + GetForwardVector() * holdDist;
	GetPhysicsHandle()->SetTargetLocationAndRotation(targetPos, targetRot);
}

//fire a sphere trace to detect props
bool UGrabber::GeomTrace(FHitResult& outResult) const
{
	//calculate start and end positions for the trace
	FVector startPos = GetComponentLocation();
	FVector endPos = startPos + GetForwardVector() * grabDist;

	FCollisionShape sphere = FCollisionShape::MakeSphere(grabRadius); // make the shape for the trace
	//send the trace out and return the results
	return GetWorld()->SweepSingleByChannel(outResult, startPos, endPos,
		FQuat::Identity, ECC_GameTraceChannel2, sphere);
}

//helper function to get the physics handle component -> sends out an error log if it's missing
UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	UPhysicsHandleComponent* result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (result == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Grabber requires a UPhysicsHandleComponent."));
	}

	return result;
}

//helper function to get the owning player of this component
ACryptRaiderCharacter* UGrabber::GetOwningPlayer() const
{
	return Cast<ACryptRaiderCharacter>(GetOwner());
}

