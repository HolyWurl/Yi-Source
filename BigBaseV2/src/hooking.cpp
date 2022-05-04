#include "common.hpp"
#include "function_types.hpp"
#include "logger.hpp"
#include "gta/array.hpp"
#include "gta/player.hpp"
#include "gta/script_thread.hpp"
#include "gui.hpp"
#include "hooking.hpp"
#include "memory/module.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "renderer.hpp"
#include "script_mgr.hpp"
#include "features.hpp"
#include "fiber_pool.hpp"

#include <MinHook.h>

namespace big
{
	static GtaThread *find_script_thread(rage::joaat_t hash)
	{
		for (auto thread : *g_pointers->m_script_threads)
		{
			if (thread
				&& thread->m_context.m_thread_id
				&& thread->m_handler
				&& thread->m_script_hash == hash)
			{
				return thread;
			}
		}

		return nullptr;
	}

	bool hooks::increment_stat_event(CNetworkIncrementStatEvent* net_event, CNetGamePlayer* sender, int64_t a3)
	{
		Player senderId = sender->m_player_id;
		Hash Stats = net_event->m_stat;
		if (features::antiIncreEvent)
		{
			if (Stats == rage::joaat("MPPLY_GAME_EXPLOITS")) {
				features::notifyfmt(u8"~r~Yi举报事件保护~s~~n~事件名称:~r~游戏漏洞利用~s~~n~发送者:~r~%s~", PLAYER::GET_PLAYER_NAME(senderId));
				return true;
			}
			else if (Stats == rage::joaat("MPPLY_VC_HATE")) {
				features::notifyfmt(u8"~r~Yi举报事件保护~s~~n~事件名称:~r~语音聊天(仇恨言论)~s~~n~发送者:~r~%s~", PLAYER::GET_PLAYER_NAME(senderId));
				return true;
			}
			else if (Stats == rage::joaat("MPPLY_VC_ANNOYINGME")) {
				features::notifyfmt(u8"~r~Yi举报事件保护~s~~n~事件名称:~r~语音聊天(骚扰)~s~~n~发送者:~r~%s~", PLAYER::GET_PLAYER_NAME(senderId));
				return true;
			}
			else if (Stats == rage::joaat("MPPLY_EXPLOITS")) {
				features::notifyfmt(u8"~r~Yi举报事件保护~s~~n~事件名称:~r~漏洞利用~s~~n~发送者:~r~%s~", PLAYER::GET_PLAYER_NAME(senderId));
				return true;
			}
			else if (Stats == rage::joaat("MPPLY_TC_ANNOYINGME")) {
				features::notifyfmt(u8"~r~Yi举报事件保护~s~~n~事件名称:~r~文字聊天(骚扰我)~s~~n~发送者:~r~%s~", PLAYER::GET_PLAYER_NAME(senderId));
				return true;
			}
			else if (Stats == rage::joaat("MPPLY_TC_HATE")) {
				features::notifyfmt(u8"~r~Yi举报事件保护~s~~n~事件名称:~r~文字聊天(仇恨言论)~s~~n~发送者:~r~%s~", PLAYER::GET_PLAYER_NAME(senderId));
				return true;
			}
			else if (Stats == rage::joaat("MPPLY_GRIEFING")) {
				features::notifyfmt(u8"~r~Yi举报事件保护~s~~n~事件名称:~r~恶意破坏~s~~n~发送者:~r~%s~", PLAYER::GET_PLAYER_NAME(senderId));
				return true;
			}
			else if (Stats == rage::joaat("MPPLY_OFFENSIVE_TAGPLATE")) {
				features::notifyfmt(u8"~r~Yi举报事件保护~s~~n~事件名称:~r~攻击性玩家~s~~n~发送者:~r~%s~", PLAYER::GET_PLAYER_NAME(senderId));
				return true;
			}
			else if (Stats == rage::joaat("MPPLY_OFFENSIVE_LANGUAGE")) {
				features::notifyfmt(u8"~r~Yi举报事件保护~s~~n~事件名称:~r~冒犯语言~s~~n~发送者:~r~%s~", PLAYER::GET_PLAYER_NAME(senderId));
				return true;
			}
			else if (Stats == rage::joaat("MPPLY_OFFENSIVE_UGC")) {
				features::notifyfmt(u8"~r~Yi举报事件保护~s~~n~事件名称:~r~具有攻击性的UGC~s~~n~发送者:~r~%s~", PLAYER::GET_PLAYER_NAME(senderId));
				return true;
			}
			else if (Stats == rage::joaat("MPPLY_BAD_CREW_NAME")) {
				features::notifyfmt(u8"~r~Yi举报事件保护~s~~n~事件名称:~r~不好的玩家名称~s~~n~发送者:~r~%s~", PLAYER::GET_PLAYER_NAME(senderId));
				return true;
			}
			else if (Stats == rage::joaat("MPPLY_BAD_CREW_MOTTO")) {
				features::notifyfmt(u8"~r~Yi举报事件保护~s~~n~事件名称:~r~不好的玩家签名~s~~n~发送者:~r~%s~", PLAYER::GET_PLAYER_NAME(senderId));
				return true;
			}
			else if (Stats == rage::joaat("MPPLY_BAD_CREW_STATUS")) {
				features::notifyfmt(u8"~r~Yi举报事件保护~s~~n~事件名称:~r~不好的玩家状态~s~~n~发送者:~r~%s~", PLAYER::GET_PLAYER_NAME(senderId));
				return true;
			}
			else if (Stats == rage::joaat("MPPLY_BAD_CREW_STATUS")) {
				features::notifyfmt(u8"~r~Yi举报事件保护~s~~n~事件名称:~r~不好的玩家标志~s~~n~发送者:~r~%s~", PLAYER::GET_PLAYER_NAME(senderId));
				return true;
			}
			else
			{
				return g_hooking->m_increment_stat_hook.get_original<decltype(&increment_stat_event)>()(net_event, sender, a3);
			}
		}
		else
		{
			return g_hooking->m_increment_stat_hook.get_original<decltype(&increment_stat_event)>()(net_event, sender, a3);
		}
	}

