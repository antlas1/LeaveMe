// Fill out your copyright notice in the Description page of Project Settings.


#include "LMADefaultCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ALMADefaultCharacter::ALMADefaultCharacter()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm"); //создаем компопнет через систему UE с автосборкой мусора
	SpringArmComponent->SetupAttachment(GetRootComponent()); //устанавливаем рута
	

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent"); //создаем компопнет через систему UE с автосборкой мусора
	CameraComponent->SetupAttachment(SpringArmComponent); //устанавливаем рута
	
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

