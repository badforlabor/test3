// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;

class FMyPluginModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command (by default it will bring up plugin window) */
	void PluginButtonClicked();
	
private:

	void AddToolbarExtension(FToolBarBuilder& Builder);
	void AddMenuExtension(FMenuBuilder& Builder);

	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);
	FReply OnAddSpeed() const;
	FReply OnSubSpeed() const;
public:
	TSharedPtr<class FMyPluginProcessor> p;
	TSharedPtr<STextBlock> TextSpeed;
	TSharedPtr<SEditableText> FPSMini;
	TSharedPtr<SEditableText> FPSMax;
private:
	TSharedPtr<class FUICommandList> PluginCommands;
};