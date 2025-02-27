// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CustomComponents/Mover.h"
#include "DoorKey.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnKeyCorrect);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UDoorKey : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorKey();

	/*event delegate->assigned in blueprints as a workaround for a BlueprintImplementableEvent
	* Allows for visual effects to occur as a result of the key being correct
	* Broadcasted in UnlockDoor()
	*/
	UPROPERTY(BlueprintAssignable)
	FOnKeyCorrect OnKeyCorrectDelegate; 
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	//Variables
	UPROPERTY(EditAnywhere, meta = (DisplayName = "Affected Door"))
	AActor* door; // actual door that will be effected by this component
	UPROPERTY(EditAnywhere, meta = (DisplayName = "Key"))
	FName doorKey; // name of the key -> key actor needs to have a tag that matches whatever this is set as
	TObjectPtr<AActor> placedActor; // reference to the actor that we're trying to check
	TObjectPtr<UMover> moverComp;	// mover component -> used in UnlockDoor()
	bool isLocked = true; // tracks the locked status of the door

	//Functions
	UFUNCTION(BlueprintCallable)
	void CheckKey(AActor* placedObj); // Toggles checking on and off for the key -> should be called on start and end overlap
	void UnlockDoor();	// actually unlocks the door
	void SetMover(UMover* mover); // sets the mover component from the door pntr -> Logs an error if the mover doesn't exsist
	bool CanUnlock(); // checks if we can even unlock the door
	bool CheckDoor(AActor* doorToCheck) const; // checks if the door passed in exsists -> Logs an error if it doesn't

};
