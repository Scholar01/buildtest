// Fill out your copyright notice in the Description page of Project Settings.


#include "CompassWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Border.h"
#include "Kismet/GameplayStatics.h"

class UGameplayStatics;

void UCompassWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Border = Cast<UBorder>(GetWidgetFromName(FName(TEXT("Border_63"))));
	TextBlock = Cast<UTextBlock>(GetWidgetFromName(FName(TEXT("TextBlock_Direction"))));
}

//
// TSharedRef<SWidget> UCompassWidget::RebuildWidget()
// {
// 	UE_LOG(LogTemp,Log,TEXT("rebuild"));
// 	TSharedRef<SWidget> Widget= Super::RebuildWidget();
// 	UCanvasPanel *RootWidget = Cast<UCanvasPanel>(GetRootWidget());
// 	UE_LOG(LogTemp,Log,TEXT("root:%s"),*RootWidget->GetName());
//
// 	if (RootWidget && WidgetTree)
// 	{
// 		TextBlock = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(),FName(TEXT("my text block")));
// 		RootWidget->AddChild(TextBlock);
// 	}
// 	return Widget;
// }

void UCompassWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	FRotator Rotator = PlayerController->GetRootComponent()->GetComponentRotation();
	double Angle = Rotator.Yaw;
	if (Angle < 0)
	{
		Angle += 360;
	}
	Border->SetRenderTransformAngle(Angle);
	int Azimuth = FMath::RoundToInt(Angle / 45);
	switch (Azimuth)
	{
	case 0:
		TextBlock->SetText(FText::FromString(TEXT("北")));
		break;
	case 1:
		TextBlock->SetText(FText::FromString(TEXT("东北")));
		break;
	case 2:
		TextBlock->SetText(FText::FromString(TEXT("东")));
		break;
	case 3:
		TextBlock->SetText(FText::FromString(TEXT("东南")));
		break;
	case 4:
		TextBlock->SetText(FText::FromString(TEXT("南")));
		break;
	case 5:
		TextBlock->SetText(FText::FromString(TEXT("西南")));
		break;
	case 6:
		TextBlock->SetText(FText::FromString(TEXT("西")));
		break;
	case 7:
		TextBlock->SetText(FText::FromString(TEXT("西北")));
		break;
	case 8:
		TextBlock->SetText(FText::FromString(TEXT("北")));
		break;
	default:
		TextBlock->SetText(FText::FromString(TEXT("?")));
		break;
	}
}
