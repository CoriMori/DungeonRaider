
#include "UI/WidgetBase.h"

UWidgetBase::UWidgetBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

void UWidgetBase::NativeConstruct() {
	Super::NativeConstruct();
}

void UWidgetBase::OnScoreChanged(int32 Score) {
	if (TXTScore) {
		TXTScore->SetText(FText::FromString("$ " + FString::FromInt(Score)));
	}
}