// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/SlidingDoor.h"

// Sets default values
ASlidingDoor::ASlidingDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	StaticMeshComponentRoot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponentRoot"));
	SetRootComponent(StaticMeshComponentRoot);

	StaticMeshComponentPart1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponentPart1"));
	StaticMeshComponentPart1->SetupAttachment(GetRootComponent());

	StaticMeshComponentPart2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponentPart2"));
	StaticMeshComponentPart2->SetupAttachment(GetRootComponent());

	MoverComponent = CreateDefaultSubobject<UMover>(TEXT("MoverComponent"));
}

// Called when the game starts or when spawned
void ASlidingDoor::BeginPlay()
{
	Super::BeginPlay();
	
}


