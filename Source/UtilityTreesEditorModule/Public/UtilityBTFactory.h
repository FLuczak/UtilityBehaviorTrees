// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "UtilityBTFactory.generated.h"

/**
 * 
 */
UCLASS()
class UTILITYTREESEDITOR_API UUtilityBTFactory : public UFactory
{
	GENERATED_BODY()
public:
	UUtilityBTFactory();
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	virtual bool ShouldShowInNewMenu() const override { return true; }
};
