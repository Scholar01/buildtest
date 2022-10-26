// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplorerPlayerController.h"

void AExplorerPlayerController::BeginPlay()
{
	this->CreateMasterMenuWidget();
	this->CreateMenu360Widget();
}

void AExplorerPlayerController::CreateMenu360Widget()
{
	if (this->Menu360WidgetInstance)
	{
		Menu360WidgetInstance->RemoveFromViewport();
		Menu360WidgetInstance = nullptr;
	}
	// 加载自定义UMG的class，通过这个class创建Widget对象，并显示在界面中。
	 if (UClass* MyWidgetClass = LoadClass<UUserWidget>(
	 	NULL, TEXT("WidgetBlueprint'/Game/_Build/Blueprints/Widgets/BP_360Menu_Widget.BP_360Menu_Widget_C'")))
	 {
	 	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	 	{
	 		Menu360WidgetInstance = CreateWidget<UUserWidget>(PC, MyWidgetClass);
	 		if (Menu360WidgetInstance)
	 		{
	 			Menu360WidgetInstance->AddToViewport();
	 			Menu360WidgetInstance->SetVisibility(ESlateVisibility::Collapsed);
	 		}
	 	}
	 }
}

void AExplorerPlayerController::CreateMasterMenuWidget()
{
	if (this->MasterMenuWidgetInstance)
	{
		MasterMenuWidgetInstance->RemoveFromViewport();
		MasterMenuWidgetInstance = nullptr;
	}
	// 加载自定义UMG的class，通过这个class创建Widget对象，并显示在界面中。
	if (UClass* MyWidgetClass = LoadClass<UUserWidget>(
		NULL, TEXT("WidgetBlueprint'/Game/_Build/Blueprints/Widgets/BP_Master_Menu_Widget.BP_Master_Menu_Widget_C'")))
	{
		if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
		{
			MasterMenuWidgetInstance = CreateWidget<UUserWidget>(PC, MyWidgetClass);
			if (MasterMenuWidgetInstance)
			{
				MasterMenuWidgetInstance->AddToViewport();
			}
		}
	}
}
