// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CustomComponents/ScoreComponent.h"
#include "Components/BoxComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "LootChest.generated.h"

//class for a chest that can accept a piece of loot -> triggers scoring updates and particle effects
UCLASS()
class CRYPTRAIDER_API ALootChest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALootChest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* Instead of spawning particles,
	* could attach a niagara system component to the actor
	* and play the particle system.
	* But this works too. Inconsequential for a project of this size.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UNiagaraSystem> particleSystemAsset;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UNiagaraComponent> particleComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> BoxComponent;
	TObjectPtr<AActor> placedActor; //actor placed in the chest

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SFX", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USoundBase> RewardSFX;

	void PlayRewardSFX();

	UFUNCTION(BlueprintCallable)
	void CheckLoot(AActor* placedObj);
	void CalculateScore();
	bool CanBeScored();

	UScoreComponent* GetScoreComponent();

};
