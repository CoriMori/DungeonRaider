// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomComponents/ScoreComponent.h"
#include "GameFramework/Actor.h"
#include "Loot.generated.h"

/*Actor with a score component and a static mesh root
* Can be picked up and put in the loot chest to be scored
* Static mesh swapped out with whatever asset the loot should be
*/
UCLASS()
class CRYPTRAIDER_API ALoot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALoot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UScoreComponent> ScoreComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	void AssignScoreValue();

};
