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

static const char* endDay_combo[]
{
	"数据泄露",
	"波格丹危机",
	"末日将至"
};
static const char* Contract_combo[]
{
	"夜生活泄密",
	"上流社会泄密",
	"南中心泄密",
	"分红关(档案任务)(xx博士)",
	"通关"
};
static int Contract_combo_pos = 0;
static int endDay_combo_pos = 0;
int player1 = 100, player2 = 100, player3 = 100, player4 = 100;
int finalMoney = 1000000;
namespace big
{
	void all_tab::task_tab()
	{
		if (ImGui::BeginTabItem("任务选项"))
		{
			if (ImGui::TreeNode("佩里克岛")) {
				if (ImGui::Button("重置面板")) {
					g_fiber_pool->queue_job([]
					{
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H4_MISSIONS"), 0, 0);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H4_PROGRESS"), 0, 0);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H4_PLAYTHROUGH_STATUS"), 0, 0);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H4CNF_APPROACH"), 0, 0);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H4CNF_BS_ENTR"), 0, 0);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H4CNF_BS_GEN"), 0, 0);
						//
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H4_MISSIONS"), 0, 0);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H4_PROGRESS"), 0, 0);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H4_PLAYTHROUGH_STATUS"), 0, 0);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H4CNF_APPROACH"), 0, 0);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H4CNF_BS_ENTR"), 0, 0);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H4CNF_BS_GEN"), 0, 0);
						features::notifyfmt("已执行");
					});
				}
				ImGui::SameLine();
				if (ImGui::Button("跳过前置")) {
					g_fiber_pool->queue_job([]
					{
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H4CNF_BS_GEN"), 131071, 0);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H4CNF_BS_ENTR"), 63, 0);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H4CNF_BS_ABIL"), 63, 0);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H4CNF_APPROACH"), -1, 0);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H4_PROGRESS"), 131055, 0);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H4CNF_TARGET"), 5, 0);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H4_MISSIONS"), 65345, 0);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H4CNF_WEAPONS"), 2, 0);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H4CNF_TROJAN"), 1, 0);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H4_PLAYTHROUGH_STATUS"), 10, 0);
						//
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H4CNF_BS_GEN"), 131071, 0);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H4CNF_BS_ENTR"), 63, 0);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H4CNF_BS_ABIL"), 63, 0);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H4CNF_APPROACH"), -1, 0);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H4_PROGRESS"), 131055, 0);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H4CNF_TARGET"), 5, 0);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H4_MISSIONS"), 65345, 0);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H4CNF_WEAPONS"), 2, 0);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H4CNF_TROJAN"), 1, 0);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H4_PLAYTHROUGH_STATUS"), 10, 0);
						features::notifyfmt("已执行");
					});
				}
				ImGui::Separator();
				ImGui::InputInt("玩家1分红", &player1);
				ImGui::SameLine();
				if(ImGui::Button("修改")) {
					*script_global(1973496).at(823).at(56).at(1).as<int*>() = player1;
				}
				ImGui::InputInt("玩家2分红", &player2);
				ImGui::SameLine();
				if (ImGui::Button("修改")) {
					*script_global(1973496).at(823).at(56).at(2).as<int*>() = player2;
				}
				ImGui::InputInt("玩家3分红", &player3);
				ImGui::SameLine();
				if (ImGui::Button("修改")) {
					*script_global(1973496).at(823).at(56).at(3).as<int*>() = player3;
				}
				ImGui::InputInt("玩家4分红", &player4);
				ImGui::SameLine();
				if (ImGui::Button("修改")) {
					*script_global(1973496).at(823).at(56).at(4).as<int*>() = player4;
				}
				ImGui::Separator();
				if (ImGui::Button("杀死队友")) {
					g_fiber_pool->queue_job([]
					{
						for (int i = 0; i < 4; i++) {
							if (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i)) && PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i) != PLAYER::PLAYER_ID()) {
								Vector3 Coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), 1);
								FIRE::ADD_EXPLOSION(Coords.x, Coords.y, Coords.z, 0, 1, 1, 0, 1, 0);
							}
						}
						features::notifyfmt("已执行");
					});
				}
				ImGui::SameLine();
				if (ImGui::Button("传送雕像")) {
					g_fiber_pool->queue_job([]
					{
						ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 5006.70, -5755.89, 15.48, 1, 0, 0, 0);
						script::get_current()->yield();
					});
				}
				ImGui::SameLine();
				if (ImGui::Button("传送大门(拿完雕像用)")) {
					g_fiber_pool->queue_job([]
					{
						ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 4990.74, -5717.96, 19.88, 1, 0, 0, 0);
						script::get_current()->yield();
					});
				}
				ImGui::SameLine();
				if (ImGui::Button("逃跑")) {
					g_fiber_pool->queue_job([]
					{
						ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 4580, -6012, 3, 1, 0, 0, 0);
						script::get_current()->yield();
					});
				}
				ImGui::TreePop();
			}
			if (ImGui::TreeNode("赌场豪劫")) {
				if (ImGui::Button("跳过前置(兵不厌炸方案)")) {
					g_fiber_pool->queue_job([]
					{
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_TARGET"), 3, 0);
						//
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H3OPT_TARGET"), 3, 0);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_APPROACH"), 2, 0);
						//
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H3OPT_APPROACH"), 2, 0);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_ACCESSPOINTS"), -1, 0);
						//
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H3OPT_ACCESSPOINTS"), -1, 0);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_POI"), -1, 0);
						//
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H3OPT_POI"), -1, 0);
						script::get_current()->yield(50ms);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_BITSET1"), -1, 0);
						//
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H3OPT_BITSET1"), -1, 0);
						script::get_current()->yield(2000ms);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_DISRUPTSHIP"), 3, 0);
						//
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H3OPT_DISRUPTSHIP"), 3, 0);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_KEYLEVELS"), 2, 0);
						//
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H3OPT_KEYLEVELS"), 2, 0);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_CREWDRIVER"), 5, 0);
						//
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H3OPT_CREWDRIVER"), 5, 0);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_CREWWEAP"), 4, 0);
						//
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H3OPT_CREWWEAP"), 4, 0);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_CREWHACKER"), 4, 0);
						//
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H3OPT_CREWHACKER"), 4, 0);
						script::get_current()->yield(50ms);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_BITSET0"), -1, 0);
						//
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H3OPT_BITSET0"), -1, 0);
						features::notifyfmt("已执行");
					});
				}
				ImGui::SameLine();
				if (ImGui::Button("重置第一块板")) {
					g_fiber_pool->queue_job([]
					{
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_BITSET1"), 0, 0);
						//
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H3OPT_BITSET1"), 0, 0);
						features::notifyfmt("已执行");
					});
				}
				ImGui::SameLine();
				if (ImGui::Button("重置第二块板")) {
					g_fiber_pool->queue_job([]
					{
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_BITSET0"), 0, 0);
						//
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H3OPT_BITSET0"), 0, 0);
						features::notifyfmt("已执行");
					});
				}
				ImGui::Separator();
				ImGui::InputInt("玩家1分红", &player1);
				ImGui::SameLine();
				if (ImGui::Button("修改")) {
					*script_global(1966718).at(1497).at(736).at(92).at(1).as<int*>() = player1;
				}
				ImGui::InputInt("玩家2分红", &player2);
				ImGui::SameLine();
				if (ImGui::Button("修改")) {
					*script_global(1966718).at(1497).at(736).at(92).at(2).as<int*>() = player2;
				}
				ImGui::InputInt("玩家3分红", &player3);
				ImGui::SameLine();
				if (ImGui::Button("修改")) {
					*script_global(1966718).at(1497).at(736).at(92).at(3).as<int*>() = player3;
				}
				ImGui::InputInt("玩家4分红", &player4);
				ImGui::SameLine();
				if (ImGui::Button("修改")) {
					*script_global(1966718).at(1497).at(736).at(92).at(4).as<int*>() = player4;
				}
				if (ImGui::Button("删除NPC分红(包括来斯特)")) {
					g_fiber_pool->queue_job([]
					{
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_CREWWEAP"), 6, 0);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_CREWDRIVER"), 6, 0);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_CREWHACKER"), 6, 0);
						//
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H3OPT_CREWWEAP"), 6, 0);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H3OPT_CREWDRIVER"), 6, 0);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H3OPT_CREWHACKER"), 6, 0);
						*script_global(262145).at(28439).as<float*>() = 0;
						features::notifyfmt("已执行");
					});
				}
				ImGui::Separator();
				if (ImGui::Button("修复拍照")) {
					g_fiber_pool->queue_job([]
					{
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_BITSET1"), 0, 0);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_BITSET0"), 0, 0);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_POI"), 0, 0);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_ACCESSPOINTS"), 0, 0);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CAS_HEIST_FLOW"), 0, 0);
						//
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H3OPT_BITSET1"), 0, 0);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H3OPT_BITSET0"), 0, 0);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H3OPT_POI"), 0, 0);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H3OPT_ACCESSPOINTS"), 0, 0);
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CAS_HEIST_FLOW"), 0, 0);
						features::notifyfmt("已执行");
					});
				}
				ImGui::TreePop();
			}
			if (ImGui::TreeNode("末日抢劫")) {
				ImGui::Combo("选择前置", &endDay_combo_pos, endDay_combo, sizeof(endDay_combo) / sizeof(*endDay_combo));
				ImGui::SameLine();
				if (ImGui::Button("跳过前置")) {
					g_fiber_pool->queue_job([]
					{
						switch (endDay_combo_pos)
						{
						case 0:
						{
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_GANGOPS_FLOW_MISSION_PROG"), 503, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_GANGOPS_HEIST_STATUS"), 229383, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_GANGOPS_FLOW_NOTIFICATIONS"), 1557, 0);
							//
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_GANGOPS_FLOW_MISSION_PROG"), 503, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_GANGOPS_HEIST_STATUS"), 229383, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_GANGOPS_FLOW_NOTIFICATIONS"), 1557, 0);
							features::notifyfmt("已跳过前置:~b~数据泄露");
							break;
						}
						case 1:
						{
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_GANGOPS_FLOW_MISSION_PROG"), 240, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_GANGOPS_HEIST_STATUS"), 229378, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_GANGOPS_FLOW_NOTIFICATIONS"), 1557, 0);
							//
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_GANGOPS_FLOW_MISSION_PROG"), 240, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_GANGOPS_HEIST_STATUS"), 229378, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_GANGOPS_FLOW_NOTIFICATIONS"), 1557, 0);
							features::notifyfmt("已跳过前置:~b~波格丹危机");
							break;
						}
						case 2:
						{
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_GANGOPS_FLOW_MISSION_PROG"), 16368, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_GANGOPS_HEIST_STATUS"), 229380, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_GANGOPS_FLOW_NOTIFICATIONS"), 1557, 0);
							//
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_GANGOPS_FLOW_MISSION_PROG"), 16368, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_GANGOPS_HEIST_STATUS"), 229380, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_GANGOPS_FLOW_NOTIFICATIONS"), 1557, 0);
							features::notifyfmt("已跳过前置:~b~末日将至");
							break;
						}
						}
					});
				}
				ImGui::Separator();
				ImGui::InputInt("玩家1分红", &player1);
				ImGui::SameLine();
				if (ImGui::Button("修改")) {
					*script_global(1962755).at(812).at(50).at(1).as<int*>() = player1;
				}
				ImGui::InputInt("玩家2分红", &player2);
				ImGui::SameLine();
				if (ImGui::Button("修改")) {
					*script_global(1962755).at(812).at(50).at(2).as<int*>() = player2;
				}
				ImGui::InputInt("玩家3分红", &player3);
				ImGui::SameLine();
				if (ImGui::Button("修改")) {
					*script_global(1962755).at(812).at(50).at(3).as<int*>() = player3;
				}
				ImGui::InputInt("玩家4分红", &player4);
				ImGui::SameLine();
				if (ImGui::Button("修改")) {
					*script_global(1962755).at(812).at(50).at(4).as<int*>() = player4;
				}
				ImGui::TreePop();
			}
			if (ImGui::TreeNode("Apartment抢劫")) {
				if (ImGui::Button("跳过前置(动画中使用)")) {
					g_fiber_pool->queue_job([]
					{
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_HEIST_PLANNING_STAGE"), -1, 0);
						//
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_HEIST_PLANNING_STAGE"), -1, 0);
						features::notifyfmt("已执行");
					});
				}
				ImGui::Separator();
				ImGui::InputInt("玩家1分红", &player1);
				ImGui::SameLine();
				if (ImGui::Button("修改")) {
					*script_global(1934631).at(3008).at(1).as<int*>() = player1;
				}
				ImGui::InputInt("玩家2分红", &player2);
				ImGui::SameLine();
				if (ImGui::Button("修改")) {
					*script_global(1934631).at(3008).at(2).as<int*>() = player2;
				}
				ImGui::InputInt("玩家3分红", &player3);
				ImGui::SameLine();
				if (ImGui::Button("修改")) {
					*script_global(1934631).at(3008).at(3).as<int*>() = player3;
				}
				ImGui::InputInt("玩家4分红", &player4);
				ImGui::SameLine();
				if (ImGui::Button("修改")) {
					*script_global(1934631).at(3008).at(4).as<int*>() = player4;
				}
				ImGui::TreePop();
			}
			if (ImGui::TreeNode("合约任务")) {
				ImGui::Combo("选择任务", &Contract_combo_pos, Contract_combo, sizeof(Contract_combo) / sizeof(*Contract_combo));
				ImGui::SameLine();
				if (ImGui::Button("跳过前置")) {
					g_fiber_pool->queue_job([]
					{
						switch (Contract_combo_pos)
						{
						case 0:
						{
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_FIXER_GENERAL_BS"), -1, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_FIXER_COMPLETED_BS"), -1, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_FIXER_STORY_BS"), 28, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_FIXER_STORY_STRAND"), -1, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_FIXER_STORY_COOLDOWN"), -1, 0);
							//
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_FIXER_GENERAL_BS"), -1, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_FIXER_COMPLETED_BS"), -1, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_FIXER_STORY_BS"), 28, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_FIXER_STORY_STRAND"), -1, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_FIXER_STORY_COOLDOWN"), -1, 0);
							features::notifyfmt("已跳过任务:~p~夜生活泄密");
							break;
						}
						case 1:
						{
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_FIXER_GENERAL_BS"), -1, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_FIXER_COMPLETED_BS"), -1, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_FIXER_STORY_BS"), 124, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_FIXER_STORY_STRAND"), -1, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_FIXER_STORY_COOLDOWN"), -1, 0);
							//
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_FIXER_GENERAL_BS"), -1, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_FIXER_COMPLETED_BS"), -1, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_FIXER_STORY_BS"), 124, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_FIXER_STORY_STRAND"), -1, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_FIXER_STORY_COOLDOWN"), -1, 0);
							features::notifyfmt("已跳过任务:~p~上流社会泄密");
							break;
						}
						case 2:
						{
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_FIXER_GENERAL_BS"), -1, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_FIXER_COMPLETED_BS"), -1, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_FIXER_STORY_BS"), 2044, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_FIXER_STORY_STRAND"), -1, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_FIXER_STORY_COOLDOWN"), -1, 0);
							//
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_FIXER_GENERAL_BS"), -1, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_FIXER_COMPLETED_BS"), -1, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_FIXER_STORY_BS"), 2044, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_FIXER_STORY_STRAND"), -1, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_FIXER_STORY_COOLDOWN"), -1, 0);
							features::notifyfmt("已跳过任务:~p~南中心泄密");
							break;
						}
						case 3:
						{
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_FIXER_GENERAL_BS"), -1, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_FIXER_COMPLETED_BS"), -1, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_FIXER_STORY_BS"), 4092, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_FIXER_STORY_STRAND"), -1, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_FIXER_STORY_COOLDOWN"), -1, 0);
							//
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_FIXER_GENERAL_BS"), -1, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_FIXER_COMPLETED_BS"), -1, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_FIXER_STORY_BS"), 4092, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_FIXER_STORY_STRAND"), -1, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_FIXER_STORY_COOLDOWN"), -1, 0);
							features::notifyfmt("已跳过任务:~p~分红关(档案任务)(xx博士)");
							break;
						}
						case 4:
						{
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_FIXER_GENERAL_BS"), -1, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_FIXER_COMPLETED_BS"), -1, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_FIXER_STORY_BS"), -1, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_FIXER_STORY_STRAND"), -1, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_FIXER_STORY_COOLDOWN"), -1, 0);
							//
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_FIXER_GENERAL_BS"), -1, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_FIXER_COMPLETED_BS"), -1, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_FIXER_STORY_BS"), -1, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_FIXER_STORY_STRAND"), -1, 0);
							STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_FIXER_STORY_COOLDOWN"), -1, 0);
							features::notifyfmt("已一键通关");
							break;
						}
						}
					});
				}
				if (ImGui::Button("重置安保合约冷却")) {
					*script_global(262145).at(31329).as<int*>() = 0;
				}
				ImGui::Separator();
				ImGui::InputInt("最终收入(任务开始后更改)(失败需重新设置)", &finalMoney);
				ImGui::SameLine();
				if (ImGui::Button("修改")) {
					*script_global(262145).at(31373).as<int*>() = finalMoney;
				}
				ImGui::Separator();
				if (ImGui::Button("传送到工厂约翰尼贡斯位置")) {
					g_fiber_pool->queue_job([]
					{
						ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 510.23, -667.92, 24.86, 1, 0, 0, 0);
						script::get_current()->yield();
					});
				}
				ImGui::SameLine();
				if (ImGui::Button("传送到机库约翰尼贡斯")) {
					g_fiber_pool->queue_job([]
					{
						ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), -935, -3018, 19, 1, 0, 0, 0);
						script::get_current()->yield();
					});
				}
				ImGui::TreePop();
			}
			ImGui::EndTabItem();
		}
	}
}