#include "common.hpp"
#include "features.hpp"
#include "fiber_pool.hpp"
#include "gui.hpp"
#include "logger.hpp"
#include "hooking.hpp"
#include "pointers.hpp"
#include "renderer.hpp"
#include "script_mgr.hpp"

BOOL APIENTRY DllMain(HMODULE hmod, DWORD reason, PVOID)
{
	using namespace big;
	if (reason == DLL_PROCESS_ATTACH)
	{

		DisableThreadLibraryCalls(hmod);

		g_hmodule = hmod;
		g_main_thread = CreateThread(nullptr, 0, [](PVOID) -> DWORD
		{
			while (!FindWindow(L"grcWindow", L"Grand Theft Auto V"))
				std::this_thread::sleep_for(1s);

			auto logger_instance = std::make_unique<logger>();
			try
			{
				LOG(RAW_GREEN_TO_CONSOLE) << u8R"kek(
　　　　　　　　　　　■■　
■■　　　　　　■■　■■　
　■■　　　　■■　　　　　
　■■　　　　■■　　　　　
　　■■　　■■　　　■■　
　　■■　　■■　　　■■　
　　　■■■■　　　　■■　
　　　■■■■　　　　■■　
　　　　■■　　　　　■■　
　　　　■■　　　　　■■　
　　　　■■　　　　　■■　
　　　　■■　　　　　■■　
　　　　■■　　　　　■■　)kek";
				auto pointers_instance = std::make_unique<pointers>();
				LOG(INFO) << "指针初始化";

				auto renderer_instance = std::make_unique<renderer>();
				LOG(INFO) << "渲染初始化";

				auto fiber_pool_instance = std::make_unique<fiber_pool>(10);
				LOG(INFO) << "纤程池初始化";

				auto hooking_instance = std::make_unique<hooking>();
				LOG(INFO) << "初始化钩子";

				//g_settings.load();
				//LOG(INFO) << "Settings Loaded.";

				g_script_mgr.add_script(std::make_unique<script>(&features::script_func));
				g_script_mgr.add_script(std::make_unique<script>(&gui::script_func));
				LOG(INFO) << "脚本已注册";

				g_hooking->enable();
				LOG(INFO) << "钩子已装载";
				LOG(INFO) << "免费辅助，付费购买恭喜被骗";
				while (g_running)
				{
					std::this_thread::sleep_for(500ms);
				}

				g_hooking->disable();
				LOG(INFO) << "卸载钩子";

				std::this_thread::sleep_for(1000ms);

				g_script_mgr.remove_all_scripts();
				LOG(INFO) << "卸载脚本";

				hooking_instance.reset();
				LOG(INFO) << "取消钩子初始化";

				fiber_pool_instance.reset();
				LOG(INFO) << "取消纤程初始化";

				renderer_instance.reset();
				LOG(INFO) << "取消渲染初始化";

				pointers_instance.reset();
				LOG(INFO) << "取消指针初始化";
			}
			catch (std::exception const &ex)
			{
				LOG(WARNING) << ex.what();
				MessageBoxA(nullptr, ex.what(), nullptr, MB_OK | MB_ICONEXCLAMATION);
			}

			LOG(INFO) << "Farewell!";
			logger_instance.reset();

			CloseHandle(g_main_thread);
			FreeLibraryAndExitThread(g_hmodule, 0);
		}, nullptr, 0, &g_main_thread_id);
	}

	return true;
}
