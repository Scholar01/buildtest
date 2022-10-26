// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Menu360Widget.h"
#include "GameFramework/PlayerController.h"
#include "ExplorerPlayerController.generated.h"

/**
 * 玩家控制器
 * 在内部创建widget，角色逻辑等
 */
UCLASS()
class BUILDTEST_API AExplorerPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	//UMG蓝图的实例对象，用于显示在游戏的Viewport中
	UPROPERTY()
	UUserWidget* Menu360WidgetInstance;

	UPROPERTY()
	UUserWidget* MasterMenuWidgetInstance;
protected:
	virtual void BeginPlay() override;

private:
	void CreateMenu360Widget();
	void CreateMasterMenuWidget();
};
