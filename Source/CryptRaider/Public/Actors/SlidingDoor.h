// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CustomComponents/Mover.h"
#include "SlidingDoor.generated.h"

//Simple class for a door that can move
UCLASS()
class CRYPTRAIDER_API ASlidingDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASlidingDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	/*static meshes that will make up the sliding door
	* I would normally do this in Blueprints
	* but since I know that there are 3 static meshes required to make a whole wall
	* I decided to do it in code to populate this class with something other than the required mover.
	* Best practice would be to leave out the static meshes since its design sided instead of function sided.
	*/

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponentRoot;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponentPart1;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponentPart2;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UMover> MoverComponent; //required mover for the door

};
