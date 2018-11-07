package com.aio.psi

import com.aio.AIOFileType
import com.aio.AIOLanguage
import com.intellij.extapi.psi.PsiFileBase
import com.intellij.openapi.fileTypes.FileType
import com.intellij.psi.FileViewProvider

import javax.swing.*

class AIOFile(viewProvider: FileViewProvider) : PsiFileBase(viewProvider, AIOLanguage.INSTANCE) {

    override fun getFileType() = AIOFileType.INSTANCE

    override fun toString() = "AIO File"

    override fun getIcon(flags: Int) = super.getIcon(flags)
}