// Copyright Epic Games, Inc. All Rights Reserved.


#include "GasGunPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "GasGunCameraManager.h"

AGasGunPlayerController::AGasGunPlayerController()
{
	// set the player camera manager class
	PlayerCameraManagerClass = AGasGunCameraManager::StaticClass();
}

void AGasGunPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
		{
			Subsystem->AddMappingContext(CurrentContext, 0);
		}
	}
}
