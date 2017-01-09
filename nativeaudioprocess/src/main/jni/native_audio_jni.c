// the file of which contains all of the method using to process the audio file
// and we are using the OpenSL ES provided by Android System
#include "com_scguo_nativeaudioprocess_MainActivity.h"
#include <assert.h>
#include <jni.h>
#include <string.h>


// for native audio process
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

// for native asset manager
#include <sys/types.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

// the following are trick of which using to load a big series of chars
// and the process tricks are implemented by define these long and tedious
// string into a separate file, and then load this file into current file
// by using #include
// pre-recorded sound clips, both are 8 khz mono 16-bit signed little endian
static const char hello[] =
#include "hello_clip.h"
;

static const char android[] =
#include "android_clip.h"
;


// engine interfaces
static SLObjectItf engineObject = NULL;
static SLEngineItf engineEngine;

// output mix interfaces
static SLObjectItf outputMixObject = NULL;
static SLEnvironmentalReverbItf outputMixEnvironmentalReverb = NULL;

// buffer queue player interfaces
static SLObjectItf bpPlayerObject = NULL;
static SLPlayItf bpPlayerPlay;
static SLSeekItf bpPlayerSeek;
static SLMuteSoloItf bpPlayerMuteSolo;
static SLVolumeItf bpPlayerVolume;

// aux effect on the output mix, used by the buffer queue player
static const SLEnvironmentalReverbSettings reverbSettings =
 SL_I3DL2_ENVIRONMENT_PRESET_STONECORRIDOR;

// URI player interfaces
static SLObjectItf uriPlayerObject = NULL;
static SLPlayItf uriPlayerPlay;
static SLSeekItf uriPlayerSeek;
static SLMuteSoloItf uriPlayerMuteSolo;
static SLVolumeItf uriPlayerVolume;

// file descriptor player interfaces
static SLObjectItf fdPlayerObject = NULL;
static SLPlayItf fdPlayerPlay;
static SLSeekItf fdPlayerSeek;
static SLMuteSoloItf fdPlayerMuteSolo;
static SLVolumeItf fdPlayerVolume;

// recorder interfaces
static SLObjectItf recorderObject = NULL;
static SLRecordItf recorderRecord;
static SLAndroidSimpleBufferQueueItf recorderBufferQueue;

// synthesized sawtooth clip
#define SAWTOOTH_FRAMES 8000
static short sawtoothBuffer[SAWTOOTH_FRAMES];

// 5 seconds of recorded audio at 16 kHz mono, 16-bit signed little endian
#define RECORDER_FRAMES (16000 * 5)
static short recorderBuffer[RECORDER_FRAMES];
static unsigned recorderSize = 0;
static SLmilliHertz recorderSR;



// expose the volume apis to the java for one of the three players
static SLVolumeItf getVolume() {
    if (uriPlayerVolume != NULL) {
        return uriPlayerVolume;
    } else if (fdPlayerVolume != NULL) {
        return fdPlayerVolume;
    } else {
        return bpPlayerVolume;
    }
}





/*
 * Class:     com_scguo_nativeaudioprocess_MainActivity
 * Method:    createEngine
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_scguo_nativeaudioprocess_MainActivity_createEngine
  (JNIEnv *, jclass);

/*
 * Class:     com_scguo_nativeaudioprocess_MainActivity
 * Method:    createBufferQueueAudioPlayer
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_scguo_nativeaudioprocess_MainActivity_createBufferQueueAudioPlayer
  (JNIEnv *, jclass);

/*
 * Class:     com_scguo_nativeaudioprocess_MainActivity
 * Method:    createAssetAudioPlayer
 * Signature: (Landroid/content/res/AssetManager;Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_scguo_nativeaudioprocess_MainActivity_createAssetAudioPlayer
  (JNIEnv *, jclass, jobject, jstring);

/*
 * Class:     com_scguo_nativeaudioprocess_MainActivity
 * Method:    setPlayingAssetAudioPlayer
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_com_scguo_nativeaudioprocess_MainActivity_setPlayingAssetAudioPlayer
  (JNIEnv *, jclass, jboolean);

/*
 * Class:     com_scguo_nativeaudioprocess_MainActivity
 * Method:    createUriAudioPlayer
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_scguo_nativeaudioprocess_MainActivity_createUriAudioPlayer
  (JNIEnv *, jclass, jstring);

/*
 * Class:     com_scguo_nativeaudioprocess_MainActivity
 * Method:    setPlayingUriAudioPlayer
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_com_scguo_nativeaudioprocess_MainActivity_setPlayingUriAudioPlayer
  (JNIEnv *, jclass, jboolean);

/*
 * Class:     com_scguo_nativeaudioprocess_MainActivity
 * Method:    setLoopingUriAudioPlayer
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_com_scguo_nativeaudioprocess_MainActivity_setLoopingUriAudioPlayer
  (JNIEnv *, jclass, jboolean);

/*
 * Class:     com_scguo_nativeaudioprocess_MainActivity
 * Method:    setChannelMuteUriAudioPlayer
 * Signature: (IZ)V
 */
