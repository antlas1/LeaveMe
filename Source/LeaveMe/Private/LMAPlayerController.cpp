// Fill out your copyright notice in the Description page of Project Settings.


#include "LMAPlayerController.h"

ALMAPlayerController::ALMAPlayerController()
{
}

void ALMAPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//мы устанавливаем игровой режим после старта игры
	//чтобы не надо было выделять карту в редакторе
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}