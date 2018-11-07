package com.aio.psi

import com.aio.AIOLanguage
import com.intellij.psi.tree.IElementType

class AIOTokenType(debugName: String) : IElementType(debugName, AIOLanguage.INSTANCE) {

    override fun toString() = "AIOTokenType." + super.toString()
}