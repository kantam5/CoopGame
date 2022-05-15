// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#define SURFACE_FLESHDEFAULT		SurfaceType1
#define SURFACE_FLESHVULNERABLE		SurfaceType2

#define COLLISTION_WEAPON			ECC_GameTraceChannel1

/* Shorthand for adding netmode into log messages */
#define NETMODE_WORLD (((GEngine == nullptr) || (GetWorld() == nullptr)) ? TEXT("") \
        : (GEngine->GetNetMode(GetWorld()) == NM_Client) ? TEXT("[Client] ") \
        : (GEngine->GetNetMode(GetWorld()) == NM_ListenServer) ? TEXT("[ListenServer] ") \
        : (GEngine->GetNetMode(GetWorld()) == NM_DedicatedServer) ? TEXT("[DedicatedServer] ") \
        : TEXT("")) // Empty (for NM_Standalone)