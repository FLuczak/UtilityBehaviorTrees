// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UtilityConsideration.generated.h"

/**
 * 
 */
UCLASS(Blueprintable,BlueprintType)
class UTILITYTREES_API UUtilityConsideration : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent)
	float Evaluate(APawn* OwnedPawn, AController* Controller);
};
