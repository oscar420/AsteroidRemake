// Copyright Epic Games, Inc. All Rights Reserved.

#include "AsteroidRemakeGameMode.h"
#include "AsteroidRemakePawn.h"

AAsteroidRemakeGameMode::AAsteroidRemakeGameMode()
{
	// set default pawn class to our flying pawn
	DefaultPawnClass = AAsteroidRemakePawn::StaticClass();
}
