package com.aio

import com.aio.parser.AIOParser
import com.aio.psi.AIOFile
import com.aio.psi.AIOTypes
import com.intellij.lang.*
import com.intellij.lexer.Lexer
import com.intellij.openapi.project.Project
import com.intellij.psi.*
import com.intellij.psi.tree.*

class AIOParserDefinition : ParserDefinition {

    override fun createLexer(project: Project) = AIOLexerAdapter()

    override fun getWhitespaceTokens() = WHITE_SPACES

    override fun getCommentTokens() = COMMENTS

    override fun getStringLiteralElements(): TokenSet = TokenSet.EMPTY

    override fun createParser(project: Project) = AIOParser()

    override fun getFileNodeType() = FILE

    override fun createFile(viewProvider: FileViewProvider) = AIOFile(viewProvider)

    override fun spaceExistanceTypeBetweenTokens(left: ASTNode, right: ASTNode) = ParserDefinition.SpaceRequirements.MAY

    override fun createElement(node: ASTNode): PsiElement = AIOTypes.Factory.createElement(node)

    companion object {

        val WHITE_SPACES = TokenSet.create(TokenType.WHITE_SPACE)

        val COMMENTS = TokenSet.create(AIOTypes.COMMENT)

        val FILE = IFileElementType(AIOLanguage.INSTANCE)
    }
}