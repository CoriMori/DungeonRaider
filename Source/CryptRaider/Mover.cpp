// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UMover::Move(const float& deltaTime)
{
	if (!shouldMove) return;

	FVector currentPos = GetOwner()->GetActorLocation();
	FVector targetPos = startPos + moveOffset;
	float speed = FVector::Distance(startPos, targetPos)/moveTime;

	FVector tPos = FMath::VInterpConstantTo(currentPos, targetPos, deltaTime, speed);
	GetOwner()->SetActorLocation(tPos);
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();
	startPos = GetOwner()->GetActorLocation();
	// ...
	
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Move(DeltaTime);
}

