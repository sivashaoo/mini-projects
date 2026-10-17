plugins {
    id("com.android.application")
    id("org.jetbrains.kotlin.android")
}

android {
    namespace = "com.sivashaoo.nimoai"
    compileSdk = 35

    defaultConfig {
        applicationId = "com.sivashaoo.nimoai"
        minSdk = 23
        targetSdk = 28
        versionCode = 1
        versionName = "0.1.0"
    }
}
