// Copyright Underflow Studios 2017

#include "BruMissionMetaData.h"
#include "BruMissionTask.h"
#include "BruMissionManager.h"

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

void UBruMissionMetaData::CompleteMission_Implementation(bool bMissionHasFailed)
{
	bHasFailed = bMissionHasFailed;
	bHasCompleted = true;
	OnMissionCompleted.Broadcast(bMissionHasFailed);
}
