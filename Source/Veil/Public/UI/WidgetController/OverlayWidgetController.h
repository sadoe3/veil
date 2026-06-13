#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/VeilWidgetController.h"
#include "GameplayEffectTypes.h"
#include "OverlayWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float, NewValue);

UCLASS(BlueprintType, Blueprintable)
class VEIL_API UOverlayWidgetController : public UVeilWidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnHealthChanged;
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnMaxHealthChanged;
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnManaChanged;
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnMaxManaChanged;

protected:
	void UpdateHealth(const FOnAttributeChangeData& Data) const;
	void UpdateMaxHealth(const FOnAttributeChangeData& Data) const;
	void UpdateMana(const FOnAttributeChangeData& Data) const;
	void UpdateMaxMana(const FOnAttributeChangeData& Data) const;
};