JNIEXPORT void JNICALL Java_com_scguo_nativeaudioprocess_MainActivity_setChannelMuteUriAudioPlayer
  (JNIEnv *, jclass, jint, jboolean);

/*
 * Class:     com_scguo_nativeaudioprocess_MainActivity
 * Method:    setChannelSoloUriAudioPlayer
 * Signature: (IZ)V
 */
JNIEXPORT void JNICALL Java_com_scguo_nativeaudioprocess_MainActivity_setChannelSoloUriAudioPlayer
  (JNIEnv *, jclass, jint, jboolean);

/*
 * Class:     com_scguo_nativeaudioprocess_MainActivity
 * Method:    getNumChannelsUriAudioPlayer
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_scguo_nativeaudioprocess_MainActivity_getNumChannelsUriAudioPlayer
  (JNIEnv *, jclass);

/*
 * Class:     com_scguo_nativeaudioprocess_MainActivity
 * Method:    setVolumeUriAudioPlayer
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_scguo_nativeaudioprocess_MainActivity_setVolumeUriAudioPlayer
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_scguo_nativeaudioprocess_MainActivity
 * Method:    setMuteUriAudioPlayer
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_com_scguo_nativeaudioprocess_MainActivity_setMuteUriAudioPlayer
  (JNIEnv *, jclass, jboolean);

/*
 * Class:     com_scguo_nativeaudioprocess_MainActivity
 * Method:    enableStereoPositionUriAudioPlayer
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_com_scguo_nativeaudioprocess_MainActivity_enableStereoPositionUriAudioPlayer
  (JNIEnv *, jclass, jboolean);

/*
 * Class:     com_scguo_nativeaudioprocess_MainActivity
 * Method:    setStereoPositionUriAudioPlayer
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_scguo_nativeaudioprocess_MainActivity_setStereoPositionUriAudioPlayer
  (JNIEnv * env, jclass clazz, jint ) {

  }

/*
 * Class:     com_scguo_nativeaudioprocess_MainActivity
 * Method:    selectClip
 * Signature: (II)Z
 */
JNIEXPORT jboolean JNICALL Java_com_scguo_nativeaudioprocess_MainActivity_selectClip
  (JNIEnv * env, jclass clazz, jint which, jint count) {

  }

/*
 * Class:     com_scguo_nativeaudioprocess_MainActivity
 * Method:    enableRevert
 * Signature: (Z)Z
 */
JNIEXPORT jboolean JNICALL Java_com_scguo_nativeaudioprocess_MainActivity_enableRevert
  (JNIEnv *, jclass, jboolean) {


  }

/*
 * Class:     com_scguo_nativeaudioprocess_MainActivity
 * Method:    createAudioRecorder
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_scguo_nativeaudioprocess_MainActivity_createAudioRecorder
  (JNIEnv * env, jclass clazz) {



  }

/*
 * Class:     com_scguo_nativeaudioprocess_MainActivity
 * Method:    startRecording
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_scguo_nativeaudioprocess_MainActivity_startRecording
  (JNIEnv * env, jclass clazz) {

  }

/*
 * Class:     com_scguo_nativeaudioprocess_MainActivity
 * Method:    shutDown
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_scguo_nativeaudioprocess_MainActivity_shutDown
  (JNIEnv * env, jclass clazz) {


  }
