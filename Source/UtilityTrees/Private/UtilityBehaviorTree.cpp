// Fill out your copyright notice in the Description page of Project Settings.


#include "UtilityBehaviorTree.h"

UUtilityBehaviorTree::UUtilityBehaviorTree()
{

}

float UUtilityBehaviorTree::EvaluateUtility(APawn* OwnedPawn, AController* Controller,bool IsInUse)
{
	float TotalUtility = 0.0f;

	if(UtilityConsiderations.Num() != ConsiderationInstances.Num())
	{
		InitializeConsiderationInstances();
	}

	for (const auto Consideration : ConsiderationInstances)
	{
		if (Consideration == nullptr)continue;
		if (!IsValid(Consideration))continue;
		TotalUtility += Consideration->Evaluate(OwnedPawn, Controller);
	}

	if(IsInUse && BoostUtilityWhileInUse)
	{
		if (SetFixedUtility)return FixedUtilityValue;
		if (MultiplyConsiderationUtility) return FMath::Clamp(TotalUtility / ConsiderationInstances.Num() * UtilityMultiplier, 0, 1.0f);
	}

	if(LowerUtilityAfterUse && LastTimeUsedTimer >= TimeToReachFullUtility && UtilityMultiplierCurve != nullptr)
	{
		return TotalUtility / ConsiderationInstances.Num() * UtilityMultiplierCurve->GetFloatValue(LastTimeUsedTimer / TimeToReachFullUtility);
	}

	return TotalUtility / ConsiderationInstances.Num();
}

void UUtilityBehaviorTree::TickTimers(float DeltaTime,bool CurrentlyUsed)
{
	if(!CurrentlyUsed)LastTimeUsedTimer += DeltaTime;
}

void UUtilityBehaviorTree::ResetLastUsedTimer()
{
	LastTimeUsedTimer = 0.0f;
}

void UUtilityBehaviorTree::InitializeConsiderationInstances()
{
	ConsiderationInstances.Empty();
	for (auto Consideration : UtilityConsiderations)
	{
		UUtilityConsideration* Created = NewObject<UUtilityConsideration>(this, Consideration);
		ConsiderationInstances.Add(Created);
	}
}
