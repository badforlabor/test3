// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "MyPluginPrivatePCH.h"

#include "SlateBasics.h"
#include "SlateExtras.h"

#include "MyPluginStyle.h"
#include "MyPluginCommands.h"

#include "LevelEditor.h"

static const FName MyPluginTabName("MyPlugin");

#define LOCTEXT_NAMESPACE "FMyPluginModule"
DECLARE_LOG_CATEGORY_EXTERN(MyLog, Verbose, All);
DEFINE_LOG_CATEGORY(MyLog);
class FMyPluginProcessor : public TSharedFromThis<FMyPluginProcessor>
{
public:
	FReply OnAddSpeed(int ) ;
	FReply OnSubSpeed(int) ;
	~FMyPluginProcessor()
	{
		UE_LOG(MyLog, Verbose, TEXT("~FMyPluginProcessor"));
	}
	FMyPluginModule* MyModule;

	// 当前的游戏速度
	float GetCurrentSpeed()
	{
		float timeDilation = 0;
		UWorld* World = NULL;

		if (GIsEditor && GEditor->PlayWorld && !GIsPlayInEditorWorld)
		{
			World = GEditor->PlayWorld;
		}
		if (World == NULL)
		{
			ULocalPlayer* player = GEngine->GetDebugLocalPlayer();
			if (player != NULL)
			{
				World = player->GetWorld();
			}
		}
		if (World != NULL)
		{
			timeDilation = World->GetWorldSettings()->TimeDilation;
		}
		return timeDilation;
	}

	void AddSpeed(float delta)
	{
		UWorld* World = NULL;

		if (GIsEditor && GEditor->PlayWorld && !GIsPlayInEditorWorld)
		{
			World = GEditor->PlayWorld;
		}
		if (World == NULL)
		{
			ULocalPlayer* player = GEngine->GetDebugLocalPlayer();
			if (player != NULL)
			{
				World = player->GetWorld();
			}
		}
		if (World != NULL)
		{
			World->GetWorldSettings()->SetTimeDilation(World->GetWorldSettings()->TimeDilation + delta);
		}

		if (MyModule != NULL)
		{
			MyModule->TextSpeed->SetText(FString::Printf(TEXT("Current Speed:%f"), GetCurrentSpeed()));
		}
	}
	void MiniFPS(const FText& NewText, ETextCommit::Type CommitInfo)
	{
		FFloatRange& oldv = GEngine->SmoothedFrameRateRange;
		FString v = NewText.ToString();
		GEngine->SmoothedFrameRateRange = FFloatRange(FPlatformString::Atof(*v), oldv.GetUpperBoundValue());
	}
	void MaxFPS(const FText& NewText, ETextCommit::Type CommitInfo)
	{
		FFloatRange& oldv = GEngine->SmoothedFrameRateRange;
		FString v = NewText.ToString();
		GEngine->SmoothedFrameRateRange = FFloatRange(oldv.GetLowerBoundValue(), FPlatformString::Atof(*v));
	}
};
FReply FMyPluginProcessor::OnAddSpeed(int) 
{
	//UE_LOG(MyLog, Verbose, TEXT("ADD SPEED"));
	AddSpeed(0.1f);
	return FReply::Handled();
}
FReply FMyPluginProcessor::OnSubSpeed(int) 
{
	//UE_LOG(MyLog, Verbose, TEXT("SUB SPEED"));
	AddSpeed(-0.1f);
	return FReply::Handled();
}

void FMyPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FMyPluginStyle::Initialize();
	FMyPluginStyle::ReloadTextures();

	FMyPluginCommands::Register();

	PluginCommands = MakeShareable(new FUICommandList);
	p = MakeShareable(new FMyPluginProcessor);
	p->MyModule = this;

	PluginCommands->MapAction(
		FMyPluginCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FMyPluginModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FMyPluginModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FMyPluginModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(MyPluginTabName, FOnSpawnTab::CreateRaw(this, &FMyPluginModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FMyPluginTabTitle", "MyPlugin"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FMyPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FMyPluginStyle::Shutdown();

	FMyPluginCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(MyPluginTabName);
}
TSharedRef<SDockTab> FMyPluginModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
#if false
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FMyPluginModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("MyPlugin.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
#else

	//FMyPluginProcessor* p = (new FMyPluginProcessor);
	//p = MakeShareable(new FMyPluginProcessor);
	//FMyPluginProcessor* p = new FMyPluginProcessor;
	FFloatRange& oldv = GEngine->SmoothedFrameRateRange;

	return SNew(SDockTab)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.MaxHeight(25)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				[
					SAssignNew(TextSpeed, STextBlock).Text(FText::FromString(FString::Printf(TEXT("current speed:%f"), p->GetCurrentSpeed())))
				]
				+ SHorizontalBox::Slot()
				[
					SNew(SButton).Text(FText::FromString("add speed"))
					.OnClicked(FOnClicked::CreateSP<FMyPluginProcessor, int>(p.Get(), &FMyPluginProcessor::OnAddSpeed, 0))
				]
				+ SHorizontalBox::Slot()
				[
					SNew(SButton).Text(FText::FromString("slow speed"))
					.OnClicked(FOnClicked::CreateSP<FMyPluginProcessor, int>(p.Get(), &FMyPluginProcessor::OnSubSpeed, 0))
					//
				]
			]
			+ SVerticalBox::Slot()
			.MaxHeight(25)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()				
				[
					SNew(STextBlock).Text(FText::FromString(TEXT("fps range:")))
				]
				+ SHorizontalBox::Slot()
					.MaxWidth(50)
				[
					SAssignNew(FPSMini, SEditableText)
					.Text(FText::FromString(FString::Printf(TEXT("%.1f"), oldv.HasLowerBound() ? oldv.GetLowerBoundValue() : 0)))
					.OnTextCommitted(p.Get(), &FMyPluginProcessor::MiniFPS)
				]
				+ SHorizontalBox::Slot()
					.MaxWidth(20)
					[
						SNew(STextBlock).Text(FText::FromString(TEXT(" ~ ")))
					]
				+ SHorizontalBox::Slot()
					.MaxWidth(50)
				[
					SAssignNew(FPSMax, SEditableText)
					.Text(FText::FromString(FString::Printf(TEXT("%.1f"), oldv.HasUpperBound() ? oldv.GetUpperBoundValue() : 10000)))
					.OnTextCommitted(p.Get(), &FMyPluginProcessor::MaxFPS)
				]
			]
		];
#endif
}


FReply FMyPluginModule::OnAddSpeed() const
{
	return FReply::Handled();
}
FReply FMyPluginModule::OnSubSpeed() const
{
	return FReply::Handled();
}

void FMyPluginModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(MyPluginTabName);
}

void FMyPluginModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FMyPluginCommands::Get().OpenPluginWindow);
}

void FMyPluginModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FMyPluginCommands::Get().OpenPluginWindow);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMyPluginModule, MyPlugin)