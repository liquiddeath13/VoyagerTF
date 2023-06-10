// Source made by Create#5488
// Release Date: 02.02.2023 
// Updated to Latest Patch
// If you need help dm me -> Create#5488
#include "MainIncludes.h"
#include <tchar.h>
#include "lazyimp.hpp"
#include "memory1.h"
inline uintptr_t player_controller;

void DrawESP();

DWORD espthread(LPVOID IN) {
	while (true) {
			DrawESP();
	}
}


void sss()
{
	while (true)
	{
		XorS(call, "FortniteClient-Win64-Shipping.exe");
		DWORD pid = Memory.GamePID;
		if (!pid == NULL)
		{
			return;
		}
	}
}

int main()
{
	Memory.Initialize();
	SetConsoleTitleA("VoyagerTF");

	std::cout << skCrypt("\n");

	Log3(skCrypt("[ VoyagerTF ] Waiting for Fortnite..."));
	sss();
	MessageBox(NULL, skCrypt(L"Click OK In Lobby"), skCrypt(L"Information"), NULL);
	hwnd = FindWindowA(0, "Fortnite  ");
	std::cout << skCrypt("\n");

	Log3(skCrypt(" "));
	Beep(350, 300);
	GetWindowThreadProcessId(hwnd, &processID);
	Sleep(200);
	if (!Memory.Initialize()) {
		std::cout << "[ VoyagerTF ] HyperVisor is NOT Initialized.";
	}
	Log3(skCrypt(" "));
	printf("[ VoyagerTF ] Fortnites Id Base Is: %p", Memory.BaseAddress);
	std::cout << '\n';

	std::cout << "Process Base: " << Memory.BaseAddress << "\n";
	std::cout << "Window HWND: " << Memory.Window << "\n";
	std::cout << "Process ID: " << Memory.GamePID << "\n";
	std::cout << "HyperV: " << Memory._HyperV << "\n";
	Sleep(1500);
	xCreateWindow();
	xInitD3d();
	xMainLoop();
	HANDLE handle = CreateThread_Esp(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(espthread), nullptr, NULL, nullptr);
	xShutdown();
}

bool isVisible(uint64_t Mesh)
{
	auto fLastSubmitTime = Memory.Read<float>(Mesh + 0x360);
	auto fLastRenderTimeOnScreen = Memory.Read<float>(Mesh + 0x368);
	const float fVisionTick = 0.15f;
	return fLastRenderTimeOnScreen + fVisionTick >= fLastSubmitTime;
}

void AimAt(DWORD_PTR entity)
{
	uint64_t currentactormesh = Memory.Read<uint64_t>(entity + OFFSETS::Mesh);
	auto rootHead = GetBoneWithRotation(currentactormesh, def::hitbox);
	Vector3 rootHeadOut = ProjectWorldToScreen(rootHead);
	if (rootHeadOut.y != 0 || rootHeadOut.y != 0)
	{
		aimbot(rootHeadOut.x, rootHeadOut.y);
	}
}

ImU32 RGBtoU32(int r, int g, int b)
{
	float fr = (float)r / 255.0;
	float fg = (float)g / 255.0;
	float fb = (float)b / 255.0;
	return ImGui::GetColorU32(ImVec4(fr, fg, fb, 1));
}
DWORD_PTR CurrentActorMesh;

