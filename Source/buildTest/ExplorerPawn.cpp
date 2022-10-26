// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplorerPawn.h"

#include "macros.h"
#include "Components/WidgetInteractionComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

class UWidgetInteractionComponent;
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
	WidgetInteractionComponent = Cast<UWidgetInteractionComponent>(
		this->GetComponentByClass(UWidgetInteractionComponent::StaticClass()));

	SpringArmComponent = Cast<USpringArmComponent>(GetComponentByClass(USpringArmComponent::StaticClass()));
	TargetArmLengthNew = SpringArmComponent->TargetArmLength;
}

// Called every frame
void AExplorerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//设置armlength
	if (!UKismetMathLibrary::NearlyEqual_FloatFloat(SpringArmComponent->TargetArmLength, TargetArmLengthNew, 10.0f))
	{
		float Length = UKismetMathLibrary::FInterpTo(
			SpringArmComponent->TargetArmLength,
			TargetArmLengthNew,
			UGameplayStatics::GetWorldDeltaSeconds(GetWorld()),
			UKismetMathLibrary::Lerp(3, 1, GetSpringArmLengthNormalized()));

		SpringArmComponent->TargetArmLength = Length;
	}
}


// Called to bind functionality to input
void AExplorerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//绑定鼠标左键事件
	UPlayerInput::AddEngineDefinedActionMapping(
		FInputActionKeyMapping("LeftButtonDown", EKeys::LeftMouseButton, false));
	PlayerInputComponent->BindAction(FName("LeftButtonDown"), IE_Pressed, this,
	                                 &AExplorerPawn::OnPressedLeftMouseButton);
	PlayerInputComponent->BindAction(FName("LeftButtonDown"), IE_Released, this,
	                                 &AExplorerPawn::OnReleasedLeftMouseButton);


	//鼠标X轴移动
	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("TurnRate", EKeys::MouseX));
	//鼠标Y轴移动
	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("LookUpRate", EKeys::MouseY));
	InputComponent->BindAxis(FName("TurnRate"), this, &AExplorerPawn::TurnRate);
	InputComponent->BindAxis(FName("LookUpRate"), this, &AExplorerPawn::LookUpRate);


	//鼠标右键平移事件
	UPlayerInput::AddEngineDefinedActionMapping(
		FInputActionKeyMapping("RightButtonDown", EKeys::RightMouseButton, false));

	PlayerInputComponent->BindAction(FName("RightButtonDown"), IE_Pressed, this,
	                                 &AExplorerPawn::OnPressedRightMouseButton);
	PlayerInputComponent->BindAction(FName("RightButtonDown"), IE_Released, this,
	                                 &AExplorerPawn::OnReleasedRightMouseButton);

	//键盘前后左右事件
	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MoveForward", EKeys::W, 1.f));
	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MoveForward", EKeys::S, -1.f));
	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MoveRight", EKeys::A, -1.f));
	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MoveRight", EKeys::D, 1.f));

	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &AExplorerPawn::MoveForward);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &AExplorerPawn::MoveRight);

	//鼠标滚轮缩放事件
	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MouseWheel", EKeys::MouseWheelAxis, 1.f));
	InputComponent->BindAxis(FName("MouseWheel"), this, &AExplorerPawn::MouseWheel);
}

void AExplorerPawn::OnPressedLeftMouseButton()
{
	if (WidgetInteractionComponent)
	{
		WidgetInteractionComponent->PressPointerKey(EKeys::LeftMouseButton);
	}

	FLatentActionInfo LatentActionInfo;
	UKismetSystemLibrary::RetriggerableDelay(GetWorld(), 0.2f, LatentActionInfo);
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController->IsInputKeyDown(EKeys::LeftMouseButton))
	{
		this->b_Mouse_Hold_01 = true;
	}
}

void AExplorerPawn::OnReleasedLeftMouseButton()
{
	if (WidgetInteractionComponent)
	{
		WidgetInteractionComponent->PressPointerKey(EKeys::LeftMouseButton);
	}

	if (this->b_Mouse_Hold_01)
	{
		//为了有甩动的效果，松开鼠标后，延时2秒再处理
		FLatentActionInfo LatentActionInfo;
		UKismetSystemLibrary::RetriggerableDelay(GetWorld(), 0.2f, LatentActionInfo);
	}

	this->b_Mouse_Hold_01 = false;
}

