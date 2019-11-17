#pragma once

#include "../Module/Brush/BrushModule.h"
#define _BRUSH BrushModule::GetInstance()

#include "../Module/Font/FontManager.h"
#define _FONT FontManager::GetInstance()

#include "../Module/Timer/TimerModule.h"
#define _TIMER TimerModule::GetInstance()

#include "../Module/Key/KeyModule.h"
#define _KEYCODE KeyModule::GetInstance()

#include "../Module/Camera/CameraModule.h"
#define _CAMERA CameraModule::GetInstance()

#include "../Module/Image/ImageManager.h"
#define _IMAGE ImageManager::GetInstance()

#include "../Module/Sound/SoundModule.h"
#define _SOUND SoundModule::GetInstance()

#include "../Module/Scene/SceneManager.h"
#define _SCENE SceneManager::GetInstance()

#include "../Module/Effect/EffectModule.h"
#define _EFFECT EffectModule::GetInstance()