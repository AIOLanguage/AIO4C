package com.aio

import com.intellij.openapi.fileTypes.*
import com.intellij.openapi.project.Project
import com.intellij.openapi.vfs.VirtualFile

class AIOSyntaxHighlighterFactory : SyntaxHighlighterFactory() {

    override fun getSyntaxHighlighter(project: Project?, virtualFile: VirtualFile?) = AIOSyntaxHighlighter()
}