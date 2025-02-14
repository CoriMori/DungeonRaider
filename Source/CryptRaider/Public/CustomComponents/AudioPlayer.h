// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AudioPlayer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDroppedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPickedUpDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UAudioPlayer : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SFX", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USoundBase> DropSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SFX", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USoundBase> PickupSound;

	bool DropSFXPlayed = true; //Tracks if the dropped sfx was already played ->set to true to prevent playing on spawn

	bool PickedUp = false;

public:	
	// Sets default values for this component's properties
	UAudioPlayer();

	UPROPERTY(BlueprintCallable)
	FDroppedDelegate OnDropped;
	UFUNCTION()
	void PlayDropSound();
	
	FPickedUpDelegate OnPickedUp;
	UFUNCTION()
	void PlayPickupSound();

	UFUNCTION(BlueprintCallable)
	bool GetDropSFXPlayed() const { return DropSFXPlayed; }

	UFUNCTION()
	void SetPickedUp(bool Value) { PickedUp = Value; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

};
