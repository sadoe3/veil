#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "VeilPlayerController.generated.h"

class UInputMappingContext;

UCLASS()
class AVeilPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AVeilPlayerController();

protected:
	virtual void BeginPlay() override;

private:
	// custom context
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> VeilContext;
};