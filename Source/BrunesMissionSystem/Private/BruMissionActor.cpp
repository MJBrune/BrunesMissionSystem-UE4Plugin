// Copyright Underflow Studios 2017

#include "BruMissionActor.h"
#include "BruMissionManager.h"
#include "Engine.h"
#include "BrunesMissionSystemInterface.h"
#include "Components/WidgetComponent.h"


ABruMissionActor::ABruMissionActor(const class FObjectInitializer& ObjectInitializer)
{
	RootSceneComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Root Scene Component"));
	SetRootComponent(RootSceneComponent);

	TaskWaypointWidget = ObjectInitializer.CreateDefaultSubobject<UWidgetComponent>(this, TEXT("Task Waypoint Widget"));
	TaskWaypointWidget->SetupAttachment(GetRootComponent());
	TaskWaypointWidget->SetWidgetSpace(EWidgetSpace::Screen);
}

void ABruMissionActor::OnRegisterMissionActor_Implementation()
{
	bIsRegisteredWithMission = true;
	TaskWaypointWidget->SetVisibility(true);
}

void ABruMissionActor::BeginPlay()
{
	Super::BeginPlay();

	TaskWaypointWidget->SetVisibility(false);

	APlayerController* SinglePlayerController = GetWorld()->GetFirstPlayerController();

	if (IsValid(SinglePlayerController) && SinglePlayerController->GetClass()->ImplementsInterface(UBrunesMissionSystemInterface::StaticClass()))
	{
		ABruMissionManager* MissionManager = IBrunesMissionSystemInterface::Execute_GetMissionManager(SinglePlayerController);

		if (IsValid(MissionManager))
		{
			MissionManager->RegisterMissionActor(this);
		}
	}
}