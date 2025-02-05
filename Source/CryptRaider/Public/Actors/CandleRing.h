// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CandleRing.generated.h"

//Spawns a ring of candles in a perfect circle around a central static mesh component
UCLASS()
class CRYPTRAIDER_API ACandleRing : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACandleRing();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AActor>> CandleVariations; //array of candle classes
	UPROPERTY(EditAnywhere, meta = (DisplayName = "Candle Quantity"))
	int32 candleQuantity = 10;
	UPROPERTY(EditAnywhere, meta = (DisplayName = "Circle Radius"))
	int32 circleRadius = 100;

	void SpawnCandles();
	TArray<FVector> GetCandleLocation(int32 quantity, int32 radius) const;
	TSubclassOf<AActor> GetRandomCandleVariant();
};
