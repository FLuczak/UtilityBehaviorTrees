// Fill out your copyright notice in the Description page of Project Settings.


#include "UtilityBehaviorTree.h"

UUtilityBehaviorTree::UUtilityBehaviorTree()
{
	InitializeConsiderationInstances();
}

float UUtilityBehaviorTree::EvaluateUtility(APawn* OwnedPawn, AController* Controller)
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

	return TotalUtility / ConsiderationInstances.Num();
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
