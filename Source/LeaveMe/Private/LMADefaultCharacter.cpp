// Fill out your copyright notice in the Description page of Project Settings.


#include "LMADefaultCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ALMADefaultCharacter::ALMADefaultCharacter()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm"); //создаем компопнет через систему UE с автосборкой мусора
	SpringArmComponent->SetupAttachment(GetRootComponent()); //устанавливаем рута
	//дублируемв C++ из блюпринта настройки, для будущего управления через C++
	//Они будут заданы как дефолтные для блюпринта их можно поменять и вернутся к ним потом
	SpringArmComponent->SetUsingAbsoluteRotation(true);
	SpringArmComponent->TargetArmLength = ArmLength; //длина штатива
	SpringArmComponent->SetRelativeRotation(FRotator(YRotation, 0.0f, 0.0f)); //pitch/yaw/roll
	SpringArmComponent->bDoCollisionTest = false; //чтобы камера не приближалась при ударе об стену
	SpringArmComponent->bEnableCameraLag = true; //плавное движение камеры за персонажем, без дерганий и эпилепсии

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent"); //создаем компопнет через систему UE с автосборкой мусора
	CameraComponent->SetupAttachment(SpringArmComponent); //устанавливаем рута
	CameraComponent->SetFieldOfView(FOV);
	CameraComponent->bUsePawnControlRotation = false; //запрещаем камере вращаться относительно SpringArmComponent.
	
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALMADefaultCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALMADefaultCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ALMADefaultCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

