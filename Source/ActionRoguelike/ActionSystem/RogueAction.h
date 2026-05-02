// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "RogueAction.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API URogueAction : public UObject
{
	GENERATED_BODY()
	
protected:
	
	UPROPERTY(EditAnywhere, Category="Actions")
	FName ActionName;
	
public:
	
	void StrartAction();
	
	// implementaion inline
	FName GetActionName() const
	{
		return ActionName;
	}
	
};
