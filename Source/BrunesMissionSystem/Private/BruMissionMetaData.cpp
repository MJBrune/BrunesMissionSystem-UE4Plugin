// Copyright Underflow Studios 2017

#include "BruMissionMetaData.h"
#include "Package.h"
#include "UObject/UObjectGlobals.h"
#include "BruMissionManager.h"

class UBruMissionTask;

UBruMissionTask* UBruMissionMetaData::ActivateTask(TSubclassOf<UBruMissionTask> MissionTask, bool bShouldBroadcastNotifyEvent)
{
	UBruMissionTask* NewMissionTask = NewObject<UBruMissionTask>(GetTransientPackage(), MissionTask);

	if (NewMissionTask->bIsUnique)
	{
		for (UBruMissionTask* ActiveMissionTask : ActiveTasks)
		{
			if (ActiveMissionTask->UniqueTaskName == NewMissionTask->UniqueTaskName)
			{
				return nullptr;
			}
		}
	}

	ActiveTasks.Add(NewMissionTask);
	NewMissionTask->ParentMissionData = this;

	NewMissionTask->OnTaskActivated.Broadcast();
	if (bShouldBroadcastNotifyEvent)
	{
		ParentMissionManager->OnAnyTaskActivated.Broadcast(NewMissionTask);
	}

	return NewMissionTask;
}

UBruMissionTask* UBruMissionMetaData::FindActivateTaskByClass(TSubclassOf<UBruMissionTask> MissionTask)
{
	for (UBruMissionTask* ActiveTask : ActiveTasks)
	{
		if (ActiveTask->GetClass() == MissionTask)
		{
			return ActiveTask;
		}
	}

	return nullptr;
}

void UBruMissionMetaData::SetMissionManager(ABruMissionManager* MissionManager)
{
	check(MissionManager); //Uhh, why we doing this? Just destroy the active mission. -mb
	ParentMissionManager = MissionManager;
}

void UBruMissionMetaData::OnMissionCompleted_Implementation(bool bMissionHasFailed)
{

}

void UBruMissionMetaData::OnMissionActivated_Implementation()
{

}

void UBruMissionMetaData::CompleteMission_Implementation(bool bMissionHasFailed)
{
	for (UBruMissionTask* ActiveTask : ActiveTasks)
	{
		for (ABruMissionActor* MissionActor : ActiveTask->RegisteredTaskActors)
		{
			ParentMissionManager->UnregisterMissionActor(MissionActor);
		}
		ActiveTask->RegisteredTaskActors.Empty();
		ActiveTask->CompleteTask(bMissionHasFailed);
	}
	bHasFailed = bMissionHasFailed;
	bHasCompleted = true;
	ParentMissionManager->SetMissionAsCompleted(this);
	OnMissionCompleted(bMissionHasFailed);
}
