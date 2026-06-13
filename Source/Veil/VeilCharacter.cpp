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

void AVeilCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// 멀티플레이 환경이면 InitAbilityActorInfo 이후나 PossessedBy에서 처리하는 것이 정석이나, 지금은 빠른 프로토타이핑을 위해 BeginPlay에서 바로 연동하기
	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (AVeilHUD* VeilHUD = Cast<AVeilHUD>(PlayerController->GetHUD()))
		{
			// 현재 PlayerState를 구현하지 않았으므로 PS 자리에는 nullptr를 넣고 진행
			VeilHUD->InitOverlay(PlayerController, nullptr, AbilitySystemComponent, AttributeSet);
		}
	}
}

void AVeilCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}
