// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CandleFlameController.generated.h"


//Component allowing material on candle flames to be swapped out easily
//Ideally this class would also change the point light color, but timelines can't go on actor components -> done in Blueprints instead
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CRYPTRAIDER_API UCandleFlameController : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCandleFlameController();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	UFUNCTION(BlueprintCallable)
	void SetFlameMaterial(TArray<UStaticMeshComponent*> Meshes, UMaterialInterface* NewMaterial);

};