	bool IsGGJ(std::string message) {
		char* normal[] = { u8"群", u8"解锁", u8"辅助", u8"科技", u8"成人", u8"少妇", u8"淫", u8"少女" };
		for (int i = 0; i < 8; i++)
		{
			if (strstr(message.c_str(), normal[i]) == NULL) {
				continue;
			}
			else
			{
				return true;
			}
		}
		return false;
	}

	bool HK_RID_CRASH_FUNC(__int64 a1) {
		return false;
	}

	__int64 __cdecl hooks::ChatHook(__int64 a1, __int64 a2, __int64 a3, const char* origText, BOOL isTeam) {
		std::string Message(origText); 
		CNetGamePlayer* player = (CNetGamePlayer*)g_pointers->get_chat_player(a3, a2, a3);
		bool isggj = IsGGJ(Message);
		
		if (features::autoCrashggj) {
			if (isggj) {
				if (player->is_valid())
				{
					g_fiber_pool->queue_job([=]
					{
						int64_t tseargs[3] = { -1386010354, player->m_player_id, 1 };
						g_pointers->m_trigger_script_event(1, tseargs, 3, 1 << player->m_player_id);
						int64_t tseargs1[3] = { 962740265, player->m_player_id, 1 };
						g_pointers->m_trigger_script_event(1, tseargs1, 3, 1 << player->m_player_id);
						int64_t tseargs2[3] = { 603406648, player->m_player_id, 1 };
						g_pointers->m_trigger_script_event(1, tseargs2, 3, 1 << player->m_player_id);
						int64_t tseargs3[3] = { -1715193475, player->m_player_id, 1 };
						g_pointers->m_trigger_script_event(1, tseargs3, 3, 1 << player->m_player_id);
						int64_t tseargs4[3] = { 1258808115, player->m_player_id, 1 };
						g_pointers->m_trigger_script_event(1, tseargs4, 3, 1 << player->m_player_id);
						int64_t tseargs6[3] = { -1386010354, player->m_player_id, 1 };
						g_pointers->m_trigger_script_event(1, tseargs6, 3, 1 << player->m_player_id);
						int64_t tseargs23[10] = { -1386010354, player->m_player_id, 0,  1229879414 , 1742796505 , -1794944145 , -480124848 , 439776191 , -2062014584 , 2120444344 };
						g_pointers->m_trigger_script_event(1, tseargs23, 10, 1 << player->m_player_id);
						features::notifyfmt(u8"~r~Yi检测到广告机~s~~n~玩家:~b~%s~s~~n~措施:~r~崩溃", player->get_name());
					});
				}
				LOG(INFO) << "Yi检测到广告机玩家:" << player->get_name() << "措施:崩溃";
			}
		}
		
		if (features::antiggj) {
			if (isggj) {
				return 0;
			}
		}
		return g_hooking->m_get_chat_data_hook.get_original<decltype(&ChatHook)>()(a1, a2, a3, origText, isTeam);
	}

	hooking::hooking() :
		m_swapchain_hook(*g_pointers->m_swapchain, hooks::swapchain_num_funcs),
		m_set_cursor_pos_hook("SetCursorPos", memory::module("user32.dll").get_export("SetCursorPos").as<void*>(), &hooks::set_cursor_pos),
		m_run_script_threads_hook("Script hook", g_pointers->m_run_script_threads, &hooks::run_script_threads),
		
		m_convert_thread_to_fiber_hook("ConvertThreadToFiber", memory::module("kernel32.dll").get_export("ConvertThreadToFiber").as<void*>(), &hooks::convert_thread_to_fiber),
		
