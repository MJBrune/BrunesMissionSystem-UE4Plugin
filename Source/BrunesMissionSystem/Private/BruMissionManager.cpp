// Copyright Underflow Studios 2017

#include "BruMissionManager.h"
#include "BruMissionActor.h"
#include "BruMissionMetaData.h"
#include "BruMissionTask.h"

// Sets default values
ABruMissionManager::ABruMissionManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABruMissionManager::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

}

void ABruMissionManager::BeginPlay()
{
	Super::BeginPlay();

}

UBruMissionMetaData* ABruMissionManager::CreateMission(TSubclassOf<UBruMissionMetaData> MissionDataClass)
{
	if (!IsValid(MissionDataClass))
	{
		return nullptr;
	}

	UBruMissionMetaData* NewMission = NewObject<UBruMissionMetaData>(GetTransientPackage(), MissionDataClass);
	ActiveMissions.AddUnique(NewMission);
	NewMission->SetMissionManager(this);
	return NewMission;
}

UBruMissionMetaData* ABruMissionManager::ActivateMission(TSubclassOf<UBruMissionMetaData> MissionDataClass)
{
	if (!IsValid(MissionDataClass))
	{
		return nullptr;
	}

	if (MissionDataClass->GetDefaultObject<UBruMissionMetaData>()->bIsUnique)
	{
		bool bHasAlreadyBeenRegistered = false;
		TArray<UBruMissionMetaData*> CombinedMissions = ActiveMissions;
		CombinedMissions.Append(CompletedMissions);
		for (UBruMissionMetaData* Mission : CombinedMissions)
		{
			if (MissionDataClass->GetDefaultObject<UBruMissionMetaData>()->MissionName.EqualTo(Mission->MissionName))
			{
				bHasAlreadyBeenRegistered = true;
			}
		}

		if (!bHasAlreadyBeenRegistered)
		{
			return CreateMission(MissionDataClass);
		}
	}
	else
	{
		return CreateMission(MissionDataClass);
	}

	return nullptr;

}

UBruMissionMetaData* ABruMissionManager::FindActiveMissionByClass(TSubclassOf<UBruMissionMetaData> MissionDataClass)
{
	if (!IsValid(MissionDataClass))
	{
		return nullptr;
	}

	for (UBruMissionMetaData* Mission : ActiveMissions)
	{
		if (MissionDataClass->GetDefaultObject<UBruMissionMetaData>()->MissionName.EqualTo(Mission->MissionName))
		{
			return Mission;
		}
	}
	return nullptr;
}

void ABruMissionManager::RegisterMissionActor(ABruMissionActor* MissionActor)
{
	PendingeMissionActors.AddUnique(MissionActor);
}

bool ABruMissionManager::HasCompletedMissionTask(TSubclassOf<UBruMissionMetaData> MissionDataClass, TSubclassOf<UBruMissionTask> TaskDataClass)
{
	if (!IsValid(MissionDataClass) || !IsValid(TaskDataClass))
	{
		return false;
	}

	for (UBruMissionMetaData* ActiveMissionData : ActiveMissions)
	{
		if (MissionDataClass->GetDefaultObject<UBruMissionMetaData>()->MissionName.EqualTo(ActiveMissionData->MissionName))
		{
			for (UBruMissionTask* MissionTaskData : ActiveMissionData->ActiveTasks)
			{
				if (TaskDataClass->GetDefaultObject<UBruMissionTask>()->TaskName.EqualTo(MissionTaskData->TaskName) && MissionTaskData->bHasCompleted)
				{
					return true;
				}
			}
		}
	}

	return false;
}

void ABruMissionManager::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	for (int32 i = PendingeMissionActors.Num() - 1; i >= 0; --i)
	{
		ABruMissionActor* MissionActor = PendingeMissionActors[i];
		for (UBruMissionMetaData* MissionData : ActiveMissions)
		{
			if (IsValid(MissionActor->ParentMissionClass) && MissionActor->ParentMissionClass->GetDefaultObject<UBruMissionMetaData>()->MissionName.EqualTo(MissionData->MissionName))
			{
				for (UBruMissionTask* MissionTaskData : MissionData->ActiveTasks)
				{
					if (IsValid(MissionActor->ParentMissionTaskClass) && MissionActor->ParentMissionTaskClass->GetDefaultObject<UBruMissionTask>()->TaskName.EqualTo(MissionTaskData->TaskName))
					{
						if (MissionTaskData->bHasCompleted)
						{
							MissionActor->Destroy(true);
						}
						MissionTaskData->RegisteredTaskActors.AddUnique(MissionActor);
						MissionActor->ParentMission = MissionData;
						MissionActor->ParentMissionTask = MissionTaskData;
						MissionActor->OnRegisterMissionActor();
					}
				}
			}
		}
	}

	PendingeMissionActors.RemoveAll([&](const ABruMissionActor* Ptr)
	{
		return Ptr->bIsRegisteredWithMission;
	});
}
