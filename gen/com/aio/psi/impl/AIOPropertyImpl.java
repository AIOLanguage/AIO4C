// This is a generated file. Not intended for manual editing.
package com.aio.psi.impl;

import java.util.List;
import org.jetbrains.annotations.*;
import com.intellij.lang.ASTNode;
import com.intellij.psi.PsiElement;
import com.intellij.psi.PsiElementVisitor;
import com.intellij.psi.util.PsiTreeUtil;
import static com.aio.psi.AIOTypes.*;
import com.intellij.extapi.psi.ASTWrapperPsiElement;
import com.aio.psi.*;

public class AIOPropertyImpl extends ASTWrapperPsiElement implements AIOProperty {

  public AIOPropertyImpl(@NotNull ASTNode node) {
    super(node);
  }

  public void accept(@NotNull AIOVisitor visitor) {
    visitor.visitProperty(this);
  }

  public void accept(@NotNull PsiElementVisitor visitor) {
    if (visitor instanceof AIOVisitor) accept((AIOVisitor)visitor);
    else super.accept(visitor);
  }

}
