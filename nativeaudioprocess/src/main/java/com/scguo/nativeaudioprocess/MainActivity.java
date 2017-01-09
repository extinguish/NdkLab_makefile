package com.scguo.nativeaudioprocess;

import android.app.Activity;
import android.content.res.AssetManager;
import android.os.Bundle;

public class MainActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }


    public static native void createEngine();
    public static native void createBufferQueueAudioPlayer();
    public static native boolean createAssetAudioPlayer(AssetManager assetManager, String fileName);

    // true == PLAYING, false == PAUSED
    public static native void setPlayingAssetAudioPlayer(boolean isPlaying);
    public static native boolean createUriAudioPlayer(String uri);
    public static native void setPlayingUriAudioPlayer(boolean isPlaying);
    public static native void setLoopingUriAudioPlayer(boolean isLooping);
    public static native void setChannelMuteUriAudioPlayer(int channel, boolean mute);
    public static native void setChannelSoloUriAudioPlayer(int channel, boolean solo);
    public static native int getNumChannelsUriAudioPlayer();
    public static native void setVolumeUriAudioPlayer(int millibel);
    public static native void setMuteUriAudioPlayer(boolean mute);
    public static native void enableStereoPositionUriAudioPlayer(boolean enable);
    public static native void setStereoPositionUriAudioPlayer(int permille);
    public static native boolean selectClip(int which, int count);
    public static native boolean enableRevert(boolean enabled);
    public static native boolean createAudioRecorder();
    public static native void startRecording();
    public static native void shutDown();

    static {
        System.loadLibrary("native_audio_module");
    }
}
