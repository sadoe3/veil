#include "VeilPlayerController.h"
#include "EnhancedInputSubsystems.h"

AVeilPlayerController::AVeilPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	bReplicates = true;
}

void AVeilPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	check(VeilContext);

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(VeilContext, 0);
	}
}