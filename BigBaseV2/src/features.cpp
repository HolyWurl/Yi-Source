#include "common.hpp"
#include "fiber_pool.hpp"
#include "gta/player.hpp"
#include "gta_util.hpp"
#include "gui.hpp"
#include "logger.hpp"
#include "memory/module.hpp"
#include "memory/pattern.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "renderer.hpp"
#include "script.hpp"
#include "features.hpp"
#define IsKeyPressed(key) GetAsyncKeyState(key) & 0x8000
namespace big
{
	int pressDelay = 0;
	void features::run_tick()
	{
		QUEUE_JOB_BEGIN_CLAUSE()
		{
			if (IsKeyPressed(tpWayPoint) && GetTickCount64() - pressDelay > 200)
			{
				pressDelay = GetTickCount64();
				if (!features::to_blip((int)BlipIcons::Waypoint))
				{
					features::notifyfmt("无法找到导航点");
				}
			}
			if (IsKeyPressed(tpObject) && GetTickCount64() - pressDelay > 200)
			{
				pressDelay = GetTickCount64();
				static const int blips[] = { 1, 57, 128, 129, 130, 143, 144, 145, 146, 271, 286, 287, 288 };
				for (int i = 0; i < 13; i++) {
					if (features::to_blip(blips[i])) {
						break;
					}

				}
			}
			if (IsKeyPressed(goforward))
			{
				GoForward();
			}
			features::GodMode();
		}QUEUE_JOB_END_CLAUSE
	}

	int features::menuOpened = VK_INSERT;
	int features::tpWayPoint = VK_F4;
	int features::tpObject = VK_F3;
	int features::goforward = VK_F5;

	/*Self*/
	bool features::godmode = false;
	void features::GodMode() {
		ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), features::godmode);
	}

	/*Protection*/
	bool features::autoCrashggj = true;
	bool features::antiggj = false;
	bool features::antiIncreEvent = true;

	/*functions*/
	void features::SpawnVehicle(char* vehName) {
		auto hash = rage::joaat(vehName);
		while (!STREAMING::HAS_MODEL_LOADED(hash))
		{
			STREAMING::REQUEST_MODEL(hash);
			script::get_current()->yield();
		}
		auto pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
		*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
		Vehicle vehicle = VEHICLE::CREATE_VEHICLE(hash, pos.x, pos.y, pos.z, 0.f, TRUE, FALSE, FALSE);
		*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;
		script::get_current()->yield();
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
		if (*g_pointers->m_is_session_started)
		{
			DECORATOR::DECOR_SET_INT(vehicle, "MPBitset", 0);
			ENTITY::_SET_ENTITY_SOMETHING(vehicle, TRUE);
			auto networkId = NETWORK::VEH_TO_NET(vehicle);
			if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(vehicle))
				NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);
			VEHICLE::SET_VEHICLE_IS_STOLEN(vehicle, FALSE);
		}
	}
	void features::notifyfmt(char* fmt, ...)
	{
		char buf[2048] = { 0 };
		va_list va_alist;

		va_start(va_alist, fmt);
		vsprintf_s(buf, fmt, va_alist);
		va_end(va_alist);

		char buff2[2048] = { 0 };
		sprintf_s(buff2, "%s", buf);

		HUD::SET_TEXT_OUTLINE();
		HUD::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(buff2);
		HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER(false, false);
	}
	float degToRad(float degs)
	{
		return degs * 3.141592653589793f / 180.f;
	}
	void features::GoForward() {
		Entity e = PLAYER::PLAYER_PED_ID();
		if (PED::IS_PED_IN_ANY_VEHICLE(e, 0))
		{
			e = PED::GET_VEHICLE_PED_IS_USING(e);
		}
		Vector3 Coords = ENTITY::GET_ENTITY_COORDS(e, 1);
		float heading = ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID());
		float Xcoords = 1.5 * sin(degToRad(heading)) * -1.f;
		float Ycoords = 1.5 * cos(degToRad(heading));
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, Coords.x + Xcoords, Coords.y + Ycoords, Coords.z, 0, 0, 1);
		script::get_current()->yield();
	}
	bool get_blip_location(Vector3& location, int sprite, int color = -1)
	{
		Blip blip;
		for (blip = HUD::GET_FIRST_BLIP_INFO_ID(sprite);
			HUD::DOES_BLIP_EXIST(blip) &&
			color != -1 && HUD::GET_BLIP_COLOUR(blip);
			blip = HUD::GET_NEXT_BLIP_INFO_ID(sprite)
			) script::get_current()->yield();

		if (!HUD::DOES_BLIP_EXIST(blip) || (color != -1 && HUD::GET_BLIP_COLOUR(blip) != color)) return false;

		location = HUD::GET_BLIP_COORDS(blip);

		return true;
	}
	bool load_ground_at_3dcoord(Vector3& location)
	{
		float groundZ;
		const uint8_t attempts = 10;

		for (uint8_t i = 0; i < attempts; i++)
		{
			// Only request a collision after the first try failed because the location might already be loaded on first attempt.
			for (uint16_t z = 0; i && z < 1000; z += 100)
			{
				STREAMING::REQUEST_COLLISION_AT_COORD(location.x, location.y, (float)z);

				script::get_current()->yield();
			}

			if (MISC::GET_GROUND_Z_FOR_3D_COORD(location.x, location.y, 1000.f, &groundZ, false, false))
			{
				location.z = groundZ + 1.f;

				return true;
			}

			script::get_current()->yield();
		}

		location.z = 1000.f;

		return false;
	}
	bool features::to_blip(int sprite, int color)
	{
		Vector3 location;

		if (!get_blip_location(location, sprite, color))
			return false;

		load_ground_at_3dcoord(location);

		PED::SET_PED_COORDS_KEEP_VEHICLE(PLAYER::PLAYER_PED_ID(), location.x, location.y, location.z);

		return true;
	}

	void features::script_func()
	{
		while (true)
		{
			TRY_CLAUSE
			{
				run_tick();
			}
			EXCEPT_CLAUSE
			script::get_current()->yield();
		}
	}
}
