// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/SkeletonKey.h"

// Sets default values
ASkeletonKey::ASkeletonKey()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SetRootComponent(StaticMeshComponent);
	
	SplinePath = CreateDefaultSubobject<USplineComponent>(TEXT("SplinePath"));
	SplinePath->SetupAttachment(GetRootComponent());

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(GetRootComponent());

	DoorKeyComponent = CreateDefaultSubobject<UDoorKey>(TEXT("DoorKeyComponent"));
}

// Called when the game starts or when spawned
void ASkeletonKey::BeginPlay()
{
	Super::BeginPlay();

	SplinePath = GetComponentByClass<USplineComponent>();

	FOnTimelineFloat ProgressUpdate;
	ProgressUpdate.BindDynamic(this, &ASkeletonKey::UpdateHeadPosition);

	headTimeline.AddInterpFloat(HeadTimelineCurve, ProgressUpdate); // add the info to the timeline itself
}

// Called every frame
void ASkeletonKey::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	headTimeline.TickTimeline(DeltaTime);
}

void ASkeletonKey::StartKeyTimeline()
{
	headTimeline.Play();
}

void ASkeletonKey::UpdateHeadPosition(float delta)
{
	// leave if we're missing something important
	if (!SplinePath || !keyObject) return;
	
	//disable physics simulation
	UPrimitiveComponent* root = Cast<UPrimitiveComponent>(keyObject->GetRootComponent());
	root->SetSimulatePhysics(false);

	float dist = delta * SplinePath->GetSplineLength();

	FVector pos = SplinePath->GetLocationAtDistanceAlongSpline(dist, ESplineCoordinateSpace::World);
	//FRotator rot = SplinePath->GetRotationAtDistanceAlongSpline(dist, ESplineCoordinateSpace::World);
	FRotator rot = FRotator(0.0f, -90.0f, 110.0f);

	keyObject->SetActorLocationAndRotation(pos, rot);
}


