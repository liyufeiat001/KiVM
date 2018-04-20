//
// Created by kiva on 2018/2/25.
//

#pragma once

#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cassert>
#include <shared/types.h>
#include <shared/string.h>
#include <kivm/memory/collectedHeap.h>

#ifdef KIVM_DEBUG
#define D(fmt, ...) \
    do { \
       (void) fprintf(stderr, "===> (KIVM DEBUG) [%s:%d]: " fmt "\n", \
                __FILE__, \
                __LINE__, \
                ##__VA_ARGS__); \
    } while (false)
#else
#define D(fmt, ...)
#endif

#define PANIC(fmt, ...) \
    do { \
       (void) fprintf(stderr, "\n\n\n*** (PANIC) *** [%s:%d]: " fmt "\n\n\n", \
                __FILE__, __LINE__, ##__VA_ARGS__); \
       exit(1); \
    } while (false)


#define JNI_ENTRY_NAME(nameAndSignature) jni_##nameAndSignature
#define JNI_ENTRY(returnType, nameAndSignature) returnType JNI_ENTRY_NAME(nameAndSignature)

namespace kivm {
    class KiVM {
    private:
        static JavaVM *sJavaVMInstance;
        static JNIEnv *sJNIEnvInstance;

    private:
        static void fillInterfaceFunctions(JNINativeInterface_ *nativeInterface);

    public:
        static inline JavaVM *getJavaVMQuick() {
            return sJavaVMInstance;
        }

    public:
        static int getJavaVM(JavaVM **pJavaVM);

        static int getEnv(JavaVM *vm, JNIEnv **pEnv, int version);

        static int createVirtualMachine(JavaVM **pJavaVM, JNIEnv **pEnv, JavaVMInitArgs *initArgs);

        static int destroyJavaVM(JavaVM *vm);
    };
}
