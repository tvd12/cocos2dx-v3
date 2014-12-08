package de.axnsoftware.eclipse.plugins.customprojects.internal.ui.preferences;

import org.eclipse.jface.preference.PreferencePage;
import org.eclipse.jface.resource.ImageDescriptor;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Control;
import org.eclipse.ui.IWorkbench;
import org.eclipse.ui.IWorkbenchPreferencePage;

public class CustomProjectsPreferencesFrontPage extends PreferencePage implements
        IWorkbenchPreferencePage
{

    public CustomProjectsPreferencesFrontPage()
    {
        // TODO Auto-generated constructor stub
    }

    public CustomProjectsPreferencesFrontPage(final String title)
    {
        super(title);
        // TODO Auto-generated constructor stub
    }

    public CustomProjectsPreferencesFrontPage(final String title,
            final ImageDescriptor image)
    {
        super(title, image);
        // TODO Auto-generated constructor stub
    }

    @Override
    protected Control createContents(final Composite parent)
    {
        // TODO Auto-generated method stub
        return null;
    }

    public void init(final IWorkbench workbench)
    {
        // TODO Auto-generated method stub

    }

}