void DrawESP() {

	if (drawbase)
	{
		ImGui::GetBackgroundDrawList()->AddText(ImVec2(35, 25), RGBtoU32(255, 255, 255), skCrypt("blyscyk#9849"));
	}
	if (crosshair)
	{
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Width / 2, Height / 2), ImVec2(Width / 2 - CrosshairSize, Height / 2), RGBtoU32(255, 255, 255));
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Width / 2, Height / 2), ImVec2(Width / 2 + CrosshairSize, Height / 2), RGBtoU32(255, 255, 255));
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Width / 2, Height / 2), ImVec2(Width / 2, Height / 2 - CrosshairSize), RGBtoU32(255, 255, 255));
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Width / 2, Height / 2), ImVec2(Width / 2, Height / 2 + CrosshairSize), RGBtoU32(255, 255, 255));
	}
	if (circletype == true)
	{
		if (square_fov) {
			ImGui::GetBackgroundDrawList()->AddRect(ImVec2(ScreenCenterX - def::AimbotFov, ScreenCenterY - def::AimbotFov), ImVec2(ScreenCenterX + def::AimbotFov, ScreenCenterY + def::AimbotFov), RGBtoU32(255, 255, 255), 0.5f);
			bool fovcircle = false;
			bool  fovcirclefilled = false;
		}
		if (fovcircle) {
			ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(ScreenCenterX, ScreenCenterY), float(def::AimbotFov), RGBtoU32(255, 255, 255), 100.0f, 0.5f);
			bool square_fov = false;
			bool fovcircle = false;
			bool  fovcirclefilled = false;
		}
		if (fovcirclefilled) {
			ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(ScreenCenterX, ScreenCenterY), float(def::AimbotFov), ImColor(0, 0, 0, 160), 220.0f);
			ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(ScreenCenterX, ScreenCenterY), float(def::AimbotFov), RGBtoU32(255, 80, 80), 220.0f, 0.5f);
			bool square_fov = false;
			bool fovcircle = false;
		}
		if (SquareFovFilled)
		{
			ImGui::GetBackgroundDrawList()->AddRect(ImVec2(ScreenCenterX - def::AimbotFov, ScreenCenterY - def::AimbotFov), ImVec2(ScreenCenterX + def::AimbotFov, ScreenCenterY + def::AimbotFov), RGBtoU32(255, 80, 80), 0.5f);
			ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(ScreenCenterX - def::AimbotFov, ScreenCenterY - def::AimbotFov), ImVec2(ScreenCenterX + def::AimbotFov, ScreenCenterY + def::AimbotFov), ImColor(0, 0, 0, 160), 1.0f), 0.5f;
		}
	}

	HitBoxAimKey();

	float closestDistance = FLT_MAX;
	DWORD_PTR closestPawn = NULL;

	Uworld = Memory.Read<DWORD_PTR>(Memory.BaseAddress + GWorld);



	DWORD_PTR Gameinstance = Memory.Read<DWORD_PTR>(Uworld + OFFSETS::Gameinstance);


	DWORD_PTR LocalPlayers = Memory.Read<DWORD_PTR>(Gameinstance + OFFSETS::LocalPlayers);


	Localplayer = Memory.Read<DWORD_PTR>(LocalPlayers);


	PlayerController = Memory.Read<DWORD_PTR>(Localplayer + OFFSETS::PlayerController);


	LocalPawn = Memory.Read<DWORD_PTR>(PlayerController + OFFSETS::LocalPawn);


	PlayerState = Memory.Read<DWORD_PTR>(LocalPawn + OFFSETS::PlayerState);

	Rootcomp = Memory.Read<DWORD_PTR>(LocalPawn + OFFSETS::RootComponet);

	DWORD_PTR GameState = Memory.Read<DWORD_PTR>(Uworld + OFFSETS::GameState);

	DWORD_PTR PlayerArray = Memory.Read<DWORD_PTR>(GameState + OFFSETS::PlayerArray);


	for (unsigned long i = 0; i < 100; ++i)
	{
		const auto& player = Memory.Read<uintptr_t>(PlayerArray + i * 0x8);
		const auto& CurrentActor = Memory.Read<uintptr_t>(player + OFFSETS::CurrentActor);
		const uint64_t CurrentActorMesh = Memory.Read<uint64_t>(CurrentActor + OFFSETS::Mesh);
		const int MyTeamId = Memory.Read<int>(PlayerState + OFFSETS::TeamId);
		const DWORD64 otherPlayerState = Memory.Read<uint64_t>(CurrentActor + 0x290);
		const int ActorTeamId = Memory.Read<int>(otherPlayerState + OFFSETS::TeamId);

		// -- ReloadCheck --
		const uintptr_t CurrentWeapon = Memory.Read<uintptr_t>(CurrentActor + 0x908);
		const auto bIsReloadingWeapon = Memory.Read<bool>(CurrentWeapon + 0x348);
		// -------------------------------------------

		// -- Targeting Check --
		const auto bIsTargeting = Memory.Read<bool>(CurrentWeapon + 0xB05);
		// -------------------------------------------

		if (SelfEsp) {
		}
		else { if (CurrentActor == LocalPawn) continue; }
	


		// --- Vector3 ---
		Vector3 Headpos = GetBoneWithRotation(CurrentActorMesh, 68);
		Vector3 bone66 = GetBoneWithRotation(CurrentActorMesh, 66);
		Vector3 top = ProjectWorldToScreen(bone66);
		Vector3 bone0 = GetBoneWithRotation(CurrentActorMesh, 0);
		Vector3 bottom = ProjectWorldToScreen(bone0);
		Vector3 Headbox = ProjectWorldToScreen(Vector3(Headpos.x, Headpos.y, Headpos.z + 15));
		Vector3 w2shead = ProjectWorldToScreen(Headpos);
		Vector3 vHeadBone = GetBoneWithRotation(CurrentActorMesh, 68);
		Vector3 vRootBone = GetBoneWithRotation(CurrentActorMesh, 0);
		Vector3 vHeadBoneOut = ProjectWorldToScreen(Vector3(vHeadBone.x, vHeadBone.y, vHeadBone.z + 15));
		localactorpos = Memory.Read<Vector3>(Rootcomp + 0x128);

		// --- Float's ---
		float distance = localactorpos.Distance(Headpos) / ChangerFOV;
		float CornerHeight = abs(Headbox.y - bottom.y);
		float CornerWidth = CornerHeight * BoxWidthValue;

		if (distance < def::VisDist)
		{

			if (AimWhileJumping) { //Allows you to ADS when You are in the Air
				Memory.Write<bool>(LocalPawn + 0x4DD6, true);
			}

			if (carFly)
			{
				if (LocalPawn)
				{
					struct {
						float ProjectionMatrix[4][4];
					} view = { 0 };
					uint64_t VEHICLE_STATS = Memory.Read<uint64_t>(LocalPawn + 0x2428);
					if (GetAsyncKeyState(VK_SPACE))Memory.Write<char>(VEHICLE_STATS + 0x6DA, 1);
				}

			}


			if (DoublePump) {
				if (CurrentWeapon)
				{
					Memory.Write<bool>(CurrentWeapon + 0x1061, true); // bIgnoreTryToFireSlotCooldownRestriction
				}
			}

			if (PlayerFly)
			{
				Memory.Write<float>(LocalPawn + 0x223c, 10.f); // ZiplineSpeedFactor
				Memory.Write<bool>(LocalPawn + 0x2140 + 0x18, true); // ZiplineState
			}

			if (Spinbot)
			{
				uintptr_t Mesh = Memory.Read<uintptr_t>((uintptr_t)LocalPawn + 0x310);

				if (Spinbot)
				{
					Memory.Write<Vector3>(Mesh + 0x140, Vector3(0, -rand() % (int)360, 0));
				}
				else
				{
					Memory.Write<Vector3>(Mesh + 0x140, Vector3(0, -90, 0));
				}
			}
			

			if (bullettp)
			{

			}

			if (NoBloom) {
				uintptr_t CurrentWeapon = Memory.Read<uintptr_t>((uintptr_t)LocalPawn + 0x908);
				if (GetAsyncKeyState(VK_LBUTTON))
				{
					Memory.Write<float>((uintptr_t)CurrentWeapon + 0x64, 30);
				}
				else
				{
					Memory.Write<float>((uintptr_t)CurrentWeapon + 0x64, 1);
				}
			}

			if (InfiniteFuel)
			{
				uint64_t VEHICLE_STATS = Memory.Read<uint64_t>(LocalPawn + 0x2428);
				if (VEHICLE_STATS)
				{
					auto FuelComponent = Memory.Read<uintptr_t>((uintptr_t)VEHICLE_STATS + 0x10F0); //FortAthenaVehicle::CachedFuelComponent 0x10A0
					Memory.Write<float>(FuelComponent + 0xf0, 20000.f);
				}
			}


			if (AirStuck) {
				Memory.Write<float>((uintptr_t)LocalPawn + 0x64, 0); //CustomTimeDilation Offset
			}
			else {
				Memory.Write<float>((uintptr_t)LocalPawn + 0x64, 1); //CustomTimeDilation Offset

			}

			if (WindowStreamProof) {
				SetWindowDisplayAffinity(Window, WDA_EXCLUDEFROMCAPTURE);
			}
			if (!WindowStreamProof) {
				SetWindowDisplayAffinity(Window, !WDA_EXCLUDEFROMCAPTURE);
			}
			if (fillbox)
			{
				DrawFilledRect(Headbox.x - (CornerWidth / 2), Headbox.y, CornerWidth, CornerHeight, ImColor(0, 0, 0, 125));
			}
			if (CornerBoxEsp)
			{
				if (isVisible(CurrentActorMesh))
				{
					DrawCorneredBox(Headbox.x - (CornerWidth / 2), Headbox.y, CornerWidth, CornerHeight, RGBtoU32(255, 255, 255), Boxthinkness);
				}
				else
				{
					DrawCorneredBox(Headbox.x - (CornerWidth / 2), Headbox.y, CornerWidth, CornerHeight, RGBtoU32(255, 0, 0), Boxthinkness);
				}
			}
			if (BoxEsp)
			{
				if (isVisible(CurrentActorMesh))
				{
					DrawBox(Headbox.x - (CornerWidth / 2), Headbox.y, CornerWidth, CornerHeight, RGBtoU32(255, 255, 255), Boxthinkness);
				}
				else
				{
					DrawBox(Headbox.x - (CornerWidth / 2), Headbox.y, CornerWidth, CornerHeight, RGBtoU32(255, 0, 0), Boxthinkness);
				}
			}
			if (Skeleton)
			{
				Vector3 vHeadBone = GetBoneWithRotation(CurrentActorMesh, 68);
				Vector3 vHip = GetBoneWithRotation(CurrentActorMesh, 2);
				Vector3 vNeck = GetBoneWithRotation(CurrentActorMesh, 67);
				Vector3 vUpperArmLeft = GetBoneWithRotation(CurrentActorMesh, 9);
				Vector3 vUpperArmRight = GetBoneWithRotation(CurrentActorMesh, 38);
				Vector3 vLeftHand = GetBoneWithRotation(CurrentActorMesh, 10);
				Vector3 vRightHand = GetBoneWithRotation(CurrentActorMesh, 39);
				Vector3 vLeftHand1 = GetBoneWithRotation(CurrentActorMesh, 30);
				Vector3 vRightHand1 = GetBoneWithRotation(CurrentActorMesh, 59);
				Vector3 vRightThigh = GetBoneWithRotation(CurrentActorMesh, 78);
				Vector3 vLeftThigh = GetBoneWithRotation(CurrentActorMesh, 71);
				Vector3 vRightCalf = GetBoneWithRotation(CurrentActorMesh, 79);
				Vector3 vLeftCalf = GetBoneWithRotation(CurrentActorMesh, 72);
				Vector3 vLeftFoot = GetBoneWithRotation(CurrentActorMesh, 73);
				Vector3 vRightFoot = GetBoneWithRotation(CurrentActorMesh, 80);
				Vector3 vPelvisOut = GetBoneWithRotation(CurrentActorMesh, 8);
				Vector3 vHeadBoneOut = ProjectWorldToScreen(vHeadBone);
				Vector3 vPelvis = ProjectWorldToScreen(vPelvisOut);
				Vector3 vHipOut = ProjectWorldToScreen(vHip);
				Vector3 vNeckOut = ProjectWorldToScreen(vNeck);
				Vector3 vUpperArmLeftOut = ProjectWorldToScreen(vUpperArmLeft);
				Vector3 vUpperArmRightOut = ProjectWorldToScreen(vUpperArmRight);
				Vector3 vLeftHandOut = ProjectWorldToScreen(vLeftHand);
				Vector3 vRightHandOut = ProjectWorldToScreen(vRightHand);
				Vector3 vLeftHandOut1 = ProjectWorldToScreen(vLeftHand1);
				Vector3 vRightHandOut1 = ProjectWorldToScreen(vRightHand1);
				Vector3 vRightThighOut = ProjectWorldToScreen(vRightThigh);
				Vector3 vLeftThighOut = ProjectWorldToScreen(vLeftThigh);
				Vector3 vRightCalfOut = ProjectWorldToScreen(vRightCalf);
				Vector3 vLeftCalfOut = ProjectWorldToScreen(vLeftCalf);
				Vector3 vLeftFootOut = ProjectWorldToScreen(vLeftFoot);
				Vector3 vRightFootOut = ProjectWorldToScreen(vRightFoot);
				DrawLine(vHeadBoneOut.x, vHeadBoneOut.y, vNeckOut.x, vNeckOut.y, &Col.white, 0.6f);
				DrawLine(vHipOut.x, vHipOut.y, vNeckOut.x, vNeckOut.y, &Col.white, 0.6f);
				DrawLine(vUpperArmLeftOut.x, vUpperArmLeftOut.y, vNeckOut.x, vNeckOut.y, &Col.white, 0.6f);
				DrawLine(vUpperArmRightOut.x, vUpperArmRightOut.y, vNeckOut.x, vNeckOut.y, &Col.white, 0.6f);
				DrawLine(vLeftHandOut.x, vLeftHandOut.y, vUpperArmLeftOut.x, vUpperArmLeftOut.y, &Col.white, 0.6f);
				DrawLine(vRightHandOut.x, vRightHandOut.y, vUpperArmRightOut.x, vUpperArmRightOut.y, &Col.white, 0.6f);
				DrawLine(vLeftHandOut.x, vLeftHandOut.y, vLeftHandOut1.x, vLeftHandOut1.y, &Col.white, 0.6f);
				DrawLine(vRightHandOut.x, vRightHandOut.y, vRightHandOut1.x, vRightHandOut1.y, &Col.white, 0.6f);
				DrawLine(vLeftThighOut.x, vLeftThighOut.y, vHipOut.x, vHipOut.y, &Col.white, 0.6f);
				DrawLine(vRightThighOut.x, vRightThighOut.y, vHipOut.x, vHipOut.y, &Col.white, 0.6f);
				DrawLine(vLeftCalfOut.x, vLeftCalfOut.y, vLeftThighOut.x, vLeftThighOut.y, &Col.white, 0.6f);
				DrawLine(vRightCalfOut.x, vRightCalfOut.y, vRightThighOut.x, vRightThighOut.y, &Col.white, 0.6f);
				DrawLine(vLeftFootOut.x, vLeftFootOut.y, vLeftCalfOut.x, vLeftCalfOut.y, &Col.white, 0.6f);
				DrawLine(vRightFootOut.x, vRightFootOut.y, vRightCalfOut.x, vRightCalfOut.y, &Col.white, 0.6f);
			}
			if (Snaplines)
			{
				if (isVisible(CurrentActorMesh))
				{
					DrawLine(Width / 2 - 0, Height / 2 - 540, bottom.x, bottom.y, &Col.white, 0.5);
				}
				else
				{
					DrawLine(Width / 2 - 0, Height / 2 - 540, bottom.x, bottom.y, &Col.red, 0.5);
				}
			}

			if (DynamicEsp)
			{
				Vector3 bottom1 = ProjectWorldToScreen(Vector3(vRootBone.x + 40, vRootBone.y - 1, vRootBone.z));
				Vector3 bottom2 = ProjectWorldToScreen(Vector3(vRootBone.x - 40, vRootBone.y - 1, vRootBone.z));
				Vector3 bottom3 = ProjectWorldToScreen(Vector3(vRootBone.x - 40, vRootBone.y - 1, vRootBone.z));
				Vector3 bottom4 = ProjectWorldToScreen(Vector3(vRootBone.x + 40, vRootBone.y - 1, vRootBone.z));
				Vector3 top1 = ProjectWorldToScreen(Vector3(vHeadBone.x + 40, vHeadBone.y, vHeadBone.z + 15));
				Vector3 top2 = ProjectWorldToScreen(Vector3(vHeadBone.x - 40, vHeadBone.y, vHeadBone.z + 15));
				ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom1.x, bottom1.y), ImVec2(top1.x, top1.y), ImColor(0, 0, 0, 255), 3.1f);
				ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom2.x, bottom2.y), ImVec2(top2.x, top2.y), ImColor(0, 0, 0, 255), 3.1f);
				ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom1.x, bottom1.y), ImVec2(bottom2.x, bottom2.y), ImColor(0, 0, 0, 255), 3.1f);
				ImGui::GetBackgroundDrawList()->AddLine(ImVec2(top1.x, top1.y), ImVec2(top2.x, top2.y), ImColor(0, 0, 0, 255), 3.1f);
				ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom1.x, bottom1.y), ImVec2(top1.x, top1.y), ImColor(255, 255, 255, 255), 0.1f);
				ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom2.x, bottom2.y), ImVec2(top2.x, top2.y), ImColor(255, 255, 255, 255), 0.1f);
				ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom1.x, bottom1.y), ImVec2(bottom2.x, bottom2.y), ImColor(255, 255, 255, 255), 0.1f);
				ImGui::GetBackgroundDrawList()->AddLine(ImVec2(top1.x, top1.y), ImVec2(top2.x, top2.y), ImColor(255, 255, 255, 255), 0.1f);
			}
			if (PlayerDistanceEsp)
			{
				char name[64];
				sprintf_s(name, skCrypt("[%2.fm]"), distance);
				DrawString(16, Headbox.x, Headbox.y - 15, &Col.white, true, true, name);
			}
			if (reloadcheck)
			{
				if (bIsReloadingWeapon)
					ImGui::GetBackgroundDrawList()->AddText(ImVec2(Headbox.x, Headbox.y + 30), IM_COL32(255, 0, 0, 0), "RELOADING");
				else
					ImGui::GetBackgroundDrawList()->AddText(ImVec2(Headbox.x, Headbox.y + 30), IM_COL32(255, 255, 255, 255), "NOT RELOADING");
			}
			if (targetingcheck)
			{
				if (bIsReloadingWeapon)
					ImGui::GetBackgroundDrawList()->AddText(ImVec2(top.x, top.y + 30), IM_COL32(255, 0, 0, 0), "Player is Targeting");
				else
					ImGui::GetBackgroundDrawList()->AddText(ImVec2(top.x, top.y + 30), IM_COL32(255, 255, 255, 255), "Player is Not Targeting");
			}
			if (ThreeDBoxEsp)
			{
				if (vHeadBoneOut.x != 0 || vHeadBoneOut.y != 0 || vHeadBoneOut.z != 0)
				{
					ImU32 ESPSkeleton;
					if (isVisible(CurrentActorMesh))
					{
						ESPSkeleton = RGBtoU32(255, 255, 255);
					}
					else if (!isVisible(CurrentActorMesh))
					{
						ESPSkeleton = RGBtoU32(255, 0, 0);
					}
					Vector3 bottom1 = ProjectWorldToScreen(Vector3(vRootBone.x + 40, vRootBone.y - 40, vRootBone.z));
					Vector3 bottom2 = ProjectWorldToScreen(Vector3(vRootBone.x - 40, vRootBone.y - 40, vRootBone.z));
					Vector3 bottom3 = ProjectWorldToScreen(Vector3(vRootBone.x - 40, vRootBone.y + 40, vRootBone.z));
					Vector3 bottom4 = ProjectWorldToScreen(Vector3(vRootBone.x + 40, vRootBone.y + 40, vRootBone.z));
					Vector3 top1 = ProjectWorldToScreen(Vector3(vHeadBone.x + 40, vHeadBone.y - 40, vHeadBone.z + 15));
					Vector3 top2 = ProjectWorldToScreen(Vector3(vHeadBone.x - 40, vHeadBone.y - 40, vHeadBone.z + 15));
					Vector3 top3 = ProjectWorldToScreen(Vector3(vHeadBone.x - 40, vHeadBone.y + 40, vHeadBone.z + 15));
					Vector3 top4 = ProjectWorldToScreen(Vector3(vHeadBone.x + 40, vHeadBone.y + 40, vHeadBone.z + 15));
					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom1.x, bottom1.y), ImVec2(top1.x, top1.y), ESPSkeleton, 0.1f);
					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom2.x, bottom2.y), ImVec2(top2.x, top2.y), ESPSkeleton, 0.1f);
					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom3.x, bottom3.y), ImVec2(top3.x, top3.y), ESPSkeleton, 0.1f);
					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom4.x, bottom4.y), ImVec2(top4.x, top4.y), ESPSkeleton, 0.1f);
					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom1.x, bottom1.y), ImVec2(bottom2.x, bottom2.y), ESPSkeleton, 0.1f);
					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom2.x, bottom2.y), ImVec2(bottom3.x, bottom3.y), ESPSkeleton, 0.1f);
					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom3.x, bottom3.y), ImVec2(bottom4.x, bottom4.y), ESPSkeleton, 0.1f);
					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom4.x, bottom4.y), ImVec2(bottom1.x, bottom1.y), ESPSkeleton, 0.1f);
					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(top1.x, top1.y), ImVec2(top2.x, top2.y), ESPSkeleton, 0.1f);
					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(top2.x, top2.y), ImVec2(top3.x, top3.y), ESPSkeleton, 0.1f);
					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(top3.x, top3.y), ImVec2(top4.x, top4.y), ESPSkeleton, 0.1f);
					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(top4.x, top4.y), ImVec2(top1.x, top1.y), ESPSkeleton, 0.1f);
				}
			}
		}
		auto dx = w2shead.x - (Width / 2);
		auto dy = w2shead.y - (Height / 2);
		auto dist = sqrtf(dx * dx + dy * dy);
		if (isVisible(CurrentActorMesh)) {

			if (dist < def::AimbotFov && dist < closestDistance) {
				closestDistance = dist;
				closestPawn = CurrentActor;
			}

		}
	}
	if (norecoil)
	{
	}
	DWORD_PTR LOL;
	if (def::Aimbot)
	{
		if (def::Aimbot && closestPawn && GetAsyncKeyState(hotkeys::aimkey) < 0) {
			AimAt(closestPawn);
		}
	}
}



