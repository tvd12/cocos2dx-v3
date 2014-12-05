package de.axnsoftware.eclipse.plugins.customprojects.internal.ui.wizards;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStream;

import org.eclipse.core.resources.IContainer;
import org.eclipse.core.resources.IFile;
import org.eclipse.core.resources.IResource;
import org.eclipse.core.resources.IWorkspaceRoot;
import org.eclipse.core.resources.ResourcesPlugin;
import org.eclipse.core.runtime.CoreException;
import org.eclipse.core.runtime.IProgressMonitor;
import org.eclipse.core.runtime.IStatus;
import org.eclipse.core.runtime.Path;
import org.eclipse.core.runtime.Status;
import org.eclipse.jdt.ui.wizards.JavaCapabilityConfigurationPage;
import org.eclipse.jdt.ui.wizards.NewJavaProjectWizardPageOne;
import org.eclipse.jface.viewers.IStructuredSelection;
import org.eclipse.jface.wizard.Wizard;
import org.eclipse.ui.INewWizard;
import org.eclipse.ui.IWorkbench;
import org.eclipse.ui.IWorkbenchPage;
import org.eclipse.ui.IWorkbenchWizard;
import org.eclipse.ui.PartInitException;
import org.eclipse.ui.PlatformUI;
import org.eclipse.ui.ide.IDE;

/**
 * TODO reimplement part of the internals of the java project wizard reuse
 * existing java project wizard pages
 */

public class NewCustomJavaProjectWizard extends Wizard implements INewWizard
{
    private NewJavaProjectWizardPageOne     javaWizardPage1;
    private JavaCapabilityConfigurationPage javaWizardPage2;
    private NewCustomJavaProjectWizardPage1           page1;

    // private NewProjectWizardPage2 page2;

    /**
     * Constructor for SampleNewWizard.
     */
    public NewCustomJavaProjectWizard()
    {
        super();
        this.setNeedsProgressMonitor(true);
    }

    /**
     * Adding the page to the wizard.
     */

    @Override
    public void addPages()
    {
        this.javaWizardPage1 = new NewJavaProjectWizardPageOne();
        this.addPage(this.javaWizardPage1);
        this.javaWizardPage2 = new JavaCapabilityConfigurationPage();
        this.addPage(this.javaWizardPage2);
    }

    /**
     * The worker method. It will find the container, create the file if missing
     * or just replace its contents, and open the editor on the newly created
     * file.
     */

    private void doFinish(final String containerName, final String fileName,
            final IProgressMonitor monitor) throws CoreException
    {
        // create a sample file
        monitor.beginTask("Creating " + fileName, 2);
        final IWorkspaceRoot root = ResourcesPlugin.getWorkspace().getRoot();
        final IResource resource = root.findMember(new Path(containerName));
        if (!resource.exists() || !(resource instanceof IContainer))
        {
            this.throwCoreException("Container \"" + containerName
                    + "\" does not exist.");
        }
        final IContainer container = (IContainer) resource;
        final IFile file = container.getFile(new Path(fileName));
        try
        {
            final InputStream stream = this.openContentStream();
            if (file.exists())
            {
                file.setContents(stream, true, true, monitor);
            }
            else
            {
                file.create(stream, true, monitor);
            }
            stream.close();
        }
        catch (final IOException e)
        {
        }
        monitor.worked(1);
        monitor.setTaskName("Opening file for editing...");
        this.getShell().getDisplay().asyncExec(new Runnable()
        {
            public void run()
            {
                final IWorkbenchPage page = PlatformUI.getWorkbench()
                        .getActiveWorkbenchWindow().getActivePage();
                try
                {
                    IDE.openEditor(page, file, true);
                }
                catch (final PartInitException e)
                {
                }
            }
        });
        monitor.worked(1);
    }

    /**
     * We will accept the selection in the workbench to see if we can initialize
     * from it.
     * 
     * @see IWorkbenchWizard#init(IWorkbench, IStructuredSelection)
     */
    public void init(final IWorkbench workbench,
            final IStructuredSelection selection)
    {
        // this.selection = selection;
    }

    /**
     * We will initialize file contents with a sample text.
     */

    private InputStream openContentStream()
    {
        final String contents = "This is the initial file contents for *.java file that should be word-sorted in the Preview page of the multi-page editor";
        return new ByteArrayInputStream(contents.getBytes());
    }

    /**
     * This method is called when 'Finish' button is pressed in the wizard. We
     * will create an operation and run it using wizard as execution context.
     */
    @Override
    public boolean performFinish()
    {
        // final String containerName = this.page.getContainerName();
        // final String fileName = this.page.getFileName();
        // final IRunnableWithProgress op = new IRunnableWithProgress()
        // {
        // public void run(final IProgressMonitor monitor)
        // throws InvocationTargetException
        // {
        // try
        // {
        // NewProjectWizard.this.doFinish(containerName, fileName,
        // monitor);
        // }
        // catch (final CoreException e)
        // {
        // throw new InvocationTargetException(e);
        // }
        // finally
        // {
        // monitor.done();
        // }
        // }
        // };
        // try
        // {
        // this.getContainer().run(true, false, op);
        // }
        // catch (final InterruptedException e)
        // {
        // return false;
        // }
        // catch (final InvocationTargetException e)
        // {
        // final Throwable realException = e.getTargetException();
        // MessageDialog.openError(this.getShell(), "Error",
        // realException.getMessage());
        // return false;
        // }
        return true;
    }

    private void throwCoreException(final String message) throws CoreException
    {
        final IStatus status = new Status(IStatus.ERROR,
                "de.axnsoftware.eclipse.osx.javafiletemplates", IStatus.OK,
                message, null);
        throw new CoreException(status);
    }
}
