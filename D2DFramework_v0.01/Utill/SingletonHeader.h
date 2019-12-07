#pragma once

#include "../Manager/Singleton/Brush/BrushModule.h"
#define _BRUSH BrushModule::GetInstance()

#include "../Manager/Singleton/Font/FontManager.h"
#define _FONT FontManager::GetInstance()

#include "../Manager/Singleton/Timer/TimerModule.h"
#define _TIMER TimerModule::GetInstance()

#include "../Manager/Singleton/Key/KeyModule.h"
#define _KEYCODE KeyModule::GetInstance()

#include "../Manager/Singleton/Camera/CameraModule.h"
#define _CAMERA CameraModule::GetInstance()

#include "../Manager/Singleton/Resource/Image/ImageManager.h"
#define _IMAGE ImageManager::GetInstance()

#include "../Manager/Singleton/Resource/Sound/SoundModule.h"
#define _SOUND SoundModule::GetInstance()

#include "../Manager/Singleton/Scene/SceneManager.h"
#define _SCENE SceneManager::GetInstance()