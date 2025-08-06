// Fill out your copyright notice in the Description page of Project Settings.


#include "UtilityTreesController.h"

#include "UtilityBehaviorTree.h"


void AUtilityTreesController::Tick(float DeltaSeconds)
{
	UtilityTimer -= DeltaSeconds;

	if(UtilityTimer <= 0.0f)
	{
		FindNewTree();
		UtilityTimer = UtilityCheckInterval;
	}

	Super::Tick(DeltaSeconds);
}


void AUtilityTreesController::FindNewTree()
{
	TArray<float> Utilities{};
	Utilities.SetNum(Trees.Num());
	auto TempIndex = 0;

	for (const auto Tree : Trees)
	{
		Utilities[TempIndex] = Tree->EvaluateUtility(GetPawn(),this);
		TempIndex++;
	}

	auto MaxUtility = -MAX_FLT;
	auto MaxUtilityIndex = -1;

	for(int i = 0; i < Utilities.Num();i++)
	{
		if(MaxUtility <= Utilities[i] && CurrentTreeIndex != i)
		{
			MaxUtility = Utilities[i];
			MaxUtilityIndex = i;
		}
	}

	if(MaxUtilityIndex != -1)
	{
		RunBehaviorTree(Trees[MaxUtilityIndex]);
		CurrentTreeIndex = MaxUtilityIndex;
	}
}

void AUtilityTreesController::BeginPlay()
{
	Super::BeginPlay();
}
