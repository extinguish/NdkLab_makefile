# the basic information of this test case
This project mainly using to demonstrate the use case of which abandon the jni/
folder, that is to way, all of the c/cpp file and the makefile will do not located
under the jni/ folder. 
And thus we need to specify the Android.mk file of this project manually.

The AndroidManifest.xml file that located under the root directory are empty, and this 
is not a bug or we forget to add content to this file, but we want to do this.
If we specify the NDK_PROJECT_PATH environment explicitly, then we do not need this 
file.