// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CustomComponents/ScoreComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "LootChest.generated.h"

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UNiagaraSystem> particleSystemAsset;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UNiagaraComponent> particleComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	AActor* placedActor; //actor placed in the chest
	
	UFUNCTION(BlueprintCallable)
	void CheckLoot(AActor* placedObj);
	void CalculateScore();
	bool CanBeScored();

	UScoreComponent* GetScoreComponent();

};
