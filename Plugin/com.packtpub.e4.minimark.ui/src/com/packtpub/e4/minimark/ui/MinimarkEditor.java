package com.packtpub.e4.minimark.ui;

import org.eclipse.ui.editors.text.TextFileDocumentProvider;
import org.eclipse.ui.texteditor.AbstractDecoratedTextEditor;

public class MinimarkEditor extends AbstractDecoratedTextEditor {

	public MinimarkEditor() {
		setDocumentProvider(new TextFileDocumentProvider());
	}
	
}
