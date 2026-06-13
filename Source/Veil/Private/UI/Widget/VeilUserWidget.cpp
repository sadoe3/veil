#include "UI/Widget/VeilUserWidget.h"
void UVeilUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	InitWidgetController();
}