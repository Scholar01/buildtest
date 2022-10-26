// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CineCameraComponent.h"
#include "CineCameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/MovementComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "ExplorerPawn.generated.h"

class UWidgetInteractionComponent;
UCLASS()
class BUILDTEST_API AExplorerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AExplorerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/**
	 * @brief 设置拖动视角的旋转速度
	 */
	UPROPERTY(EditAnywhere, DisplayName = "旋转速度", Category = "鼠标设置")
	float Rotation_Speed_Mouse = 2;

	UPROPERTY(EditAnywhere, DisplayName="平移强度", Category="鼠标设置")
	float Pan_Intensity_Mouse = 0.1f;

	/**
	 * @brief 设置按住鼠标左键左右拖动窗口的方式
	 */
	UPROPERTY(EditAnywhere, DisplayName = "翻转z轴", Category = "旋转设置")
	bool bInvertYaw = false;
	/**
	 * @brief 设置按住鼠标左键上下拖动窗口的方式
	 */
	UPROPERTY(EditAnywhere, DisplayName = "翻转y轴", Category = "旋转设置")
	bool bInvertPitch = false;

	/**
	 * @brief 用于控制上线拖动的最小值，避免360度旋转
	 */
	UPROPERTY(EditAnywhere, DisplayName = "Y轴最小值", Category = "旋转设置")
	float Pitch_Limit_Min = -89.0;

	/**
	 * @brief 用于控制上线拖动的最大值，避免360度旋转
	 */
	UPROPERTY(EditAnywhere, DisplayName = "Y轴最大值", Category = "旋转设置")
	float Pitch_Limit_Max = 5.0f;

	/**
	 * @brief 设置平移的曲线
	 */
	UPROPERTY(EditAnywhere, DisplayName="平移强度曲线", Category="平移设置")
	UCurveFloat* Pan_Intensity_Curve;

	/**
	 * @brief 设置缩放的曲线
	 */
	UPROPERTY(EditAnywhere, DisplayName="缩放强度曲线", Category="缩放设置")
	UCurveFloat* Zoom_Intensity_Curve;

	/**
	 * @brief 缩放速度
	 */
	UPROPERTY(EditAnywhere, DisplayName = "缩放速度", Category = "鼠标设置")
	float Zoom_Speed_Mouse = 30000;
	
	/**
	 * @brief 用于缩放的最小值
	 */
	UPROPERTY(EditAnywhere, DisplayName = "缩放最小值", Category = "缩放设置")
	float SpringArm_Length_Min = 1000.0f;

	/**
	 * @brief 用于控制缩放最大值
	 */
	UPROPERTY(EditAnywhere, DisplayName = "缩放最大值", Category = "缩放设置")
	float SpringArm_Length_Max = 200000.0f;


public:
	/**
	 * @brief 鼠标左键被按下
	 */
	UFUNCTION(BlueprintCallable, Category = "MouseEvents")
	void OnPressedLeftMouseButton();

	/**
	 * @brief 鼠标左键被放开
	 */
	UFUNCTION(BlueprintCallable, Category = "MouseEvents")
	void OnReleasedLeftMouseButton();

	/**
	 * @brief 鼠标右键被按下
	 */
	UFUNCTION(BlueprintCallable, Category = "MouseEvents")
	void OnPressedRightMouseButton();

	/**
	 * @brief 鼠标右键被放开
	 */
	UFUNCTION(BlueprintCallable, Category = "MouseEvents")
	void OnReleasedRightMouseButton();
	/**
	 * @brief 鼠标滚轮事件
	 */
	UFUNCTION(BlueprintCallable, Category = "MouseEvents")
	void MouseWheel(float AxisValue);


	/**
	 * @brief 鼠标y轴移动事件
	 */
	UFUNCTION(BlueprintCallable, Category = "MouseEvents")
	void LookUpRate(float AxisValue);

	/**
	 * @brief 鼠标x轴移动事件
	 */
	UFUNCTION(BlueprintCallable, Category = "MouseEvents")
	void TurnRate(float AxisValue);


	/**
	 * @brief 键盘前后移动事件
	 */
	UFUNCTION(BlueprintCallable, Category = "KeyBoardEvents")
	void MoveForward(float AxisValue);

	/**
	 * @brief 键盘左右移动事件
	 */
	UFUNCTION(BlueprintCallable, Category = "KeyBoardEvents")
	void MoveRight(float AxisValue);


	/**
	 * @brief 获取机械臂的向量
	 * @return 
	 */
	UFUNCTION(BlueprintCallable)
	float GetSpringArmLengthNormalized();


private:
	UPROPERTY()
	UWidgetInteractionComponent* WidgetInteractionComponent;

	UPROPERTY()
	USpringArmComponent* SpringArmComponent;

	/**
	 * @brief 鼠标左键是否按下
	 */
	UPROPERTY()
	bool b_Mouse_Hold_01 = false;

	/**
	 * @brief 鼠标右键被按下
	 */
	UPROPERTY()
	bool b_Mouse_Hold_02 = false;

	UPROPERTY()
	float TargetArmLengthNew = 1000;
};


