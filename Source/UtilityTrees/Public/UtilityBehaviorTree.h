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
	float EvaluateUtility(APawn* OwnedPawn, AController* Controller, bool IsInUse);
	void TickTimers(float DeltaTime, bool CurrentlyUsed);
	void ResetLastUsedTimer();
	void InitializeConsiderationInstances();
private:
	TArray<TObjectPtr<UUtilityConsideration>> ConsiderationInstances{};
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UUtilityConsideration>> UtilityConsiderations{};

	UPROPERTY(EditAnywhere)
	bool BoostUtilityWhileInUse = false;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "BoostUtilityWhileInUse"))
	bool SetFixedUtility = false;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "BoostUtilityWhileInUse"))
	bool MultiplyConsiderationUtility = false;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "SetFixedUtility"))
	float FixedUtilityValue = 1.0f;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "MultiplyConsiderationUtility"))
	float UtilityMultiplier = 1.0f;

	UPROPERTY(EditAnywhere)
	bool LowerUtilityAfterUse = false;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "LowerUtilityAfterUse"))
	float TimeToReachFullUtility = 10.0f;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "LowerUtilityAfterUse"))
	UCurveFloat* UtilityMultiplierCurve{};

	float LastTimeUsedTimer = 0.0f;
};
