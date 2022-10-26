// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NotificationWidget.h"
#include "Blueprint/UserWidget.h"
#include "MasterMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class BUILDTEST_API UMasterMenuWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;

private:
	/**
	 * @brief 弹出的小窗口控件
	 */
	UPROPERTY()
	UNotificationWidget* NotificationWidget;
};
