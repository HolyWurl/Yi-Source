#pragma once
#include "common.hpp"

namespace big::features
{
	extern int menuOpened;
	extern int tpWayPoint;
	extern int tpObject;
	extern int goforward;

	/*Self*/
	extern bool godmode;
	void GodMode();

	/*Protections*/
	extern bool autoCrashggj;
	extern bool antiggj;
	extern bool antiIncreEvent;


	/*funtions*/
	void SpawnVehicle(char* vehname);
	void notifyfmt(char* fmt, ...);
	void GoForward();
	bool to_blip(int sprite, int color = -1);
	void run_tick();
	void script_func();
}
