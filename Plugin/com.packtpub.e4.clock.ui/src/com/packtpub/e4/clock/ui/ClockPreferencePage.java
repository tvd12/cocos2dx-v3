package com.packtpub.e4.clock.ui;

import java.util.Arrays;
import java.util.TimeZone;

import org.eclipse.jface.preference.BooleanFieldEditor;
import org.eclipse.jface.preference.ColorFieldEditor;
import org.eclipse.jface.preference.ComboFieldEditor;
import org.eclipse.jface.preference.DirectoryFieldEditor;
import org.eclipse.jface.preference.FieldEditorPreferencePage;
import org.eclipse.jface.preference.FileFieldEditor;
import org.eclipse.jface.preference.IntegerFieldEditor;
import org.eclipse.jface.preference.PathEditor;
import org.eclipse.jface.preference.RadioGroupFieldEditor;
import org.eclipse.jface.preference.ScaleFieldEditor;
import org.eclipse.jface.resource.ImageDescriptor;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Control;
import org.eclipse.ui.IWorkbench;
import org.eclipse.ui.IWorkbenchPreferencePage;

public class ClockPreferencePage 
		extends FieldEditorPreferencePage 
		implements IWorkbenchPreferencePage {

	public ClockPreferencePage() {
		super(FieldEditorPreferencePage.GRID);
	}

	public ClockPreferencePage(String title) {
	}

	public ClockPreferencePage(String title, ImageDescriptor image) {
	}

	@Override
	public void init(IWorkbench workbench) {
		this.setPreferenceStore(Activator.getDefault().getPreferenceStore());
	}

	@Override
	protected Control createContents(Composite parent) {
		return super.createContents(parent);
	}

	@Override
	protected void createFieldEditors() {
		this.addField(new IntegerFieldEditor("launchCount", 
				"Number of times it has been launched", 
				this.getFieldEditorParent()));
		
		IntegerFieldEditor offset = new IntegerFieldEditor("offset", 
				"Current offset form GMT", 
				this.getFieldEditorParent());
		offset.setValidRange(-14, +12);
		this.addField(offset);
		
		String[][] data = null;
		String[] ids = TimeZone.getAvailableIDs();
		Arrays.sort(ids);
		data = new String[ids.length][];
		for(int i = 0 ; i < ids.length ; i++) {
			data[i] = new String[] {ids[i], ids[i]};
		}

		this.addField(new ComboFieldEditor("favorite", 
				"Favorite time zone", 
				data, 
				this.getFieldEditorParent()));
		this.addField(new BooleanFieldEditor("tick",
				"Boolean value",
				this.getFieldEditorParent()));
		this.addField(new ColorFieldEditor("colour", 
				"Favourite colour",
				this.getFieldEditorParent()));
		this.addField(new ScaleFieldEditor("scale", 
				"Scale",
				this.getFieldEditorParent(), 
				0, 
				360, 
				10, 
				90));
		this.addField(new FileFieldEditor("file", 
				"Pick a file",
				this.getFieldEditorParent()));
		this.addField(new DirectoryFieldEditor("dir", 
				"Pick a directory",
				this.getFieldEditorParent()));
		this.addField(new PathEditor("path",
				"Path",
		        "Directory",
		        this.getFieldEditorParent()));
		this.addField(new RadioGroupFieldEditor("group", 
				"Radio choices", 
				3,
		        data,
		        this.getFieldEditorParent(),true));

	}

}
