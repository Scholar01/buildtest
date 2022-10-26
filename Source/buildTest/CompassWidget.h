// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"
#include "CompassWidget.generated.h"

class UBorder;
/**
 * 
 */
UCLASS()
class BUILDTEST_API UCompassWidget : public UUserWidget
{
	GENERATED_BODY()


protected:
	virtual void NativeConstruct() override;

	// virtual TSharedRef<SWidget> RebuildWidget() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	UPROPERTY()
	UBorder* Border;
	UPROPERTY()
	UTextBlock* TextBlock;
};
