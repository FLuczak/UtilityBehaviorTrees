// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "UtilityConsideration.h"
#include "UtilityBehaviorTree.generated.h"

/**
 * 
 */
UCLASS()
class UTILITYTREES_API UUtilityBehaviorTree : public UBehaviorTree
{
	GENERATED_BODY()
public:
	UUtilityBehaviorTree();
	float EvaluateUtility(APawn* OwnedPawn, AController* Controller);
private:
	TArray<TObjectPtr<UUtilityConsideration>> ConsiderationInstances{};
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UUtilityConsideration>> UtilityConsiderations{};
	void InitializeConsiderationInstances();
};
