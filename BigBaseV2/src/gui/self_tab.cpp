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
#include "script_global.hpp"

static const char* Session_combo[]
{
	"多人公开战局",
	"单人公开战局",
	"邀请战局",
};
static int Session_combo_pos = 0;
char vehSpawn[100];
namespace big
{
	void all_tab::self_tab()
	{
		if (ImGui::BeginTabItem("个人选项"))
		{
			ImGui::Checkbox("无敌", &features::godmode);
			ImGui::Separator();
			if (ImGui::Button("传送任务点"))
				{
					g_fiber_pool->queue_job([]
					{
						static const int blips[] = { 1, 57, 128, 129, 130, 143, 144, 145, 146, 271, 286, 287, 288 };
						for (int i = 0; i < 13; i++) {
							if (features::to_blip(blips[i])) {
								break;
							}

						}
					});
				}
			ImGui::SameLine();
			if (ImGui::Button("传送导航点"))
				{
					g_fiber_pool->queue_job([]
					{
						if (!features::to_blip((int)BlipIcons::Waypoint))
						{
							features::notifyfmt("无法找到导航点");
						}
					});
				}
			ImGui::SameLine();
			if (ImGui::Button("闪现")) {
				g_fiber_pool->queue_job([]
				{
					features::GoForward();
				});
			}
			if (ImGui::Button("补满血"))
			{
				g_fiber_pool->queue_job([]
				{
					ENTITY::SET_ENTITY_HEALTH(PLAYER::PLAYER_PED_ID(), PED::GET_PED_MAX_HEALTH(PLAYER::PLAYER_PED_ID()), 0);
				});
			}
			ImGui::SameLine();
			if (ImGui::Button("补满护甲"))
			{
				g_fiber_pool->queue_job([]
				{
					PED::ADD_ARMOUR_TO_PED(PLAYER::PLAYER_PED_ID(), PLAYER::GET_PLAYER_MAX_ARMOUR(PLAYER::PLAYER_ID()) - PED::GET_PED_ARMOUR(PLAYER::PLAYER_PED_ID()));
				});
			}
			ImGui::Separator();
			ImGui::InputText("车辆名称(英文)", vehSpawn, 100);
			ImGui::SameLine();
			if (ImGui::Button("生成载具")) {
				g_fiber_pool->queue_job([]
				{
					auto hash = rage::joaat(vehSpawn);
					if (STREAMING::IS_MODEL_VALID(hash)) {
						features::SpawnVehicle(vehSpawn);
					}
					else
					{
						features::notifyfmt("模型无效");
					}
				});
				
			}
			ImGui::Combo("选择战局", &Session_combo_pos, Session_combo, sizeof(Session_combo) / sizeof(*Session_combo));
			ImGui::SameLine();
			if (ImGui::Button("加入战局")) {
				switch (Session_combo_pos)
				{
				case 0:
				{
					g_fiber_pool->queue_job([]
					{
						*script_global(1575004).as<int*>() = 0;	//1，单人公开  0，多人公开 2，帮会 10，单人 6，好友 11，邀请
						*script_global(1574587).as<int*>() = 1;
						script::get_current()->yield(200ms);
						*script_global(1574587).as<int*>() = 0;
					});
					break;
				}
				case 1:
				{
					g_fiber_pool->queue_job([]
					{
						*script_global(1575004).as<int*>() = 1;	//1，单人公开  0，多人公开 2，帮会 10，单人 6，好友 11，邀请
						*script_global(1574587).as<int*>() = 1;
						script::get_current()->yield(200ms);
						*script_global(1574587).as<int*>() = 0;
					});
					break;
				}
				case 2:
				{
					g_fiber_pool->queue_job([]
					{
						*script_global(1575004).as<int*>() = 11;	//1，单人公开  0，多人公开 2，帮会 10，单人 6，好友 11，邀请
						*script_global(1574587).as<int*>() = 1;
						script::get_current()->yield(200ms);
						*script_global(1574587).as<int*>() = 0;
					});
					break;
				}
				}
			}
			ImGui::EndTabItem();
		}
	}
}