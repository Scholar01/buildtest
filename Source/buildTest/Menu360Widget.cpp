// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu360Widget.h"

void UMenu360Widget::NativeConstruct()
{
	Super::NativeConstruct();

	FScriptDelegate Delegate;
	Delegate.BindUFunction(this, "OnBtnCloseClick");
	ButtonClose = Cast<UButton>(GetWidgetFromName(FName(TEXT("Button_Close"))));
	ButtonClose->OnClicked.Add(Delegate);
}

void UMenu360Widget::OnBtnCloseClick()
{
	UE_LOG(LogTemp, Log, TEXT("on btn close click"));
}
