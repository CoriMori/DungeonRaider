// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomComponents/CandleFlameController.h"

// Sets default values for this component's properties
UCandleFlameController::UCandleFlameController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCandleFlameController::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UCandleFlameController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UCandleFlameController::SetFlameMaterial(TArray<UStaticMeshComponent*> Meshes, UMaterialInterface* NewMaterial)
{
	for(UStaticMeshComponent* m : Meshes)
	{
		m->SetMaterial(0, NewMaterial);
	}
}

