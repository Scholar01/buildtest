// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplorerPawn.h"

// Sets default values
AExplorerPawn::AExplorerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AExplorerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AExplorerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AExplorerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

