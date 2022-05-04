#pragma once
#include "common.hpp"
#include "gta/fwddec.hpp"
#include "gta/natives.hpp"

namespace big::functions
{
	using fpRidCrashFunc = bool(*)(__int64 a1);
	using trigger_script_event = void(int event_group, int64_t* args, int arg_count, int player_bits);
	typedef __int64(__cdecl* fpGetChatData)(__int64 a1, __int64 a2, __int64 a3, const char* origText, BOOL a5);
	typedef __int64(__cdecl* fpGetChatPlayer)(__int64 a1, __int64 a2, __int64 a3);
	using increment_stat_event = bool(uint64_t net_event_struct, int64_t sender, int64_t a3);
	using run_script_threads_t = bool(*)(std::uint32_t ops_to_execute);
	using get_native_handler_t = rage::scrNativeHandler(*)(rage::scrNativeRegistrationTable*, rage::scrNativeHash);
	using fix_vectors_t = void(*)(rage::scrNativeCallContext*);
}
