// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class PuzzlePlatforms_MTarget : TargetRules
{
	public PuzzlePlatforms_MTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		ExtraModuleNames.Add("PuzzlePlatforms_M");
	}
}