		m_rid_crash_hook("rid_crash_hook", g_pointers->m_Rid_Crash, &HK_RID_CRASH_FUNC),
		m_increment_stat_hook("CIncrementStatEvent", g_pointers->m_increment_stat_event, &hooks::increment_stat_event),
		m_get_chat_data_hook("get_chat_data", g_pointers->get_chat_data, &hooks::ChatHook)

	{
		m_swapchain_hook.hook(hooks::swapchain_present_index, &hooks::swapchain_present);
		m_swapchain_hook.hook(hooks::swapchain_resizebuffers_index, &hooks::swapchain_resizebuffers);

		g_hooking = this;
	}

	hooking::~hooking()
	{
		if (m_enabled)
			disable();

		g_hooking = nullptr;
	}

	void hooking::enable()
	{
		m_swapchain_hook.enable();
		m_og_wndproc = reinterpret_cast<WNDPROC>(SetWindowLongPtrW(g_pointers->m_hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&hooks::wndproc)));
		m_set_cursor_pos_hook.enable();
		m_rid_crash_hook.enable();
		m_increment_stat_hook.enable();
		m_get_chat_data_hook.enable();


		m_run_script_threads_hook.enable();
		m_convert_thread_to_fiber_hook.enable();

		m_enabled = true;
	}

	void hooking::disable()
	{
		m_enabled = false;
		m_convert_thread_to_fiber_hook.disable();
		m_run_script_threads_hook.disable();
		m_rid_crash_hook.disable();
		m_increment_stat_hook.disable();
		m_get_chat_data_hook.disable();

		m_set_cursor_pos_hook.disable();
		SetWindowLongPtrW(g_pointers->m_hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(m_og_wndproc));
		m_swapchain_hook.disable();
	}

	minhook_keepalive::minhook_keepalive()
	{
		MH_Initialize();
	}

	minhook_keepalive::~minhook_keepalive()
	{
		MH_Uninitialize();
	}

	bool hooks::run_script_threads(std::uint32_t ops_to_execute)
	{
		TRY_CLAUSE
		{
			if (g_running)
			{
				g_script_mgr.tick();
			}

			return g_hooking->m_run_script_threads_hook.get_original<functions::run_script_threads_t>()(ops_to_execute);
		} EXCEPT_CLAUSE
		return false;
	}

	void *hooks::convert_thread_to_fiber(void *param)
	{
		TRY_CLAUSE
		{
			if (IsThreadAFiber())
			{
				return GetCurrentFiber();
			}

			return g_hooking->m_convert_thread_to_fiber_hook.get_original<decltype(&convert_thread_to_fiber)>()(param);
		} EXCEPT_CLAUSE
		return nullptr;
	}

	HRESULT hooks::swapchain_present(IDXGISwapChain *this_, UINT sync_interval, UINT flags)
	{
		TRY_CLAUSE
		{
			if (g_running)
			{
				g_renderer->on_present();
			}

			return g_hooking->m_swapchain_hook.get_original<decltype(&swapchain_present)>(swapchain_present_index)(this_, sync_interval, flags);
		} EXCEPT_CLAUSE
		return NULL;
	}

	HRESULT hooks::swapchain_resizebuffers(IDXGISwapChain * this_, UINT buffer_count, UINT width, UINT height, DXGI_FORMAT new_format, UINT swapchain_flags)
	{
		TRY_CLAUSE
		{
			if (g_running)
			{
				g_renderer->pre_reset();

				auto result = g_hooking->m_swapchain_hook.get_original<decltype(&swapchain_resizebuffers)>(swapchain_resizebuffers_index)
					(this_, buffer_count, width, height, new_format, swapchain_flags);

				if (SUCCEEDED(result))
				{
					g_renderer->post_reset();
				}

				return result;
			}

			return g_hooking->m_swapchain_hook.get_original<decltype(&swapchain_resizebuffers)>(swapchain_resizebuffers_index)
				(this_, buffer_count, width, height, new_format, swapchain_flags);
		} EXCEPT_CLAUSE
		return NULL;
	}

	LRESULT hooks::wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		TRY_CLAUSE
		{
			if (g_running)
			{
				g_renderer->wndproc(hwnd, msg, wparam, lparam);
			}

			return CallWindowProcW(g_hooking->m_og_wndproc, hwnd, msg, wparam, lparam);
		} EXCEPT_CLAUSE
		return NULL;
	}

	BOOL hooks::set_cursor_pos(int x, int y)
	{
		TRY_CLAUSE
		{
			if (g_gui.m_opened)
				return true;

			return g_hooking->m_set_cursor_pos_hook.get_original<decltype(&set_cursor_pos)>()(x, y);
		} EXCEPT_CLAUSE
		return FALSE;
	}
}
