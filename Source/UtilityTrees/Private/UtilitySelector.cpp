// Fill out your copyright notice in the Description page of Project Settings.


#include "UtilitySelector.h"

#include "AIController.h"
#include "UtilityDecorator.h"

UUtilitySelector::UUtilitySelector()
{
	NodeName = "Utility Selector";
}

void UUtilitySelector::InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	EBTMemoryInit::Type InitType) const
{
	Super::InitializeMemory(OwnerComp, NodeMemory, InitType);
}

void UUtilitySelector::CleanupMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	EBTMemoryClear::Type CleanupType) const
{
	Super::CleanupMemory(OwnerComp, NodeMemory, CleanupType);
}

int32 UUtilitySelector::GetNextChildHandler(FBehaviorTreeSearchData& SearchData, int32 PrevChild,
	EBTNodeResult::Type LastResult) const
{
	UBehaviorTreeComponent& OwnerComp = SearchData.OwnerComp;
	TArray<float> Utilities = TArray<float>();
	Utilities.SetNum(Children.Num());

	for (int32 ChildIdx = 0; ChildIdx < Children.Num(); ++ChildIdx)
	{
		const FBTCompositeChild& Child = Children[ChildIdx];
		float TotalUtility = 0.f;
		int UtilityDecoratorsCount = 0;

		for (UBTDecorator* Decorator : Child.Decorators)
		{
			if (UUtilityDecorator* UtilityDecorator = Cast<UUtilityDecorator>(Decorator))
			{
				AAIController* Controller = OwnerComp.GetAIOwner();
				const float Utility = UtilityDecorator->CalculateUtility(&OwnerComp,Controller->GetPawn(),Controller);
				TotalUtility += Utility;
				UtilityDecoratorsCount++;
			}
		}

		Utilities[ChildIdx] = TotalUtility / static_cast<float>(UtilityDecoratorsCount);
	}

	constexpr float Max = -MAX_int32;
	int MaxIndex = INDEX_NONE;
	int TempIndex = 0;

	for (const auto Utility : Utilities)
	{
		if(Max < Utility)
		{
			MaxIndex = TempIndex;
		}

		TempIndex++;
	}

	if (MaxIndex != INDEX_NONE)
	{
		return MaxIndex;
	}

	return Super::GetNextChildHandler(SearchData, PrevChild, LastResult);
}
