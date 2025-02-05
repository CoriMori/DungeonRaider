// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SplineComponent.h"
#include "CustomComponents/DoorKey.h"
#include "GameFramework/Actor.h"
#include "SkeletonKey.generated.h"


//Class for an actor that can unlock a door when a key is placed on them -> the key will follow the spline path
class UCurveFloat;
UCLASS()
class CRYPTRAIDER_API ASkeletonKey : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkeletonKey();

	UFUNCTION(BlueprintCallable)
	void SetKeyComponent(AActor* KeyActor) { keyObject = KeyActor; } 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UCurveFloat> HeadTimelineCurve = nullptr; // curve for the timeline

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UDoorKey> DoorKeyComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> SplinePath; // specific spline path for the key to follow
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> BoxComponent;

	FTimeline headTimeline;
	TObjectPtr<AActor> keyObject;

	UFUNCTION(BlueprintCallable)
	void StartKeyTimeline();

	UFUNCTION() //UFUNCTION is required for the timeline to find the function -> will not work without it
	void UpdateHeadPosition(float delta);

};
