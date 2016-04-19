/*#include "Vibrator.h"

void Vibrator::Vibrate(int time) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "vibrate", "(I)V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID, time);
		t.env->DeleteLocalRef(t.classID);
	}
#endif
}
void Vibrator::CancelVibrate() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "cancelVibrate", "()V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
#endif
}*/