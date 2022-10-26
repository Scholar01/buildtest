// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplorerGameMode.h"

#include "ExplorerPlayerController.h"
#include "Blueprint/UserWidget.h"

AExplorerGameMode::AExplorerGameMode()
{
	this->HUDClass = NULL;
	// 设置玩家控制器
	this->PlayerControllerClass = AExplorerPlayerController::StaticClass();
}
