#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/VeilAttributeSet.h"
#include "AbilitySystemComponent.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	UVeilAttributeSet* VeilAttributeSet = CastChecked<UVeilAttributeSet>(AttributeSet);
	OnHealthChanged.Broadcast(VeilAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(VeilAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(VeilAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(VeilAttributeSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	UVeilAttributeSet* VeilAttributeSet = CastChecked<UVeilAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(VeilAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::UpdateHealth);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(VeilAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::UpdateMaxHealth);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(VeilAttributeSet->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::UpdateMana);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(VeilAttributeSet->GetMaxManaAttribute()).AddUObject(this, &UOverlayWidgetController::UpdateMaxMana);
}

void UOverlayWidgetController::UpdateHealth(const FOnAttributeChangeData& Data) const { OnHealthChanged.Broadcast(Data.NewValue); }
void UOverlayWidgetController::UpdateMaxHealth(const FOnAttributeChangeData& Data) const { OnMaxHealthChanged.Broadcast(Data.NewValue); }
void UOverlayWidgetController::UpdateMana(const FOnAttributeChangeData& Data) const { OnManaChanged.Broadcast(Data.NewValue); }
void UOverlayWidgetController::UpdateMaxMana(const FOnAttributeChangeData& Data) const { OnMaxManaChanged.Broadcast(Data.NewValue); }