void AExplorerPawn::OnPressedRightMouseButton()
{
	this->b_Mouse_Hold_02 = true;
}

void AExplorerPawn::OnReleasedRightMouseButton()
{
	this->b_Mouse_Hold_02 = false;
}

void AExplorerPawn::MouseWheel(float AxisValue)
{
	if (this->Zoom_Intensity_Curve && AxisValue != 0)
	{
		float FloatValue = this->Zoom_Intensity_Curve->GetFloatValue(this->GetSpringArmLengthNormalized());
		//曲线*缩放速度
		FloatValue *= Zoom_Speed_Mouse;
		float Length = AxisValue > 0 ? FloatValue : -FloatValue;
		Length = this->SpringArmComponent->TargetArmLength + Length;
		Length = UKismetMathLibrary::Clamp(Length, SpringArm_Length_Min, SpringArm_Length_Max);
		this->TargetArmLengthNew = Length;
		// this->SpringArmComponent->TargetArmLength = Length;
	}
}

void AExplorerPawn::LookUpRate(float AxisValue)
{
	if (this->b_Mouse_Hold_01)
	{
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		auto ControlRotation = PlayerController->GetControlRotation();
		float y = this->bInvertPitch ? -Rotation_Speed_Mouse : Rotation_Speed_Mouse;
		y *= AxisValue;
		y += ControlRotation.Pitch;
		y = UKismetMathLibrary::ClampAngle(y, Pitch_Limit_Min, Pitch_Limit_Max);

		PlayerController->SetControlRotation(FRotator(y, ControlRotation.Yaw, 0.0));
	}
	if (this->b_Mouse_Hold_02)
	{
		this->MoveForward(-AxisValue);
	}
}

void AExplorerPawn::TurnRate(float AxisValue)
{
	if (this->b_Mouse_Hold_01)
	{
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		auto ControlRotation = PlayerController->GetControlRotation();
		float z = this->bInvertYaw ? -Rotation_Speed_Mouse : Rotation_Speed_Mouse;
		z *= AxisValue;
		z += ControlRotation.Yaw;


		PlayerController->SetControlRotation(FRotator(ControlRotation.Pitch, z, 0.0));
	}
	if (this->b_Mouse_Hold_02)
	{
		this->MoveRight(-AxisValue);
	}
}

void AExplorerPawn::MoveForward(float AxisValue)
{
	if (this->Pan_Intensity_Curve)
	{
		float Normalized = this->GetSpringArmLengthNormalized();
		float Curve = this->Pan_Intensity_Curve->GetFloatValue(Normalized) * this->Pan_Intensity_Mouse;
		float Z = AxisValue * Curve;
		auto Rotation = this->GetControlRotation();
		FRotator R_T = FRotator(0, Rotation.Yaw, 0);
		FVector Direction = UKismetMathLibrary::GetForwardVector(R_T);
		this->AddMovementInput(Direction, Z);
	}
}

void AExplorerPawn::MoveRight(float AxisValue)
{
	if (this->Pan_Intensity_Curve)
	{
		float Normalized = this->GetSpringArmLengthNormalized();
		float Curve = this->Pan_Intensity_Curve->GetFloatValue(Normalized) * this->Pan_Intensity_Mouse;
		float Z = AxisValue * Curve;
		auto Rotation = this->GetControlRotation();
		FRotator R_T = FRotator(0, Rotation.Yaw, 0);
		FVector Direction = UKismetMathLibrary::GetRightVector(R_T);
		this->AddMovementInput(Direction, Z);
	}
}

float AExplorerPawn::GetSpringArmLengthNormalized()
{
	if (!SpringArmComponent)
	{
		return 0;
	}

	return UKismetMathLibrary::NormalizeToRange(SpringArmComponent->TargetArmLength, SpringArm_Length_Min,
	                                            SpringArm_Length_Max);
}
