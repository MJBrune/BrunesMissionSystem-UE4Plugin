// Copyright Underflow Studios 2017

#pragma once

#include "CoreMinimal.h"
#include "BrunesMissionSystemInterface.generated.h"

class ABruMissionManager;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBrunesMissionSystemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BRUNESMISSIONSYSTEM_API IBrunesMissionSystemInterface
{
	GENERATED_BODY()
public:
	//returns the mission system so we can find on the player controller.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Brune's Mission System")
	ABruMissionManager* GetMissionManager();
	
};
