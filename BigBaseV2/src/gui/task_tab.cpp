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
	"����й¶",
	"����Σ��",
	"ĩ�ս���"
};
static const char* Contract_combo[]
{
	"ҹ����й��",
	"�������й��",
	"������й��",
	"�ֺ��(��������)(xx��ʿ)",
	"ͨ��"
};
static int Contract_combo_pos = 0;
static int endDay_combo_pos = 0;
int player1 = 100, player2 = 100, player3 = 100, player4 = 100;
int finalMoney = 1000000;
namespace big
{
	void all_tab::task_tab()
	{
		if (ImGui::BeginTabItem("����ѡ��"))
		{
			if (ImGui::TreeNode("����˵�")) {
				if (ImGui::Button("�������")) {
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
						features::notifyfmt("��ִ��");
					});
				}
				ImGui::SameLine();
				if (ImGui::Button("����ǰ��")) {
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
						features::notifyfmt("��ִ��");
					});
				}
				ImGui::Separator();
				ImGui::InputInt("���1�ֺ�", &player1);
				ImGui::SameLine();
				if(ImGui::Button("�޸�")) {
					*script_global(1973496).at(823).at(56).at(1).as<int*>() = player1;
				}
				ImGui::InputInt("���2�ֺ�", &player2);
				ImGui::SameLine();
				if (ImGui::Button("�޸�")) {
					*script_global(1973496).at(823).at(56).at(2).as<int*>() = player2;
				}
				ImGui::InputInt("���3�ֺ�", &player3);
				ImGui::SameLine();
				if (ImGui::Button("�޸�")) {
					*script_global(1973496).at(823).at(56).at(3).as<int*>() = player3;
				}
				ImGui::InputInt("���4�ֺ�", &player4);
				ImGui::SameLine();
				if (ImGui::Button("�޸�")) {
					*script_global(1973496).at(823).at(56).at(4).as<int*>() = player4;
				}
				ImGui::Separator();
				if (ImGui::Button("ɱ������")) {
					g_fiber_pool->queue_job([]
					{
						for (int i = 0; i < 4; i++) {
							if (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i)) && PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i) != PLAYER::PLAYER_ID()) {
								Vector3 Coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), 1);
								FIRE::ADD_EXPLOSION(Coords.x, Coords.y, Coords.z, 0, 1, 1, 0, 1, 0);
							}
						}
						features::notifyfmt("��ִ��");
					});
				}
				ImGui::SameLine();
				if (ImGui::Button("���͵���")) {
					g_fiber_pool->queue_job([]
					{
						ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 5006.70, -5755.89, 15.48, 1, 0, 0, 0);
						script::get_current()->yield();
					});
				}
				ImGui::SameLine();
				if (ImGui::Button("���ʹ���(���������)")) {
					g_fiber_pool->queue_job([]
					{
						ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 4990.74, -5717.96, 19.88, 1, 0, 0, 0);
						script::get_current()->yield();
					});
				}
				ImGui::SameLine();
				if (ImGui::Button("����")) {
					g_fiber_pool->queue_job([]
					{
						ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 4580, -6012, 3, 1, 0, 0, 0);
						script::get_current()->yield();
					});
				}
				ImGui::TreePop();
			}
			if (ImGui::TreeNode("�ĳ�����")) {
				if (ImGui::Button("����ǰ��(������ը����)")) {
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
						features::notifyfmt("��ִ��");
					});
				}
				ImGui::SameLine();
				if (ImGui::Button("���õ�һ���")) {
					g_fiber_pool->queue_job([]
					{
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_BITSET1"), 0, 0);
						//
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H3OPT_BITSET1"), 0, 0);
						features::notifyfmt("��ִ��");
					});
				}
				ImGui::SameLine();
				if (ImGui::Button("���õڶ����")) {
					g_fiber_pool->queue_job([]
					{
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_H3OPT_BITSET0"), 0, 0);
						//
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_H3OPT_BITSET0"), 0, 0);
						features::notifyfmt("��ִ��");
					});
				}
				ImGui::Separator();
				ImGui::InputInt("���1�ֺ�", &player1);
				ImGui::SameLine();
				if (ImGui::Button("�޸�")) {
					*script_global(1966718).at(1497).at(736).at(92).at(1).as<int*>() = player1;
				}
				ImGui::InputInt("���2�ֺ�", &player2);
				ImGui::SameLine();
				if (ImGui::Button("�޸�")) {
					*script_global(1966718).at(1497).at(736).at(92).at(2).as<int*>() = player2;
				}
				ImGui::InputInt("���3�ֺ�", &player3);
				ImGui::SameLine();
				if (ImGui::Button("�޸�")) {
					*script_global(1966718).at(1497).at(736).at(92).at(3).as<int*>() = player3;
				}
				ImGui::InputInt("���4�ֺ�", &player4);
				ImGui::SameLine();
				if (ImGui::Button("�޸�")) {
					*script_global(1966718).at(1497).at(736).at(92).at(4).as<int*>() = player4;
				}
				if (ImGui::Button("ɾ��NPC�ֺ�(������˹��)")) {
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
						features::notifyfmt("��ִ��");
					});
				}
				ImGui::Separator();
				if (ImGui::Button("�޸�����")) {
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
						features::notifyfmt("��ִ��");
					});
				}
				ImGui::TreePop();
			}
			if (ImGui::TreeNode("ĩ������")) {
				ImGui::Combo("ѡ��ǰ��", &endDay_combo_pos, endDay_combo, sizeof(endDay_combo) / sizeof(*endDay_combo));
				ImGui::SameLine();
				if (ImGui::Button("����ǰ��")) {
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
							features::notifyfmt("������ǰ��:~b~����й¶");
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
							features::notifyfmt("������ǰ��:~b~����Σ��");
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
							features::notifyfmt("������ǰ��:~b~ĩ�ս���");
							break;
						}
						}
					});
				}
				ImGui::Separator();
				ImGui::InputInt("���1�ֺ�", &player1);
				ImGui::SameLine();
				if (ImGui::Button("�޸�")) {
					*script_global(1962755).at(812).at(50).at(1).as<int*>() = player1;
				}
				ImGui::InputInt("���2�ֺ�", &player2);
				ImGui::SameLine();
				if (ImGui::Button("�޸�")) {
					*script_global(1962755).at(812).at(50).at(2).as<int*>() = player2;
				}
				ImGui::InputInt("���3�ֺ�", &player3);
				ImGui::SameLine();
				if (ImGui::Button("�޸�")) {
					*script_global(1962755).at(812).at(50).at(3).as<int*>() = player3;
				}
				ImGui::InputInt("���4�ֺ�", &player4);
				ImGui::SameLine();
				if (ImGui::Button("�޸�")) {
					*script_global(1962755).at(812).at(50).at(4).as<int*>() = player4;
				}
				ImGui::TreePop();
			}
			if (ImGui::TreeNode("Apartment����")) {
				if (ImGui::Button("����ǰ��(������ʹ��)")) {
					g_fiber_pool->queue_job([]
					{
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_HEIST_PLANNING_STAGE"), -1, 0);
						//
						STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_HEIST_PLANNING_STAGE"), -1, 0);
						features::notifyfmt("��ִ��");
					});
				}
				ImGui::Separator();
				ImGui::InputInt("���1�ֺ�", &player1);
				ImGui::SameLine();
				if (ImGui::Button("�޸�")) {
					*script_global(1934631).at(3008).at(1).as<int*>() = player1;
				}
				ImGui::InputInt("���2�ֺ�", &player2);
				ImGui::SameLine();
				if (ImGui::Button("�޸�")) {
					*script_global(1934631).at(3008).at(2).as<int*>() = player2;
				}
				ImGui::InputInt("���3�ֺ�", &player3);
				ImGui::SameLine();
				if (ImGui::Button("�޸�")) {
					*script_global(1934631).at(3008).at(3).as<int*>() = player3;
				}
				ImGui::InputInt("���4�ֺ�", &player4);
				ImGui::SameLine();
				if (ImGui::Button("�޸�")) {
					*script_global(1934631).at(3008).at(4).as<int*>() = player4;
				}
				ImGui::TreePop();
			}
			if (ImGui::TreeNode("��Լ����")) {
				ImGui::Combo("ѡ������", &Contract_combo_pos, Contract_combo, sizeof(Contract_combo) / sizeof(*Contract_combo));
				ImGui::SameLine();
				if (ImGui::Button("����ǰ��")) {
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
							features::notifyfmt("����������:~p~ҹ����й��");
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
							features::notifyfmt("����������:~p~�������й��");
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
							features::notifyfmt("����������:~p~������й��");
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
							features::notifyfmt("����������:~p~�ֺ��(��������)(xx��ʿ)");
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
							features::notifyfmt("��һ��ͨ��");
							break;
						}
						}
					});
				}
				if (ImGui::Button("���ð�����Լ��ȴ")) {
					*script_global(262145).at(31329).as<int*>() = 0;
				}
				ImGui::Separator();
				ImGui::InputInt("��������(����ʼ�����)(ʧ������������)", &finalMoney);
				ImGui::SameLine();
				if (ImGui::Button("�޸�")) {
					*script_global(262145).at(31373).as<int*>() = finalMoney;
				}
				ImGui::Separator();
				if (ImGui::Button("���͵�����Լ���ṱ˹λ��")) {
					g_fiber_pool->queue_job([]
					{
						ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 510.23, -667.92, 24.86, 1, 0, 0, 0);
						script::get_current()->yield();
					});
				}
				ImGui::SameLine();
				if (ImGui::Button("���͵�����Լ���ṱ˹")) {
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