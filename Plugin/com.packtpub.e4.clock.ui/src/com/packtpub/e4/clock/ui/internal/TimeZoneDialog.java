package com.packtpub.e4.clock.ui.internal;

import java.util.TimeZone;

import org.eclipse.jface.dialogs.IDialogConstants;
import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.swt.SWT;
import org.eclipse.swt.graphics.RGB;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Control;
import org.eclipse.swt.widgets.Shell;

import com.packtpub.e4.clock.ui.ClockWidget;

public class TimeZoneDialog extends MessageDialog {

	private TimeZone timeZone;
	public TimeZoneDialog(Shell parentShell, TimeZone timeZone) {
		super(parentShell, timeZone.getID(), null, 
				"Time Zone " + timeZone.getID(), 
				INFORMATION, new String[] {IDialogConstants.OK_LABEL}, 0);
		this.timeZone = timeZone;
	}
	
	@Override
	protected Control createCustomArea(Composite parent) {
		ClockWidget clock = new ClockWidget(parent, 
				SWT.NONE, 
				new RGB(128, 255, 0));
		clock.setOffset((TimeZone.getDefault().getOffset(System.currentTimeMillis())
				- timeZone.getOffset(System.currentTimeMillis()))
				/ 3600000);
		
		return parent;
	}
	
}
