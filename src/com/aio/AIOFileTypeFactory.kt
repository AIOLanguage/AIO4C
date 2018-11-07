package com.aio

import com.intellij.openapi.fileTypes.*

class AIOFileTypeFactory : FileTypeFactory() {

    override fun createFileTypes(fileTypeConsumer: FileTypeConsumer) {
        fileTypeConsumer.consume(AIOFileType.INSTANCE)
    }
}