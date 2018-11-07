package com.aio

import com.aio.psi.AIOTypes
import com.intellij.lexer.Lexer
import com.intellij.openapi.editor.*
import com.intellij.openapi.editor.colors.TextAttributesKey
import com.intellij.openapi.fileTypes.SyntaxHighlighterBase
import com.intellij.psi.TokenType
import com.intellij.psi.tree.IElementType

import com.intellij.openapi.editor.colors.TextAttributesKey.createTextAttributesKey

class AIOSyntaxHighlighter : SyntaxHighlighterBase() {

    override fun getHighlightingLexer() = AIOLexerAdapter()

    override fun getTokenHighlights(tokenType: IElementType): Array<TextAttributesKey> {
        return when (tokenType) {
            AIOTypes.SEPARATOR -> SEPARATOR_KEYS
            AIOTypes.KEY -> KEY_KEYS
            AIOTypes.VALUE -> VALUE_KEYS
            AIOTypes.COMMENT -> COMMENT_KEYS
            TokenType.BAD_CHARACTER -> BAD_CHAR_KEYS
            else -> EMPTY_KEYS
        }
    }

    companion object {

        val SEPARATOR = createTextAttributesKey("AIO_SEPARATOR", DefaultLanguageHighlighterColors.OPERATION_SIGN)
        val KEY = createTextAttributesKey("AIO_KEY", DefaultLanguageHighlighterColors.KEYWORD)
        val VALUE = createTextAttributesKey("AIO_VALUE", DefaultLanguageHighlighterColors.STRING)
        val COMMENT = createTextAttributesKey("AIO_COMMENT", DefaultLanguageHighlighterColors.LINE_COMMENT)
        val BAD_CHARACTER = createTextAttributesKey("AIO_BAD_CHARACTER", HighlighterColors.BAD_CHARACTER)

        private val BAD_CHAR_KEYS = arrayOf(BAD_CHARACTER)
        private val SEPARATOR_KEYS = arrayOf(SEPARATOR)
        private val KEY_KEYS = arrayOf(KEY)
        private val VALUE_KEYS = arrayOf(VALUE)
        private val COMMENT_KEYS = arrayOf(COMMENT)
        private val EMPTY_KEYS = arrayOf<TextAttributesKey>()
    }
}