void render() {
	switch (keybind)
	{
	case 0:
		def::aimkeypos = 1;
		break;
	case 1:
		def::aimkeypos = 0;
		break;
	case 2:
		def::aimkeypos = 2;
		break;
	}
	if (RenderOption == 0)
	{
		fovcirclefilled = false;
		square_fov = false;
		fovcircle = true;
		SquareFovFilled = false;
	}
	if (RenderOption == 1)
	{
		fovcircle = false;
		fovcirclefilled = false;
		square_fov = true;
		SquareFovFilled = false;
	}
	if (RenderOption == 2)
	{
		square_fov = false;
		fovcircle = false;
		fovcirclefilled = true;
		SquareFovFilled = false;
	}
	if (RenderOption == 3)
	{
		square_fov = false;
		fovcircle = false;
		fovcirclefilled = false;
		SquareFovFilled = true;
	}
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	DrawESP();
	if (GetAsyncKeyState(VK_F2) & 1) {  // 0x2D = Insert
		ShowMenu = !ShowMenu;
	}
	if (ShowMenu)
	{
		ImVec4* colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
		colors[ImGuiCol_Border] = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
		colors[ImGuiCol_CheckMark] = ImVec4(0.83f, 0.37f, 0.26f, 3.00f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
		colors[ImGuiCol_Button] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
		colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
		colors[ImGuiCol_Separator] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
		colors[ImGuiCol_Tab] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
		colors[ImGuiCol_TabHovered] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
		colors[ImGuiCol_TabUnfocused] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_TableHeaderBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
		colors[ImGuiCol_TableBorderStrong] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
		colors[ImGuiCol_TableBorderLight] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
		colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
		colors[ImGuiCol_NavHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.20f);
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.35f);
		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowRounding = 7;
		style.ChildRounding = 4;
		style.FrameRounding = 3;
		style.PopupRounding = 4;
		ImGui::SetNextWindowSize(ImVec2(530.000f, 440.000f), ImGuiCond_Once);

		ImGui::Begin("VoyagerTF | By ! blyscyk#9849", NULL, 0);

		ImDrawList* pDrawList;
		const auto& CurrentWindowPos = ImGui::GetWindowPos();
		const auto& pWindowDrawList = ImGui::GetWindowDrawList();
		const auto& pBackgroundDrawList = ImGui::GetBackgroundDrawList();
		const auto& pForegroundDrawList = ImGui::GetForegroundDrawList();



		ImGui::SetCursorPos(ImVec2(8.000f, 25.000f));
		if (ImGui::Button(skCrypt("Aim"), ImVec2(120.000f, 60.000f)))
		{
			tab = 1;
		}

		ImGui::SetCursorPos(ImVec2(8.000f, 100.000f));
		if (ImGui::Button(skCrypt("Visuals"), ImVec2(120.000f, 60.000f)))
		{
			tab = 2;
		}

		ImGui::SetCursorPos(ImVec2(8.000f, 175.000f));
		if (ImGui::Button(skCrypt("Exploits"), ImVec2(120.000f, 60.000f)))
		{
			tab = 3;
		}
		switch (tab)
		{
		case 1:


			ImGui::SetCursorPos(ImVec2(143.000f, 27.000f));
			ImGui::Checkbox("Aimbot", &def::Aimbot);


			ImGui::SetCursorPos(ImVec2(143.000f, 50.000f));
			ImGui::Checkbox(skCrypt("FOV Circle"), &circletype);

			ImGui::SetNextItemWidth(250.000f);
			ImGui::SetCursorPos(ImVec2(143.000f, 73.000f));
			ImGui::SliderFloat(skCrypt("FOV Size"), &def::AimbotFov, 20, 999);

			ImGui::SetNextItemWidth(250.000f);
			ImGui::SetCursorPos(ImVec2(143.000f, 96.000f));
			ImGui::SliderFloat(skCrypt("Smooth"), &Smoothness, 2.000f, 50.000f);

			ImGui::SetCursorPos(ImVec2(143.000f, 119.000f));
			ImGui::SliderInt(skCrypt("Esp Distance"), &def::VisDist, 50, 300);


			ImGui::SetNextItemWidth(250.000f);
			ImGui::SetCursorPos(ImVec2(143.000f, 142.000f));
			ImGui::Combo(skCrypt("Aim Bone"), &def::hitboxpos, hitboxes, sizeof(hitboxes) / sizeof(*hitboxes));

			ImGui::SetNextItemWidth(250.000f);
			ImGui::SetCursorPos(ImVec2(143.000f, 175.000f));
			ImGui::Checkbox(skCrypt("Stream Proof"), &WindowStreamProof);

			ImGui::SetNextItemWidth(250.000f);
			ImGui::SetCursorPos(ImVec2(143.000f, 198.000f));
			HotkeyButton(hotkeys::aimkey, ChangeKey, keystatus);

			ImGui::SetCursorPos(ImVec2(143.000f, 221.000f));
			ImGui::Text("Aimbot Hotkey");
			break;
		case 2:
			ImGui::SetCursorPos(ImVec2(143.000f, 27.000f));
			ImGui::Checkbox(skCrypt("Box Esp"), &BoxEsp);

			ImGui::SetCursorPos(ImVec2(143.000f, 50.000f));
			ImGui::Checkbox(skCrypt("CornerBox Esp"), &CornerBoxEsp);

			ImGui::SetCursorPos(ImVec2(143.000f, 73.000f));
			ImGui::Checkbox(skCrypt("CornerBox Filled Esp"), &fillbox);

			ImGui::SetCursorPos(ImVec2(143.000f, 96.000f));
			ImGui::Checkbox(skCrypt("3D Box Esp"), &ThreeDBoxEsp);

			ImGui::SetCursorPos(ImVec2(143.000f, 119.000f));
			ImGui::Checkbox(skCrypt("Distance"), &PlayerDistanceEsp);

			ImGui::SetCursorPos(ImVec2(143.000f, 142.000f));
			ImGui::Checkbox(skCrypt("Snaplines"), &Snaplines);

			ImGui::SetCursorPos(ImVec2(143.000f, 188.000f));
			ImGui::Checkbox(skCrypt("Crosshair"), &crosshair);

			ImGui::SetNextItemWidth(150.000f);
			ImGui::SetCursorPos(ImVec2(143.000f, 211.000f));
			ImGui::SliderInt(skCrypt("Line Thickness"), &LineThinkness, 1, 10);

			ImGui::SetNextItemWidth(150.000f);
			ImGui::SetCursorPos(ImVec2(143.000f, 234.000f));
			ImGui::SliderInt(skCrypt("Box Thickness"), &Boxthinkness, 1, 10);

			ImGui::SetNextItemWidth(150.000f);
			ImGui::SetCursorPos(ImVec2(143.000f, 257.000f));
			ImGui::SliderFloat(skCrypt("Box Width"), &BoxWidthValue, 0.40, 25.f);

			ImGui::SetCursorPos(ImVec2(143.000f, 280.000f));
			ImGui::SetNextItemWidth(250.000f);
			ImGui::SliderInt(skCrypt("Crosshair Size"), &CrosshairSize, 2.000f, 30.000f);

			ImGui::SetCursorPos(ImVec2(143.000f, 303.000f));
			ImGui::Checkbox(skCrypt("SelfEsp"), &SelfEsp);

			ImGui::SetCursorPos(ImVec2(143.000f, 328.000f));
			ImGui::Checkbox(skCrypt("ReloadCheck"), &reloadcheck);

			ImGui::SetCursorPos(ImVec2(143.000f, 353.000f));
			ImGui::Checkbox(skCrypt("TargetingCheck"), &targetingcheck);

			ImGui::SetCursorPos(ImVec2(143.000f, 403.000f));
			ImGui::Checkbox(skCrypt("Dynamic Box Esp"), &DynamicEsp);

			ImGui::SetCursorPos(ImVec2(143.000f, 428.000f));
			ImGui::Checkbox(skCrypt("Skeleton Esp"), &Skeleton);


			break;





	     	case 3:

				ImGui::Text("Writing to Memory is not UD lol");



			break;

		}

	}


	ImGui::EndFrame();
	D3dDevice->SetRenderState(D3DRS_ZENABLE, false);
	D3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	D3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
	D3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);

	if (D3dDevice->BeginScene() >= 0)
	{
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		D3dDevice->EndScene();
	}
	HRESULT result = D3dDevice->Present(NULL, NULL, NULL, NULL);

	if (result == D3DERR_DEVICELOST && D3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
	{
		ImGui_ImplDX9_InvalidateDeviceObjects();
		D3dDevice->Reset(&d3dpp);
		ImGui_ImplDX9_CreateDeviceObjects();
	}
}

