package com.aio.psi

import com.aio.AIOLanguage
import com.intellij.psi.tree.IElementType

class AIOElementType(debugName: String) : IElementType(debugName, AIOLanguage.INSTANCE)