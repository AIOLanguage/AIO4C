package com.aio

import com.intellij.openapi.fileTypes.LanguageFileType
import org.jetbrains.annotations.*

import javax.swing.*

class AIOFileType private constructor() : LanguageFileType(AIOLanguage.INSTANCE) {

    override fun getName() = "AIO file"

    override fun getDescription() = "AIO language file"

    override fun getDefaultExtension() = "aio"

    override fun getIcon() = AIOIcons.FILE

    companion object {

        val INSTANCE = AIOFileType()
    }
}