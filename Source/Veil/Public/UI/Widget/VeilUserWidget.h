#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VeilUserWidget.generated.h"

UCLASS()
class VEIL_API UVeilUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void InitWidgetController();
};