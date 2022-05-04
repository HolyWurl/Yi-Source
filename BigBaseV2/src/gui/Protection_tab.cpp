#include "common.hpp"
#include "all_tab.h"
#include "imgui.h"
#include "script.hpp"
#include "fiber_pool.hpp"
#include "natives.hpp"
#include "gta_util.hpp"
#include "ImGuiBitfield.h"
#include "features.hpp"
#include "../imgui_hotkey.hpp"
#include "gui.hpp"

namespace big
{
	void all_tab::Protection_tab()
	{
		if (ImGui::BeginTabItem("保护选项"))
		{
			ImGui::Checkbox("自动Crash广告机", &features::autoCrashggj);
			ImGui::SameLine();
			ImGui::Checkbox("Shield广告机", &features::antiggj);
			ImGui::Checkbox("阻止举报", &features::antiIncreEvent);
			ImGui::EndTabItem();
		}
	}
}