// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetDefinitionUtilityBT.h"

#include "BehaviorTreeEditor.h"
#include "BehaviorTreeEditorModule.h"
#include "BehaviorTree/BehaviorTree.h"
#include "UtilityBehaviorTree.h"
#include "UtilityBTDetailsCustomization.h"

FText UAssetDefinitionUtilityBT::GetAssetDisplayName() const
{
	return FText::FromString(TEXT("Utility behavior tree"));
}

FLinearColor UAssetDefinitionUtilityBT::GetAssetColor() const
{
	return Super::GetAssetColor();
}

void UAssetDefinitionUtilityBT::OpenInDefaults(UBehaviorTree* OldBehaviorTree, UBehaviorTree* NewBehaviorTree) const
{
	FAssetDiffArgs DiffArgs;
	DiffArgs.OldAsset = OldBehaviorTree;
	DiffArgs.NewAsset = NewBehaviorTree;
	Super::PerformAssetDiff(DiffArgs);
}

TConstArrayView<FAssetCategoryPath> UAssetDefinitionUtilityBT::GetAssetCategories() const
{
	return Super::GetAssetCategories();
}

EAssetCommandResult UAssetDefinitionUtilityBT::OpenAssets(const FAssetOpenArgs& OpenArgs) const
{
	const EToolkitMode::Type Mode = OpenArgs.GetToolkitMode();
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	for (UBehaviorTree* BehaviorTree : OpenArgs.LoadObjects<UBehaviorTree>())
	{
		// check if we have an editor open for this BT's blackboard & use that if we can
		bool bFoundExisting = false;
		if (BehaviorTree->BlackboardAsset != nullptr)
		{
			constexpr bool bFocusIfOpen = false;
			FBehaviorTreeEditor* ExistingInstance = static_cast<FBehaviorTreeEditor*>(GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->FindEditorForAsset(static_cast<UObject*>(BehaviorTree->BlackboardAsset), bFocusIfOpen));
			if (ExistingInstance != nullptr && ExistingInstance->GetBehaviorTree() == nullptr)
			{
				ExistingInstance->InitBehaviorTreeEditor(Mode, OpenArgs.ToolkitHost, BehaviorTree);
				bFoundExisting = true;
			}
		}

		if (!bFoundExisting)
		{
			FBehaviorTreeEditorModule& BehaviorTreeEditorModule = FModuleManager::GetModuleChecked<FBehaviorTreeEditorModule>("BehaviorTreeEditor");
			auto CreatedInstance = BehaviorTreeEditorModule.CreateBehaviorTreeEditor(Mode, OpenArgs.ToolkitHost, BehaviorTree);

			FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

			FDetailsViewArgs DetailsViewArgs;
			DetailsViewArgs.bHideSelectionTip = true;
			DetailsViewArgs.bUpdatesFromSelection = false;
			DetailsViewArgs.NotifyHook = nullptr;
			DetailsViewArgs.bLockable = false;
			DetailsViewArgs.NameAreaSettings = FDetailsViewArgs::HideNameArea;


			const TSharedRef<IDetailsView> DetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
			DetailsView->SetObject(BehaviorTree);

			DetailsView->RegisterInstancedCustomPropertyLayout(
				UUtilityBehaviorTree::StaticClass(),
				FOnGetDetailCustomizationInstance::CreateStatic(&FBehaviorTreeDetailsCustomization::MakeInstance)
			);

			const TSharedRef<SWindow> DetailsWindow = SNew(SWindow)
				.Title(FText::FromString("Utility BT Details"))
				.ClientSize(FVector2D(400, 600))
				.SupportsMaximize(false)
				.SupportsMinimize(false)
				.IsTopmostWindow(true)
				[
					DetailsView
				];

			UAssetEditorSubsystem* EditorSubsystem = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>();

			UBehaviorTree* TargetBT = BehaviorTree;
			const bool bFocusIfOpen = true;

			FBehaviorTreeEditor* BTEditorInstance = static_cast<FBehaviorTreeEditor*>(
				EditorSubsystem->FindEditorForAsset(TargetBT, bFocusIfOpen)
				);


			if (BTEditorInstance)
			{
				TSharedPtr<SDockTab> HostingTab = BTEditorInstance->GetToolkitHost()->GetTabManager()->FindExistingLiveTab(BTEditorInstance->GetToolkitFName());

				if(HostingTab != nullptr)
				{
					TSharedPtr<SWindow> ParentWindow = HostingTab->GetParentWindow();
					FSlateApplication::Get().AddWindowAsNativeChild(DetailsWindow, ParentWindow.ToSharedRef());
				}
			}


			// Open the window
			FSlateApplication::Get().AddWindow(DetailsWindow);

			PropertyModule.NotifyCustomizationModuleChanged();
		}
	}
	return EAssetCommandResult::Handled;
}

EAssetCommandResult UAssetDefinitionUtilityBT::PerformAssetDiff(const FAssetDiffArgs& DiffArgs) const
{
	return Super::PerformAssetDiff(DiffArgs);
}

TSoftClassPtr<UObject> UAssetDefinitionUtilityBT::GetAssetClass() const
{
	return UUtilityBehaviorTree::StaticClass();
}
