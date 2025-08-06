#include "UtilityBTDetailsCustomization.h"
#include "BehaviorTree/BehaviorTree.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "UtilityBehaviorTree.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Text/STextBlock.h"

TSharedRef<IDetailCustomization> FBehaviorTreeDetailsCustomization::MakeInstance()
{
	return MakeShareable(new FBehaviorTreeDetailsCustomization);
}

void FBehaviorTreeDetailsCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	IDetailCategoryBuilder& Category = DetailBuilder.EditCategory("Custom");

	TArray<TWeakObjectPtr<UObject>> Objects;
	DetailBuilder.GetObjectsBeingCustomized(Objects);

	if (Objects.Num() > 0 && Objects[0]->IsA<UUtilityBehaviorTree>())
	{
		UUtilityBehaviorTree* BT = Cast<UUtilityBehaviorTree>(Objects[0].Get());
	}
}