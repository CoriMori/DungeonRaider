// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomComponents/Grabber.h"

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
	if (GetPhysicsHandle() == nullptr) return;

	FHitResult result;

	if (GeomTrace(result)) {
		UPrimitiveComponent* heldComp = result.GetComponent();
		//DrawDebugSphere(GetWorld(), result.ImpactPoint, 5.0f, 16, FColor::Cyan, false, 5.0f);
		heldComp->GetOwner()->Tags.Add("Grabbed");
		heldComp->WakeAllRigidBodies();
		GetPhysicsHandle()->GrabComponentAtLocationWithRotation(heldComp, NAME_None, result.ImpactPoint, GetComponentRotation());
		GetOwningPlayer()->bHoldingObject = true;
	}
}

void UGrabber::Release()
{
	if (GetPhysicsHandle()->GetGrabbedComponent() == nullptr) return;
	GetPhysicsHandle()->GetGrabbedComponent()->GetOwner()->Tags.Remove("Grabbed");
	GetPhysicsHandle()->GetGrabbedComponent()->WakeAllRigidBodies();
	GetPhysicsHandle()->ReleaseComponent();
	GetOwningPlayer()->bHoldingObject = false;
}

void UGrabber::Throw()
{
	if (GetPhysicsHandle()->GetGrabbedComponent() == nullptr) return;
	FVector dir = GetForwardVector() * throwForce;
	GetPhysicsHandle()->GetGrabbedComponent()->AddImpulse(dir, NAME_None, true);
	Release();
}



//update the grabbed objects location
void UGrabber::UpdateTargetLocationAndRotation()
{

	if (GetPhysicsHandle() == nullptr || GetPhysicsHandle()->GetGrabbedComponent() == nullptr) return;
	FRotator targetRot;
	FVector targetPos;
	if (GetOwningPlayer()->bRotatingObject) {
		GetPhysicsHandle()->GetTargetLocationAndRotation(targetPos, targetRot); //putting targetPos in as a placeholder, it will be reassigned later
		targetRot.Roll = GetOwningPlayer()->LookAxisVector.X + targetRot.Roll;
		targetRot.Pitch = GetOwningPlayer()->LookAxisVector.Y + targetRot.Pitch;
	}
	else {
		targetRot = GetComponentRotation();
	}

	targetPos = GetComponentLocation() + GetForwardVector() * holdDist;
	GetPhysicsHandle()->SetTargetLocationAndRotation(targetPos, targetRot);
}

//fire a sphere trace to detect props
bool UGrabber::GeomTrace(FHitResult& outResult) const
{
	FVector startPos = GetComponentLocation();
	FVector endPos = startPos + GetForwardVector() * grabDist;

	FCollisionShape sphere = FCollisionShape::MakeSphere(grabRadius);
	//DrawDebugSphere(GetWorld(), endPos, grabRadius, 16, FColor::Blue, true);
	//DrawDebugLine(GetWorld(), startPos, endPos, FColor::Red, true);
	return GetWorld()->SweepSingleByChannel(outResult, startPos, endPos,
		FQuat::Identity, ECC_GameTraceChannel2, sphere);
}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	UPhysicsHandleComponent* result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (result == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Grabber requires a UPhysicsHandleComponent."));
	}

	return result;
}

ACryptRaiderCharacter* UGrabber::GetOwningPlayer() const
{
	return Cast<ACryptRaiderCharacter>(GetOwner());
}

