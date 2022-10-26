// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NotificationWidget.generated.h"

class UButton;
/**
 * 界面加载后，用于显示弹出的欢迎框
 */
UCLASS()
class BUILDTEST_API UNotificationWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	/**
	 * @brief 打开窗口的函数
	 */
	UFUNCTION()
	void OpenNotification();

protected:
	virtual void NativeConstruct() override;
	/**
	 * @brief 根据名称播放动画
	 * @param InWidgetAnimName 
	 */
	UFUNCTION()
	void PlayWidgetAnimation(const FString& InWidgetAnimName);


private:
	UPROPERTY()
	UButton* ButtonClose;

	UFUNCTION()
	void OnBtnCloseReleased();

	/**
	 * @brief 根据名称获取动画
	 * @param InWidgetAnimName 
	 * @return 
	 */
	UFUNCTION()
	UWidgetAnimation* GetNameWidgetAnimation(const FString& InWidgetAnimName) const;
};
