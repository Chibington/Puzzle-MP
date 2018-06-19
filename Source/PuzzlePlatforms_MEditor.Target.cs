// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class PuzzlePlatforms_MEditorTarget : TargetRules
{
	public PuzzlePlatforms_MEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		ExtraModuleNames.Add("PuzzlePlatforms_M");
	}
}
