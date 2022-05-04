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
		if (ImGui::BeginTabItem("����ѡ��"))
		{
			ImGui::Checkbox("�Զ�Crash����", &features::autoCrashggj);
			ImGui::SameLine();
			ImGui::Checkbox("Shield����", &features::antiggj);
			ImGui::Checkbox("��ֹ�ٱ�", &features::antiIncreEvent);
			ImGui::EndTabItem();
		}
	}
}