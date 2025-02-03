// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "SkeletonKey.generated.h"

class UCurveFloat;
UCLASS()
class CRYPTRAIDER_API ASkeletonKey : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkeletonKey();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UCurveFloat* HeadTimelineCurve = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USplineComponent* SplinePath;

	UFUNCTION(BlueprintCallable)
	void SetKeyComponent(AActor* KeyActor) { keyObject = KeyActor; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FTimeline headTimeline;
	AActor* keyObject;

	UFUNCTION(BlueprintCallable)
	void StartKeyTimeline();

	UFUNCTION() //UFUNCTION is required for the timeline to find the function -> will not work without it
	void UpdateHeadPosition(float delta);

};
