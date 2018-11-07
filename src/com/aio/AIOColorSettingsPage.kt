package com.aio

import com.aio.AIOLanguage.Companion.LANGUAGE_NAME
import com.intellij.openapi.editor.colors.TextAttributesKey
import com.intellij.openapi.options.colors.AttributesDescriptor
import com.intellij.openapi.options.colors.ColorDescriptor
import com.intellij.openapi.options.colors.ColorSettingsPage

class AIOColorSettingsPage : ColorSettingsPage {

    override fun getIcon() = AIOIcons.FILE

    override fun getHighlighter() = AIOSyntaxHighlighter()

    override fun getDemoText() =
            "# You are reading the \".properties\" entry.\n" +
                    "! The exclamation mark can also mark text as comments.\n" +
                    "website = http://en.wikipedia.org/\n" +
                    "language = English\n" +
                    "# The backslash below tells the application to continue reading\n" +
                    "# the value onto the next line.\n" +
                    "message = Welcome to \\\n" +
                    "          Wikipedia!\n" +
                    "# Add spaces to the key\n" +
                    "key\\ with\\ spaces = This is the value that could be looked up with the key \"key with spaces\".\n" +
                    "# Unicode\n" +
                    "tab : \\u0009"

    override fun getAdditionalHighlightingTagToDescriptorMap(): Map<String, TextAttributesKey>? = null

    override fun getAttributeDescriptors() = DESCRIPTORS

    override fun getColorDescriptors(): Array<ColorDescriptor> = ColorDescriptor.EMPTY_ARRAY

    override fun getDisplayName() = LANGUAGE_NAME

    companion object {

        private val DESCRIPTORS = arrayOf(
                AttributesDescriptor("Key", AIOSyntaxHighlighter.KEY),
                AttributesDescriptor("Separator", AIOSyntaxHighlighter.SEPARATOR),
                AttributesDescriptor("Value", AIOSyntaxHighlighter.VALUE)
        )
    }
}