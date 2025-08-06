// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "UtilityDecorator.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class UTILITYTREES_API UUtilityDecorator : public UBTDecorator
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent)
	float CalculateUtility(UBehaviorTreeComponent* OwnerComp,APawn* OwnedPawn,AController* Controller);
};
