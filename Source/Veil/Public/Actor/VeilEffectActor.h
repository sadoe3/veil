#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VeilEffectActor.generated.h"

class UGameplayEffect;

UCLASS()
class VEIL_API AVeilEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AVeilEffectActor();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;
};