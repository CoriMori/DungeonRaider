// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AudioPlayer.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UAudioPlayer : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SFX", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USoundBase> DropSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SFX", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USoundBase> PickupSound;
public:	
	// Sets default values for this component's properties
	UAudioPlayer();

	UFUNCTION(BlueprintCallable, Category = "SFX")
	void PlayDropSound();

	void PlayPickupSound();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

};
