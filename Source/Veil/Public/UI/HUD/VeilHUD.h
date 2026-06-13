#pragma once
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "VeilHUD.generated.h"

class UVeilUserWidget;
class UOverlayWidgetController;
struct FWidgetControllerParams;
class UAbilitySystemComponent;
class UAttributeSet;

UCLASS()
class VEIL_API AVeilHUD : public AHUD
{
	GENERATED_BODY()
public:
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& Params);
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

private:
	UPROPERTY()
	TObjectPtr<UVeilUserWidget> OverlayWidget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UVeilUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
};