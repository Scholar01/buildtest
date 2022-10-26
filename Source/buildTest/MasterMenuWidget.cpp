// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterMenuWidget.h"

void UMasterMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//初始化获取component对象
	this->NotificationWidget = Cast<UNotificationWidget>(GetWidgetFromName("BP_Notification_Widget"));

	//延迟播放动画
	FTimerHandle UnusedHandle;

	GetWorld()->GetTimerManager().SetTimer(UnusedHandle, FTimerDelegate::CreateLambda([this]
	{
		this->NotificationWidget->OpenNotification();
	}), 2.5f, false);
}
