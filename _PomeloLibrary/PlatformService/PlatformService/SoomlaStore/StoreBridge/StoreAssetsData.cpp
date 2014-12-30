#include "StoreAssetsDefine.h"
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>

typedef struct Foo {
    int len;
    char name[100];
} Foo_t;

JNIEXPORT jint JNICALL
Java_TestJNI_foo(JNIEnv *env, jobject obj, jobject fooObj) {

    Foo_t * bar = malloc(sizeof(Foo_t));
    jclass clazz;
    jfieldID fid;

    //init the bar data of C
    strcpy(bar->name, "Yachun Miao");
    bar->len = strlen(bar->name);

    // mapping bar of C to foo
    clazz = (*env)->GetObjectClass(env, fooObj);
    if (0 == clazz) {
        printf("GetObjectClass returned 0\n");
        return (-1);
    }
    fid = (*env)->GetFieldID(env, clazz, "len", "I");
    (*env)->SetLongField(env, fooObj, fid, bar->len);

    fid = (*env)->GetFieldID(env, clazz, "name", "Ljava/lang/String;");
    jstring name = (*env)->NewStringUTF(env, bar->name);
    (*env)->SetObjectField(env, fooObj, fid, name);

    free(bar);
    return 0;
}