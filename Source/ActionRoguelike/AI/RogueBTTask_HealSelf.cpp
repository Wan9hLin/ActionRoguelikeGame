// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueBTTask_HealSelf.h"
#include "RogueAIController.h"
#include "ActionSystem/RogueActionSystemComponent.h"
#include "GameFramework/Character.h"

EBTNodeResult::Type URogueBTTask_HealSelf::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
	check(Pawn);
	
	URogueActionSystemComponent* ActionComp = Pawn->GetComponentByClass<URogueActionSystemComponent>();
	if (ensure(ActionComp))
	{
		ActionComp->ApplyHealthChange(HealAmount);
		return EBTNodeResult::Succeeded;
	}
	
	return  EBTNodeResult::Failed;
}
