// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "RogueAction.generated.h"

class URogueActionSystemComponent;

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class ACTIONROGUELIKE_API URogueAction : public UObject
{
	GENERATED_BODY()
	
protected:
	
	UPROPERTY(EditAnywhere, Category="Actions")
	FName ActionName = FName("PrimaryAttack");
	
public:
	
	UFUNCTION(BlueprintCallable)
	URogueActionSystemComponent* GetOwningComponent() const;

	UFUNCTION(BlueprintNativeEvent, Category = "Actions")
	void StrartAction();
	
	UFUNCTION(BlueprintNativeEvent, Category = "Actions")
	void StopAction();
	
	// implementaion inline
	FName GetActionName() const
	{
		return ActionName;
	}
	
};
