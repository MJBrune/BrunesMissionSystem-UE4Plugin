// Copyright Underflow Studios 2017

#pragma once

#include "BruMissionTask.generated.h"

class ABruMissionActor;
class UBruMissionMetaData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBruTaskCompletedResults, UBruMissionTask*, FailedTask, bool, bTaskHasFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBruTaskActivatedResults);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class BRUNESMISSIONSYSTEM_API UBruMissionTask : public UObject
{
	GENERATED_BODY()
public:
	//Called to complete the task and close out the UI for the task.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Task Status")
	void CompleteTask(bool bTaskHasFailed);

	//Called after CompleteTask is called.
	UPROPERTY(BlueprintAssignable)
	FBruTaskCompletedResults OnTaskCompleted;

	//Called after ActivateTask is called.
	UPROPERTY(BlueprintAssignable)
	FBruTaskActivatedResults OnTaskActivated;

	//true if the task is completed and should be displayed as such.
	UPROPERTY(Transient, BlueprintReadOnly, VisibleAnywhere, Category = "Task Status")
	bool bHasCompleted;

	//true if the task has failed and should be displayed as such.
	UPROPERTY(Transient, BlueprintReadOnly, VisibleAnywhere, Category = "Task Status")
	bool bHasFailed;

	//If true then this mission task can only be activated once and completed once and will not reactivated for any reason.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Configuration")
	bool bIsUnique = true;

	//The task's creative name that explains to the player what the overall objective is. (Starts display at task activation and stops on mission completion.)
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Configuration")
	FText TaskName;

	//The task's overall description. (Displayed only while the task is a next usable task)
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Configuration")
	FText TaskDescription;

	UPROPERTY(Transient, BlueprintReadOnly, EditAnywhere, Category = "Task Actors")
	TArray<ABruMissionActor*> RegisteredTaskActors;

	UPROPERTY(Transient, BlueprintReadOnly, VisibleAnywhere, Category = "Mission System")
	UBruMissionMetaData* ParentMissionData;

	//Unique Mission Name used for developers to save missions.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Configuration")
	FName UniqueTaskName;
};
