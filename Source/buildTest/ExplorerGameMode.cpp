// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplorerGameMode.h"

#include "ExplorerPawn.h"
#include "ExplorerPlayerController.h"
#include "Blueprint/UserWidget.h"

AExplorerGameMode::AExplorerGameMode()
{
	this->HUDClass = NULL;
	// 设置玩家控制器
	this->PlayerControllerClass = AExplorerPlayerController::StaticClass();

	this->DefaultPawnClass = AExplorerPawn::StaticClass();

	UBlueprintGeneratedClass* BP = Cast<UBlueprintGeneratedClass>(AExplorerPawn::StaticClass());
	if (BP)
	{
		UE_LOG(LogTemp,Log,TEXT("bp:%s"),*BP->GetName());
	}
}
