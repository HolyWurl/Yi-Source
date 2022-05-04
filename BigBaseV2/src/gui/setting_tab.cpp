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
	void all_tab::setting_tab()
	{
		if (ImGui::BeginTabItem("设置选项"))
		{
			if (ImGui::TreeNode("快捷键配置"))
			{
				ImGui::BeginGroup();
				if (ImGui::Hotkey("菜单开关", &features::menuOpened))
					g_gui.m_opened = false;
				ImGui::EndGroup();

				ImGui::BeginGroup();
				ImGui::Hotkey("传送导航点", &features::tpWayPoint);
				ImGui::EndGroup();

				ImGui::BeginGroup();
				ImGui::Hotkey("传送任务点", &features::tpObject);
				ImGui::EndGroup();

				ImGui::BeginGroup();
				ImGui::Hotkey("闪现", &features::goforward);
				ImGui::EndGroup();

				ImGui::TreePop();
			}
			if (ImGui::Button("退出Yi"))
			{
				g_running = false;
			}
			ImGui::EndTabItem();
		}
	}
}