// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Menu360Widget.generated.h"

/**
 * 360度菜单
 */
UCLASS()
class BUILDTEST_API UMenu360Widget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;


	UFUNCTION()
	void OnBtnCloseClick();

private:
	UPROPERTY()
	UButton* ButtonClose;
};
