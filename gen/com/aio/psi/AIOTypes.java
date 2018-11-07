// This is a generated file. Not intended for manual editing.
package com.aio.psi;

import com.intellij.psi.tree.IElementType;
import com.intellij.psi.PsiElement;
import com.intellij.lang.ASTNode;
import com.aio.psi.impl.*;

public interface AIOTypes {

  IElementType PROPERTY = new AIOElementType("PROPERTY");

  IElementType COMMENT = new AIOTokenType("COMMENT");
  IElementType CRLF = new AIOTokenType("CRLF");
  IElementType KEY = new AIOTokenType("KEY");
  IElementType SEPARATOR = new AIOTokenType("SEPARATOR");
  IElementType VALUE = new AIOTokenType("VALUE");

  class Factory {
    public static PsiElement createElement(ASTNode node) {
      IElementType type = node.getElementType();
      if (type == PROPERTY) {
        return new AIOPropertyImpl(node);
      }
      throw new AssertionError("Unknown element type: " + type);
    }
  }
}
