// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"

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
	UpdateTargetLocation();
}

//grab an object
void UGrabber::Grab()
{
	if (GetPhysicsHandle() == nullptr) return;

	FHitResult result;

	if (GeomTrace(result)) {
		UPrimitiveComponent* heldComp = result.GetComponent();
		heldComp->GetOwner()->Tags.Add("Grabbed");
		heldComp->WakeAllRigidBodies();
		GetPhysicsHandle()->GrabComponentAtLocationWithRotation(heldComp, NAME_None, result.ImpactPoint, GetComponentRotation());
	}
}

void UGrabber::Release()
{
	if (GetPhysicsHandle()->GetGrabbedComponent() == nullptr) return;
	GetPhysicsHandle()->GetGrabbedComponent()->GetOwner()->Tags.Remove("Grabbed");
	GetPhysicsHandle()->GetGrabbedComponent()->WakeAllRigidBodies();
	GetPhysicsHandle()->ReleaseComponent();
}

void UGrabber::Throw()
{
	if (GetPhysicsHandle()->GetGrabbedComponent() == nullptr) return;
	FVector dir = GetForwardVector() * throwForce;
	GetPhysicsHandle()->GetGrabbedComponent()->AddImpulse(dir, NAME_None, true);
	Release();
}

//update the grabbed objects location
void UGrabber::UpdateTargetLocation()
{
	if (GetPhysicsHandle() == nullptr || GetPhysicsHandle()->GetGrabbedComponent() == nullptr) return;

	FVector targetPos = GetComponentLocation() + GetForwardVector() * holdDist;
	GetPhysicsHandle()->SetTargetLocationAndRotation(targetPos, GetComponentRotation());
}

//fire a sphere trace to detect props
bool UGrabber::GeomTrace(FHitResult& outResult) const
{
	FVector startPos = GetComponentLocation();
	FVector endPos = startPos + GetForwardVector() * grabDist;

	FCollisionShape sphere = FCollisionShape::MakeSphere(grabRadius);
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

