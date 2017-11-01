// Copyright Underflow Studios 2017

#pragma once

#include "GameFramework/Actor.h"
#include "BruMissionManager.generated.h"

class UBruMissionMetaData;
class ABruMissionActor;
class UBruMissionTask;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBruAnyTaskActivatedResults, UBruMissionTask*, Task);

//Mission manager for each player, typically on the player state or player controller.
UCLASS()
class BRUNESMISSIONSYSTEM_API ABruMissionManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABruMissionManager();

	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void Tick(float DeltaSeconds) override;

	//Called anytime a task is activated.
	UPROPERTY(BlueprintAssignable)
	FBruAnyTaskActivatedResults OnAnyTaskActivated;
	
	//Creates a new mission for the specified player.
	UFUNCTION(BlueprintCallable, Category = "Mission System")
	UBruMissionMetaData* CreateMission(TSubclassOf<UBruMissionMetaData> MissionDataClass);

	//Activates a new mission for the specified player.
	//Returns the active mission. Returns nullptr if it's a unique mission that's already been created.
	UFUNCTION(BlueprintCallable, Category = "Mission System")
	virtual UBruMissionMetaData* ActivateMission(TSubclassOf<UBruMissionMetaData> MissionData);

	//Returns the first found active mission that matches the class entered.
	UFUNCTION(BlueprintCallable, Category = "Mission System")
	virtual UBruMissionMetaData* FindActiveMissionByClass(TSubclassOf<UBruMissionMetaData> MissionDataClass);

	//Called to register a mission actor with the mission manager to tie it to a task.
	UFUNCTION(BlueprintCallable, Category = "Mission System")
	virtual void RegisterMissionActor(ABruMissionActor* MissionActor);

	//Called to register a mission actor with the mission manager to tie it to a task.
	UFUNCTION(BlueprintCallable, Category = "Mission System")
	virtual bool HasCompletedMissionTask(TSubclassOf<UBruMissionMetaData> MissionData, TSubclassOf<UBruMissionTask> TaskData);

protected:
	virtual void BeginPlay() override;

	//The completed missions for the active player.
	UPROPERTY(BlueprintReadOnly, Category = "Mission System")
	TArray<UBruMissionMetaData*> CompletedMissions;

	//The current missions for the active player.
	UPROPERTY(BlueprintReadOnly, Category = "Mission System")
	TArray<UBruMissionMetaData*> ActiveMissions;

	//The mission actors that want to be registered but the mission or task isn't activated yet.
	UPROPERTY(BlueprintReadWrite, Category = "Mission System")
	TArray<ABruMissionActor*> PendingeMissionActors;
};
