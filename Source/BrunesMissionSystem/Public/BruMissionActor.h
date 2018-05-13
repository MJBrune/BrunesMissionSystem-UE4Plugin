// Copyright Underflow Studios 2017

#pragma once

#include "Engine.h"
#include "Components/WidgetComponent.h"
#include "BruMissionActor.generated.h"

class UBruMissionTask;
class UBruMissionMetaData;

/*
* Represents a mission action like kill this or go here. In the real world.
*/
UCLASS(Abstract)
class BRUNESMISSIONSYSTEM_API ABruMissionActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ABruMissionActor(const class FObjectInitializer& ObjectInitializer);

	// Called when the actor is registered with the active mission and task.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Mission System")
	void OnRegisterMissionActor();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Mission System")
	void OnUnregisterMissionActor();

	//True if the mission manager has found an active mission for this actor.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mission System")
	bool bIsRegisteredWithMission = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mission System")
	TSubclassOf<UBruMissionTask> ParentMissionTaskClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mission System")
	TSubclassOf<UBruMissionMetaData> ParentMissionClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mission System")
	UBruMissionTask* ParentMissionTask;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mission System")
	UBruMissionMetaData* ParentMission;
	
	//Used when you need this actor to be very unique
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mission System")
	FString UniqueMissionActorID;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Defaults")
	USceneComponent* RootSceneComponent;

	//ToDo: Write waypoint system in order to support multiple locations.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "HUD")
	UWidgetComponent* TaskWaypointWidget;

protected:
	virtual void BeginPlay() override;
	
};
