// Fill out your copyright notice in the Description page of Project Settings.


#include "UtilityBTFactory.h"

#include "UtilityBehaviorTree.h"

UUtilityBTFactory::UUtilityBTFactory()
{
	SupportedClass = UUtilityBehaviorTree::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UUtilityBTFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags,
	UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UUtilityBehaviorTree>(InParent, Class, Name, Flags);
}
