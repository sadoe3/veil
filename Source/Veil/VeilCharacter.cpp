// Copyright Epic Games, Inc. All Rights Reserved.

#include "VeilCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/VeilAttributeSet.h"

#include "UI/HUD/VeilHUD.h"
#include "GameFramework/PlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AVeilCharacter::AVeilCharacter()
{
	// ASC 및 AS 초기화
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AttributeSet = CreateDefaultSubobject<UVeilAttributeSet>("AttributeSet");
	
	
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AVeilCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}


void AVeilCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
    
	// 서버(혹은 싱글플레이) 환경 초기화
	InitAbilityActorInfo();
}

void AVeilCharacter::InitAbilityActorInfo()
{
	// 1. GAS Actor Info 초기화
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
    
	// 2. 컨트롤러 및 HUD 캐스팅 후 UI(Overlay) 초기화
	if (APlayerController* VeilPlayerController = Cast<APlayerController>(GetController()))
	{
		if (AVeilHUD* VeilHUD = Cast<AVeilHUD>(VeilPlayerController->GetHUD()))
		{
			VeilHUD->InitOverlay(VeilPlayerController, nullptr, AbilitySystemComponent, AttributeSet);
		}
	}
}


void AVeilCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// EnhancedInputComponent로 캐스팅하여 입력 바인딩
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// MoveAction이 트리거될 때 Move 함수 호출
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AVeilCharacter::Move);
	}
}

void AVeilCharacter::Move(const FInputActionValue& Value)
{
	// 2D 벡터(X, Y) 값을 가져옴
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// 카메라 혹은 컨트롤러가 바라보는 방향을 기준으로 전후좌우 방향 계산
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// 전진 방향(X)과 우측 방향(Y) 구하기
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// 물리 엔진에 움직임 입력 추가
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}