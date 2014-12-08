package de.axnsoftware.eclipse.plugins.customprojects.internal.ui.wizards;

import org.eclipse.jface.dialogs.IDialogPage;
import org.eclipse.jface.wizard.WizardPage;
import org.eclipse.swt.SWT;
import org.eclipse.swt.events.ModifyEvent;
import org.eclipse.swt.events.ModifyListener;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Text;

/**
 * The "New" wizard page allows setting the container for the new file as well
 * as the file name. The page will only accept file name without the extension
 * OR with the extension that matches the expected one (java).
 */

public class NewCustomJavaProjectWizardPage1 extends WizardPage
{
    private String templateName;
    private String templatePath;
    private Text   applicationName;

    /**
     * Constructor for SampleNewWizardPage.
     * 
     * @param pageName
     */
    public NewCustomJavaProjectWizardPage1()
    {
        super("wizardPage");
        this.setTitle("Multi-page Editor File");
        this.setDescription("This wizard creates a new file with *.java extension that can be opened by a multi-page editor.");
    }

    /**
     * @see IDialogPage#createControl(Composite)
     */
    public void createControl(final Composite parent)
    {

        /*
         * TODO Layout: (see standard NewClass/TypeWizardPage from JDT
         * 
         * Error messages/hints
         * 
         * Template selector
         * 
         * Application Name Application Class Name (initially derived from
         * application name, once manually edited it will not change upon
         * changing the application name)
         */

        final Composite container = new Composite(parent, SWT.NULL);

        final Composite templateSelector = new Composite(container, SWT.NULL);
        final GridLayout layout = new GridLayout();
        // FIXME add controls (list box, hyper links to prefs page)
        templateSelector.setLayout(layout);
        layout.numColumns = 2;
        layout.verticalSpacing = 9;
        final Label label = new Label(templateSelector, SWT.NULL);
        label.setText("&Choose Template:");

        this.applicationName = new Text(container, SWT.BORDER | SWT.SINGLE);
        final GridData gd = new GridData(GridData.FILL_HORIZONTAL);
        this.applicationName.setLayoutData(gd);
        this.applicationName.addModifyListener(new ModifyListener()
        {
            public void modifyText(final ModifyEvent e)
            {
                NewCustomJavaProjectWizardPage1.this.dialogChanged();
            }
        });

        this.initialize();
        this.dialogChanged();
        this.setControl(container);
    }

    /**
     * Ensures that both text fields are set.
     */

    private void dialogChanged()
    {
        this.updateStatus(null);
    }

    public String getApplicationName()
    {
        return this.templateName;
    }

    public String getTemplateName()
    {
        return this.templateName;
    }

    public String getTemplatePath()
    {
        return this.templatePath;
    }

    /**
     * Tests if the current workbench selection is a suitable container to use.
     */

    private void initialize()
    {
    }

    private void updateStatus(final String message)
    {
        this.setErrorMessage(message);
        this.setPageComplete(message == null);
    }
}
