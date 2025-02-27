// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "WidgetBase.generated.h"

//Widget class requring a score text block -> main widget for the project
UCLASS()
class CRYPTRAIDER_API UWidgetBase : public UUserWidget
{
	GENERATED_BODY()
public:
	UWidgetBase(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> TXTScore;
	void OnScoreChanged(int32 Score); //handle what happens when the score changes
};
