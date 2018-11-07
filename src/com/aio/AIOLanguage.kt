package com.aio

import com.intellij.lang.Language

class AIOLanguage private constructor() : Language(LANGUAGE_NAME) {

    companion object {

        const val LANGUAGE_NAME = "AIO"

        val INSTANCE = AIOLanguage()
    }
}