D3DPRESENT_PARAMETERS p_Params = { NULL };
HRESULT DirectXInit(HWND hWnd)
{
	//hide_thread(LI_FN(GetCurrentThread).get()());
	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &p_Object)))
		LI_FN(exit).get()(3);

	RtlSecureZeroMemory(&p_Params, sizeof(p_Params));
	p_Params.Windowed = TRUE;
	p_Params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	p_Params.hDeviceWindow = hWnd;
	p_Params.MultiSampleQuality = D3DMULTISAMPLE_NONE;
	p_Params.BackBufferFormat = D3DFMT_A8R8G8B8;
	p_Params.BackBufferWidth = Width;
	p_Params.BackBufferHeight = Height;
	p_Params.EnableAutoDepthStencil = TRUE;
	p_Params.AutoDepthStencilFormat = D3DFMT_D16;
	p_Params.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;




	p_Object->Release();
	return S_OK;
}
HWND hijacked_hwnd{};


void xMainLoop()
{
	MSG Message;
	RtlZeroMemory(&Message, sizeof(Message));
	DirectXInit(hijacked_hwnd);
	while ((Message.message != WM_QUIT) /* && (dt_info->tm_mday == DAY) */)
	{
		if (PeekMessageA(&Message, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessageA(&Message);
			continue;
		}
		HWND hwnd_active = GetForegroundWindow();
		if (hwnd_active == hwnd) {
			HWND hwndtest = GetWindow(hwnd_active, GW_HWNDPREV);
			SetWindowPos(Window, hwndtest, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		}

		RECT rc;
		POINT xy;
		ZeroMemory(&rc, sizeof(RECT));
		ZeroMemory(&xy, sizeof(POINT));
		GetClientRect(hwnd, &rc);
		ClientToScreen(hwnd, &xy);
		rc.left = xy.x;
		rc.top = xy.y;

		ImGuiIO& io = ImGui::GetIO();
		io.IniFilename = NULL;
		io.ImeWindowHandle = hwnd;
		io.DeltaTime = 1.0f / 60.0f;

		POINT p;
		GetCursorPos(&p);
		io.MousePos.x = p.x - xy.x;
		io.MousePos.y = p.y - xy.y;

		if (GetAsyncKeyState(VK_LBUTTON)) {
			io.MouseDown[0] = true;
			io.MouseClicked[0] = true;
			io.MouseClickedPos[0].x = io.MousePos.x;
			io.MouseClickedPos[0].x = io.MousePos.y;
		}
		else
			io.MouseDown[0] = false;
		render();
	}
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	DestroyWindow(Window);
}

