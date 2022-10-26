// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ExplorerPlayerController.h"
#include "GameFramework/GameModeBase.h"
#include "ExplorerGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BUILDTEST_API AExplorerGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	AExplorerGameMode();

	UPROPERTY()
	AExplorerPlayerController* ExplorerPlayerController;
	// protected:
	// 	virtual void BeginPlay() override;
	//
	// 	virtual void Tick(float DeltaSeconds) override;
};
