// Copyright Underflow Studios 2017

#include "BruMissionTask.h"




void UBruMissionTask::CompleteTask_Implementation(bool bTaskHasFailed)
{
	bHasFailed = bTaskHasFailed;
	bHasCompleted = true;
	OnTaskCompleted.Broadcast(this, bTaskHasFailed);
}