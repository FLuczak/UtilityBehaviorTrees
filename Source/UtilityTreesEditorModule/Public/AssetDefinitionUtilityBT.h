// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetDefinition_BehaviorTree.h"
#include "AssetDefinitionUtilityBT.generated.h"


UCLASS()
class UTILITYTREESEDITOR_API UAssetDefinitionUtilityBT : public UAssetDefinition_BehaviorTree
{
	GENERATED_BODY()
protected:
	// UAssetDefinition Begin
	virtual FText GetAssetDisplayName() const override;
	virtual FLinearColor GetAssetColor() const override;
	void OpenInDefaults(class UBehaviorTree* OldBehaviorTree, class UBehaviorTree* NewBehaviorTree) const;
	virtual TSoftClassPtr<UObject> GetAssetClass() const override;
	virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;
	virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;
	virtual EAssetCommandResult PerformAssetDiff(const FAssetDiffArgs& DiffArgs) const override;
};
