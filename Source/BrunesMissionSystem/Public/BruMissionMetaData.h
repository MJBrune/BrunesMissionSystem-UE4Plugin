// Copyright Underflow Studios 2017

#pragma once

#include "BruMissionMetaData.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBruMissionCompletedResults, bool, bMissionHasFailed);

class UBruMissionTask;
class ABruMissionManager;

/**
 *  Mission Data Object for UI and etc.
 */
UCLASS(BlueprintType, Blueprintable)
class BRUNESMISSIONSYSTEM_API UBruMissionMetaData : public UObject
{
	GENERATED_BODY()

public:

	//Activates a task for the current mission
	UFUNCTION(BlueprintCallable, Category = "Tasks")
	virtual UBruMissionTask* ActivateTask(TSubclassOf<UBruMissionTask> MissionTask, bool bShouldBroadcastNotifyEvent = true);

	UFUNCTION(BlueprintCallable, Category = "Tasks")
	virtual UBruMissionTask* FindActivateTaskByClass(TSubclassOf<UBruMissionTask> MissionTask);

	//Called to complete the mission and close out the UI for the mission.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Task Status")
	void CompleteMission(bool bMissionHasFailed);

	//Sets the mission manager for callbacks
	UFUNCTION(BlueprintCallable, Category = "Task Status")
	virtual void SetMissionManager(ABruMissionManager* MissionManager);

	//Mission Manager in order to communicate back. NULL until OnMissionManagerSet is called.
	UPROPERTY(Transient, BlueprintReadOnly, VisibleAnywhere, Category = "Task Status")
	ABruMissionManager* ParentMissionManager;

	//The mission's creative name that explains to the player what the overall objective is. (Displayed for the entire length of mission)
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Configuration")
	FText MissionName;
	
	//The mission's overall description. (Displayed for the entire length of mission)
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Configuration")
	FText MissionDescription;

	//If true then this mission can only be activated once and completed once and will not reactivated for any reason.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Configuration")
	bool bIsUnique = true;

	//The current tasks for the active player.
	UPROPERTY(Transient, BlueprintReadOnly, EditAnywhere, Category = "Tasks")
	TArray<UBruMissionTask*> ActiveTasks;

	//Called after CompleteMission is called.
	UPROPERTY(BlueprintAssignable)
	FBruMissionCompletedResults OnMissionCompleted;

	//true if the mission is completed and should be displayed as such.
	UPROPERTY(Transient, BlueprintReadOnly, Category = "Task Status")
	bool bHasCompleted = false;

	//true if the mission has failed and should be displayed as such.
	UPROPERTY(Transient, BlueprintReadOnly, VisibleAnywhere, Category = "Task Status")
	bool bHasFailed = false;

	//This is the developer mission name for saves. Just throw in any mission name.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Configuration")
	FName UniqueMissionName;

protected:

	//All of the tasks for this mission. 
	// Note: This is for validation only. No other tasks can be activated except for these.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Tasks")
	TArray<TSubclassOf<UBruMissionTask>> Tasks;
};
