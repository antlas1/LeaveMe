// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LMADefaultCharacter.generated.h"

//Потом сделаем инклуд
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class LEAVEME_API ALMADefaultCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALMADefaultCharacter();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent; //рычаг камеры

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent; //камера (FOV)
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY()
	UDecalComponent* CurrentCursor = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
	UMaterialInterface* CursorMaterial = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
	FVector CursorSize = FVector(20.0f, 40.0f, 40.0f);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
private:
    float YRotation = -75.0f;
	float ArmLength = 1400.0f;
	//Минимальное и максимальное значение дины рычага
	float MinArmLength = 300.0f;
	float MaxArmLength = 2000.0f;
	float FOV = 55.0f;
	
	void MoveForward(float Value);
	void MoveRight(float Value);
	//отработка колеса для камеры
	void ZoomCamera(float Value);
};
