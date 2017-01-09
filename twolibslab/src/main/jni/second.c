#include "com_scguo_twolibslab_MainActivity.h"
#include "first.h"
#include <jni.h>

jint
Java_com_scguo_twolibslab_MainActivity_add(JNIEnv* env, jobject this, jint x, jint y) {
    return first(x, y);
}


