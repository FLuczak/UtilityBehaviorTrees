// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "UtilityBehaviorTree.h"
#include "UtilityTreesController.generated.h"

/**
 * 
 */
UCLASS(Blueprintable,BlueprintType)
class UTILITYTREES_API AUtilityTreesController : public AAIController
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	TArray<TObjectPtr<UUtilityBehaviorTree>> Trees;

	UPROPERTY(EditAnywhere)
	float UtilityCheckInterval = 0.1f;

	float UtilityTimer = 0.0f;
	int CurrentTreeIndex = -1;

	void FindNewTree();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
};
