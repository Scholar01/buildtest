// Fill out your copyright notice in the Description page of Project Settings.


#include "NotificationWidget.h"

#include "Components/Button.h"

void UNotificationWidget::OpenNotification()
{
	this->GetWidgetFromName("Overlay_41")->SetVisibility(Visibility);
	this->PlayWidgetAnimation("FadeIn");
}

void UNotificationWidget::NativeConstruct()
{
	UE_LOG(LogTemp, Log, TEXT("NativeConstruct"));
	Super::NativeConstruct();

	FScriptDelegate Delegate;
	Delegate.BindUFunction(this, "OnBtnCloseReleased");
	ButtonClose = Cast<UButton>(GetWidgetFromName(FName(TEXT("Button_Close"))));
	ButtonClose->OnReleased.Add(Delegate);
}

void UNotificationWidget::OnBtnCloseReleased()
{
	UE_LOG(LogTemp, Log, TEXT("OnBtnCloseReleased"));
	UWidgetAnimation* Animation = this->GetNameWidgetAnimation("FadeIn");
	if (Animation)
	{
		float EndTime = Animation->GetEndTime();
		PlayAnimation(Animation,0,1,EUMGSequencePlayMode::Reverse,1.5);
		FTimerHandle UnusedHandle;
		GetWorld()->GetTimerManager().SetTimer(UnusedHandle, FTimerDelegate::CreateLambda([this]
		{
			this->SetVisibility(ESlateVisibility::Collapsed);
		}), EndTime, false);
	}
}


void UNotificationWidget::PlayWidgetAnimation(const FString& InWidgetAnimName)
{
	if (UWidgetAnimation* MyTempAnimation = GetNameWidgetAnimation(InWidgetAnimName))
	{
		//播放此WidgetAnim
		PlayAnimation(MyTempAnimation, 0, 1, EUMGSequencePlayMode::Forward, 1.5);
	}
}


UWidgetAnimation* UNotificationWidget::GetNameWidgetAnimation(const FString& InWidgetAnimName) const
{
	//获取Widget蓝图生成类
	if (UWidgetBlueprintGeneratedClass* WidgetBlueprintGenerated = Cast<UWidgetBlueprintGeneratedClass>(GetClass()))
	{
		//获取类中的WidgetAnim
		TArray<UWidgetAnimation*> TArrayAnimations = WidgetBlueprintGenerated->Animations;

		//通过传入的动画名，找到对应的WidgetAnim
		UWidgetAnimation** MyTempAnimation = TArrayAnimations.FindByPredicate(
			[&](const UWidgetAnimation* OurAnimation)
			{
				return OurAnimation->GetFName().ToString() == (InWidgetAnimName + FString("_INST"));
			});

		return *MyTempAnimation;
	}

	return NULL;
}
