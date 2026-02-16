// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "RogueBTService_CheckRangeTo.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API URogueBTService_CheckRangeTo : public UBTService
{
	GENERATED_BODY()
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
