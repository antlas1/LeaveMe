// Fill out your copyright notice in the Description page of Project Settings.


#include "LMADefaultCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/LMAHealthComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/Engine.h"

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
	
	//запретим нашему персонажу поворачиваться в сторону камеры. 
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	HealthComponent = CreateDefaultSubobject<ULMAHealthComponent>("HealthComponent");
}

// Called when the game starts or when spawned
void ALMADefaultCharacter::BeginPlay()
{
	Super::BeginPlay();
	//Мы проверяем задан ли материал для нашего курсора и если он задан
	if (CursorMaterial)
	{
		CurrentCursor = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), CursorMaterial, CursorSize, FVector(0));
	}
	OnHealthChanged(HealthComponent->GetHealth());
	HealthComponent->OnDeath.AddUObject(this, &ALMADefaultCharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &ALMADefaultCharacter::OnHealthChanged);
}

// Called every frame
void ALMADefaultCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!(HealthComponent->IsDead()))
	{
		RotationPlayerOnCursor();
	}
}

// Called to bind functionality to input
void ALMADefaultCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Привязка для управления осей
	PlayerInputComponent->BindAxis("MoveForward", this, &ALMADefaultCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ALMADefaultCharacter::MoveRight);
	PlayerInputComponent->BindAxis("ZoomCamera", this, &ALMADefaultCharacter::ZoomCamera);
}

void ALMADefaultCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void ALMADefaultCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
} 


void ALMADefaultCharacter::ZoomCamera(float Value)
{
   ArmLength = FMath::Clamp(ArmLength + Value * 100.0f, MinArmLength, MaxArmLength);
   SpringArmComponent->TargetArmLength = ArmLength;
}

void ALMADefaultCharacter::OnDeath()
{
	CurrentCursor->DestroyRenderState_Concurrent();

	PlayAnimMontage(DeathMontage);

	GetCharacterMovement()->DisableMovement();

	SetLifeSpan(5.0f);

	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
}

void ALMADefaultCharacter::OnHealthChanged(float NewHealth)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Health = %f"), NewHealth));
}

void ALMADefaultCharacter::RotationPlayerOnCursor()
{
	//получаем локальный указатель на контроллер нашего персонажа
APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC)
	{
		//FHitResult - хранящая поля с информацией о столкновении с различными объектами, дастанцию, место начала/конца трейса
		FHitResult ResultHit;
		/*
		Функция GetHitResultUnderCursor принимает несколько аргументов, первый – это канал
		трассировки, ECC_GameTraceChannel1, это тот канал который мы с вами задали в Project Settings >
		Engine > Collision. Чтобы проверить номер созданного канала, перейдите в директорию Config >
		DefaultEngine.ini. Где в категории CollisionProfile у вас должна быть следующая запись	+DefaultChannelResponses=(Channel=ECC_GameTraceChannel1,DefaultResponse=ECR_Block,bTraceTyp
e=True,bStaticObject=False,Name="Land")
		*/
		PC->GetHitResultUnderCursor(ECC_GameTraceChannel1, true, ResultHit);
		//передаем результат соотношения местоположения игрока и точки с которой у нас столкнулся курсор. 
		float FindRotatorResultYaw = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), ResultHit.Location).Yaw;
		//поворачиваем персонажа на наш курсор с помощью функции SetActorRotation
		SetActorRotation(FQuat(FRotator(0.0f, FindRotatorResultYaw, 0.0f)));
		//Последнее что нам осталось, это присоединить визуальную часть нашего курсора, относительно текущего положения.
		if (CurrentCursor)
		{
			CurrentCursor->SetWorldLocation(ResultHit.Location);
		}
	}
}
