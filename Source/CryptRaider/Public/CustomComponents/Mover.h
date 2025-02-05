// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Mover.generated.h"

//Component allows an object to move a certain distance
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UMover : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMover();

	void SetShouldMove(bool value){ shouldMove = value; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void Move(const float& deltaTime);
	FVector startPos; 
	UPROPERTY(EditAnywhere, meta = (DisplayName = "Move Offset"))
	FVector moveOffset;
	UPROPERTY(EditAnywhere, meta = (DisplayName = "Move Time"))
	float moveTime;
	bool shouldMove = false;
};
