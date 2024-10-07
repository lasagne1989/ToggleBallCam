#include "pch.h"
#include "ToggleBallCam.h"


BAKKESMOD_PLUGIN(ToggleBallCam, "Toggles you ball cam to the next all in training packs", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

void ToggleBallCam::onLoad()
{
	_globalCvarManager = cvarManager;	
	
	gameWrapper->HookEvent("Function TAGame.Ball_TA.Destroyed",
		[this](std::string eventName) {
			LOG("working");
			if (!gameWrapper->IsInFreeplay()) { return; }
			std::string camState;
			CameraWrapper cam = gameWrapper->GetCamera();
			if (!cam) { return; }
			camState = cam.GetCameraState();
			if (camState == "CameraState_BallCam_TA") {
				PlayerControllerWrapper input = gameWrapper->GetPlayerController();
				if (!input) { return; }
				input.PressSecondaryCamera();
				input.ReleaseSecondaryCamera();
				LOG("OFF");
				gameWrapper->SetTimeout([this](GameWrapper* gw) {
					PlayerControllerWrapper input = gameWrapper->GetPlayerController();
					if (!input) { return; }
					input.PressSecondaryCamera();
					input.ReleaseSecondaryCamera();
					LOG("on");
					}, 1.0f);
			}
					
			});
	
}
void ToggleBallCam::onUnload()
{

}