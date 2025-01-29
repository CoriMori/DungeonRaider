// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CandleRing.generated.h"

UCLASS()
class CRYPTRAIDER_API ACandleRing : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACandleRing();

	UFUNCTION(BlueprintCallable)
	TArray<FVector> GetCandleLocation(int32 quantity, int32 radius) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	

};
