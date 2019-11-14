#pragma once

#include "../Singleton/Color/ColorManager.h"
#define _COLOR ColorManager::GetInstance()

#include "../Singleton/Font/FontManager.h"
#define _FONT FontManager::GetInstance()

#include "../Singleton/Timer/TimerModule.h"
#define _TIMER TimerModule::GetInstance()

#include "../Singleton/Key/KeyModule.h"
#define _KEY KeyModule::GetInstance()

#include "../Singleton/Camera/CameraModule.h"
#define _CAMERA CameraModule::GetInstance()

#include "../Singleton/Store/Image/ImageStore.h"
#define _IMAGE ImageStore::GetInstance()

#include "../Singleton/Store/Sound/SoundStore.h"
#define _SOUND SoundStore::GetInstance()

#include "../Singleton/Scene/SceneManager.h"
#define _SCENE SceneManager::GetInstance()

//#include "../Singleton/Effect/EffectModule.h"
//#define _EFFECT EffectModule::GetInstance()