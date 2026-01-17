#pragma once

#include "Array.h"
#include "LevelSetupOption.h"
#include "Types.h"

namespace fb
{
	struct LevelSetup
	{
		LevelSetup()
		{
			m_difficultyIndex = 0;
			m_isSaveGame = false;
			m_forceReloadResources = false;
		};

		String m_name;
		Array<LevelSetupOption> m_inclusionOptions;
		u32 m_difficultyIndex;
		Array<String> m_subLevelNames;
		String m_startPoint;
		Array<s32> m_subLevelStates;
		bool m_isSaveGame;
		bool m_forceReloadResources;
	};

	namespace gw3
	{
		enum LoadScreenLevelCategory
		{
			LoadScreenLevelCategory_None = 0,
			LoadScreenLevelCategory_Social = 1,
			LoadScreenLevelCategory_Sandbox = 2,
			LoadScreenLevelCategory_PvP = 3,
			LoadScreenLevelCategory_Ops = 4
		};

		struct LevelSetup
		{
			Array<LevelSetupOption> InclusionOptions;
			u32 DifficultyIndex;
			String LoadScreen_GameMode;
			String StartPoint;
			String LevelManagerInitialLevel;
			String LoadScreen_LevelName;
			String Name;
			String LevelManagerStartPoint;
			String LoadScreen_LevelAsset;
			String Playlist;
			String LoadScreen_LevelDescription;
			LoadScreenLevelCategory LoadScreen_LevelCategory;
			bool HasPersistentSave;
			bool ForceReloadResources;
			bool IsSaveGame;
		};
	}
}
