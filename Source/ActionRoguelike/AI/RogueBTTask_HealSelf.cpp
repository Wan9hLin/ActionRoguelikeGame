// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueBTTask_HealSelf.h"
#include "RogueAIController.h"
#include "SharedGameplayTag.h"
#include "ActionSystem/RogueActionSystemComponent.h"
#include "GameFramework/Character.h"

EBTNodeResult::Type URogueBTTask_HealSelf::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
	check(Pawn);
	
	URogueActionSystemComponent* ActionComp = Pawn->GetComponentByClass<URogueActionSystemComponent>();
	if (ensure(ActionComp))
	{
		ActionComp->ApplyAttributeChange(SharedGameplayTag::Attribute_Health, HealAmount, Base);
		return EBTNodeResult::Succeeded;
	}
	
	return  EBTNodeResult::Failed;
}
