// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Player/CryptRaiderCharacter.h"
#include "Grabber.generated.h"

//Component to allow player to grab an object using PhysicsHandle
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UGrabber : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UFUNCTION(BlueprintCallable)
	void Grab();
	UFUNCTION(BlueprintCallable)
	void Release();
	UFUNCTION(BlueprintCallable)
	void Throw();
	void UpdateTargetLocationAndRotation();
	bool GeomTrace(FHitResult& outResult) const;
	UPhysicsHandleComponent* GetPhysicsHandle() const;
	ACryptRaiderCharacter* GetOwningPlayer() const;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "Max Grab Distance"))
	float grabDist = 400.0f; // the furthest point we're checking for objects to grab
	UPROPERTY(EditAnywhere, meta = (DisplayName = "Grab Radius"))
	float grabRadius = 100.0f; // the radius of the sphere geom trace
	UPROPERTY(EditAnywhere, meta = (DisplayName = "Hold Distance"))
	float holdDist = 200.0f; // how far the held object will be from physics handle
	UPROPERTY(EditAnywhere, meta = (DisplayName = "Throw Force"))
	float throwForce = 100.0f; // determines how hard the applied impulse will be
};
