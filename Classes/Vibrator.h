/*#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include <android/log.h>
#include "platform/android/jni/JniHelper.h"
#endif
#define  CLASS_NAME "org/cocos2dx/lib/Cocos2dxHelper"
#ifndef _VIBRATOR_
#define _VIBRATOR_
class Vibrator
{
public:
	static void Vibrate(int time);
	static void CancelVibrate();
};
#endif*/