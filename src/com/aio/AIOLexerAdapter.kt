package com.aio

import com.intellij.lexer.FlexAdapter

import java.io.Reader

class AIOLexerAdapter : FlexAdapter(AIOLexer(null as Reader?))