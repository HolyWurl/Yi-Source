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
		if (ImGui::BeginTabItem("����ѡ��"))
		{
			if (ImGui::TreeNode("��ݼ�����"))
			{
				ImGui::BeginGroup();
				if (ImGui::Hotkey("�˵�����", &features::menuOpened))
					g_gui.m_opened = false;
				ImGui::EndGroup();

				ImGui::BeginGroup();
				ImGui::Hotkey("���͵�����", &features::tpWayPoint);
				ImGui::EndGroup();

				ImGui::BeginGroup();
				ImGui::Hotkey("���������", &features::tpObject);
				ImGui::EndGroup();

				ImGui::BeginGroup();
				ImGui::Hotkey("����", &features::goforward);
				ImGui::EndGroup();

				ImGui::TreePop();
			}
			if (ImGui::Button("�˳�Yi"))
			{
				g_running = false;
			}
			ImGui::EndTabItem();
		}
	}
}