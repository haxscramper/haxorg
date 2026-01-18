#include "elk_jni_wrapper.hpp"
#include <jni.h>
#include <iostream>
#include <format>


#include <dlfcn.h>
#define PATH_SEPARATOR ":"

namespace elk_jni {

class ElkLayoutEngine::Impl {
  private:
    static inline JavaVM*   jvm                 = nullptr;
    static inline JNIEnv*   env                 = nullptr;
    static inline jclass    wrapperClass        = nullptr;
    static inline jmethodID performLayoutMethod = nullptr;
    static inline bool      initialized         = false;

  public:
    bool isInitialized() const { return initialized; }

    bool initializeJVM(std::string const& wrapper_jar) {
        if (initialized) { return true; }

        JavaVMInitArgs vm_args;
        JavaVMOption   options[2];

        // Get the current directory and construct classpath
        std::string classpath = std::format(
            "-Djava.class.path={}", wrapper_jar);

        options[0].optionString = const_cast<char*>(classpath.c_str());
        options[1].optionString = const_cast<char*>("-Xmx512m");

        vm_args.version            = JNI_VERSION_1_8;
        vm_args.nOptions           = 2;
        vm_args.options            = options;
        vm_args.ignoreUnrecognized = false;

        jint result = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);
        if (result != JNI_OK) {
            std::string desc;
            switch (result) {
                case JNI_OK: desc = "JNI_OK 0    /* success */"; break;
                case JNI_ERR:
                    desc = "JNI_ERR (-1) /* unknown error */";
                    break;
                case JNI_EDETACHED:
                    desc
                        = "JNI_EDETACHED (-2) /* thread detached from the "
                          "VM */";
                    break;
                case JNI_EVERSION:
                    desc = "JNI_EVERSION (-3) /* JNI version error */";
                    break;
                case JNI_ENOMEM:
                    desc = "JNI_ENOMEM (-4) /* not enough memory */";
                    break;
                case JNI_EEXIST:
                    desc = "JNI_EEXIST (-5) /* VM already created */";
                    break;
                case JNI_EINVAL:
                    desc = "JNI_EINVAL (-6) /* invalid arguments */";
                    break;
            }

            throw std::runtime_error(
                std::format("Failed to create JVM: {}", result));
        }

        // Find the wrapper class
        wrapperClass = env->FindClass("com/example/elk/ElkLayoutWrapper");
        if (!wrapperClass) {
            env->ExceptionDescribe();
            throw std::runtime_error(
                "Failed to find ElkLayoutWrapper class");
        }

        // Make it a global reference
        wrapperClass = (jclass)env->NewGlobalRef(wrapperClass);

        // Get the method ID
        performLayoutMethod = env->GetStaticMethodID(
            wrapperClass,
            "performLayout",
            "(Ljava/lang/String;)Ljava/lang/String;");
        if (!performLayoutMethod) {
            env->ExceptionDescribe();
            throw std::runtime_error(
                "Failed to find performLayout method");
        }

        initialized = true;
        return true;
    }

    void shutdownJVM() {
        if (jvm) {
            if (wrapperClass) {
                env->DeleteGlobalRef(wrapperClass);
                wrapperClass = nullptr;
            }
            jvm->DestroyJavaVM();
            jvm = nullptr;
            env = nullptr;
        }
        initialized = false;
    }

    std::string callPerformLayout(const std::string& inputJson) {
        if (!initialized || !env) {
            throw std::runtime_error("JVM not initialized");
        }

        // Create Java string
        jstring jInputJson = env->NewStringUTF(inputJson.c_str());
        if (!jInputJson) {
            throw std::runtime_error("Failed to create input string");
        }

        // Call the method
        jstring jResult = (jstring)env->CallStaticObjectMethod(
            wrapperClass, performLayoutMethod, jInputJson);

        // Clean up input string
        env->DeleteLocalRef(jInputJson);

        if (env->ExceptionCheck()) {
            env->ExceptionDescribe();
            env->ExceptionClear();
            throw std::runtime_error("Exception in Java method");
        }

        if (!jResult) {
            throw std::runtime_error("Null result from Java method");
        }

        // Convert result to C++ string
        const char* resultChars = env->GetStringUTFChars(jResult, nullptr);
        std::string result(resultChars);
        env->ReleaseStringUTFChars(jResult, resultChars);
        env->DeleteLocalRef(jResult);

        return result;
    }
};

ElkLayoutEngine::ElkLayoutEngine() : pImpl(new Impl()) {}

ElkLayoutEngine::~ElkLayoutEngine() {
    // shutdown();
    delete pImpl;
}

bool ElkLayoutEngine::initialize(const std::string& classPathJar) {
    return pImpl->initializeJVM(classPathJar);
}

void ElkLayoutEngine::shutdown() { pImpl->shutdownJVM(); }

std::string ElkLayoutEngine::performLayout(const std::string& inputJson) {
    return pImpl->callPerformLayout(inputJson);
}

bool ElkLayoutEngine::isInitialized() const {
    return pImpl->isInitialized();
}

} // namespace elk_jni
