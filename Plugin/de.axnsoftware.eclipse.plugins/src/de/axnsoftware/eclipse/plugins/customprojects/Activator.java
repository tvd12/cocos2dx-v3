package de.axnsoftware.eclipse.plugins.customprojects;

import org.eclipse.jface.resource.ImageDescriptor;
import org.eclipse.ui.plugin.AbstractUIPlugin;
import org.osgi.framework.BundleContext;

/**
 * The activator class controls the plug-in life cycle
 */
public class Activator extends AbstractUIPlugin
{
    // The plug-in ID
    public static final String PLUGIN_ID = "de.axnsoftware.eclipse.plugins.customprojects"; //$NON-NLS-1$

    // The shared instance
    private static Activator   plugin;

    /**
     * Returns the shared instance
     * 
     * @return the shared instance
     */
    public static Activator getDefault()
    {
        return Activator.plugin;
    }

    /**
     * Returns an image descriptor for the image file at the given plug-in
     * relative path
     * 
     * @param path
     *            the path
     * @return the image descriptor
     */
    public static ImageDescriptor getImageDescriptor(final String path)
    {
        return AbstractUIPlugin.imageDescriptorFromPlugin(Activator.PLUGIN_ID,
                path);
    }

    /**
     * The constructor
     */
    public Activator()
    {
    }

    /*
     * (non-Javadoc)
     * 
     * @see
     * org.eclipse.ui.plugin.AbstractUIPlugin#start(org.osgi.framework.BundleContext
     * )
     */
    @Override
    public void start(final BundleContext context) throws Exception
    {
        super.start(context);
        Activator.plugin = this;
    }

    /*
     * (non-Javadoc)
     * 
     * @see
     * org.eclipse.ui.plugin.AbstractUIPlugin#stop(org.osgi.framework.BundleContext
     * )
     */
    @Override
    public void stop(final BundleContext context) throws Exception
    {
        Activator.plugin = null;
        super.stop(context);
    }
}
