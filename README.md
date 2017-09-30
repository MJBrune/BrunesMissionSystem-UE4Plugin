# BrunesMissionSystem-UE4Plugin
A large-scale single player mission system that will handle the complexities laid out in the gdc 2017 talk: https://www.gdcvault.com/play/1024158/Building-Non-linear-Narratives-in

## Usage

-- Mission Actors are world representations of task objectives. Such as holding a location to go or attaching to the actor one must follow/kill/etc.

-- Missions MetaData and Task Data are simple data oritented uobjects (not dataassets because they like to seralize which we don't need.) They hold things like descriptions of the mission/task/action and talk to the player directly via the mission menu or mission task notification system.

-- Mission Manager. This is the object that handles a players missions. The only supported place currently to put this is the PlayerController with the BrunesMissionSystemInterface in order for the system to utilize it.

```
#include "BrunesMissionSystemInterface.h"

class ABruMissionManager;

class AJPPlayerController : public APlayerController, public IBrunesMissionSystemInterface
{
	GENERATED_BODY()

public:
	virtual void OnConstruction(const FTransform& Transform) override;

	ABruMissionManager* GetMissionManager_Implementation() override;
private:
	ABruMissionManager* MissionSystemManager;

};
```

``` 
void AJPPlayerController::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	MissionSystemManager = GetWorld()->SpawnActor<ABruMissionManager>(ABruMissionManager::StaticClass(), GetActorTransform());
} 
```

### Commit Guide

Follow https://docs.unrealengine.com/latest/INT/Programming/Development/CodingStandard/ and https://github.com/Allar/ue4-style-guide

### License

BSD 2-Clause License

Copyright (c) 2017, Michael Brune
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
