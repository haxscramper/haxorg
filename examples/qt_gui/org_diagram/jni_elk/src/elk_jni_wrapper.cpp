#include "elk_jni_wrapper.hpp"
#include <jni.h>
#include <iostream>
#include <format>


#include <dlfcn.h>
#define PATH_SEPARATOR ":"

namespace elk_jni {

class ElkLayoutEngine::Impl {
  public:
    JavaVM*   jvm                 = nullptr;
    JNIEnv*   env                 = nullptr;
    jclass    wrapperClass        = nullptr;
    jmethodID performLayoutMethod = nullptr;
    bool      initialized         = false;

    bool initializeJVM(std::string const& wrapper_jar) {
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
            throw std::runtime_error(
                std::format("Failed to create JVM: {}", result));
        }

        // Find the wrapper class
        wrapperClass = env->FindClass("com/example/elk/ElkLayoutWrapper");
        if (!wrapperClass) {
            env->ExceptionDescribe();
            throw std::runtime_error(
                "Failed to find ElkLayoutWrapper class");
            return false;
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
            return false;
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
        if (!initialized || !env) { return "ERROR: JVM not initialized"; }

        // Create Java string
        jstring jInputJson = env->NewStringUTF(inputJson.c_str());
        if (!jInputJson) { return "ERROR: Failed to create input string"; }

        // Call the method
        jstring jResult = (jstring)env->CallStaticObjectMethod(
            wrapperClass, performLayoutMethod, jInputJson);

        // Clean up input string
        env->DeleteLocalRef(jInputJson);

        if (env->ExceptionCheck()) {
            env->ExceptionDescribe();
            env->ExceptionClear();
            return "ERROR: Exception in Java method";
        }

        if (!jResult) { return "ERROR: Null result from Java method"; }

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
    shutdown();
    delete pImpl;
}

bool ElkLayoutEngine::initialize(const std::string& classPathJar) {
    return pImpl->initializeJVM(classPathJar);
}

void ElkLayoutEngine::shutdown() { pImpl->shutdownJVM(); }

std::string ElkLayoutEngine::performLayout(const std::string& inputJson) {
    return pImpl->callPerformLayout(inputJson);
}

bool ElkLayoutEngine::isInitialized() const { return pImpl->initialized; }

} // namespace elk_jni
