#include <HAPI_lib.h>
#include "WorldState.h"

#if defined(DEBUG) | defined(_DEBUG)
	#include<crtdbg.h>
	#define new new(_NORMAL_BLOCK,__FILE__,__LINE__)
#endif

void HAPI_Main(){

	WorldState world_state;

	if (!world_state.createWorld()){
		HAPI->UserMessage("World Creation Failed", "ERROR: ");
	}
	else{
		world_state.updateWorld();
	}

}
