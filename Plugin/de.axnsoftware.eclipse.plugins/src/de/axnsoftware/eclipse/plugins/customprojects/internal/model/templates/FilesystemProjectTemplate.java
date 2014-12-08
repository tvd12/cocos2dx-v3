package de.axnsoftware.eclipse.plugins.customprojects.internal.model.templates;

import java.io.InputStream;
import java.net.URL;

import de.axnsoftware.eclipse.plugins.customprojects.internal.model.content.ProjectTemplateContent;
import de.axnsoftware.eclipse.plugins.customprojects.internal.model.stores.ITemplateStore;

public class FilesystemProjectTemplate extends AbstractProjectTemplate
{
    public FilesystemProjectTemplate(final String name,
            final ITemplateStore store, final URL url)
    {
        super(name, store, url);
    }

    public ProjectTemplateContent[] enumerateContents()
    {
        throw new RuntimeException("not implemented yet.");
    }

    public InputStream fetchContent(final URL url)
    {
        // TODO Auto-generated method stub
        return null;
    }

    public URL getURL()
    {
        // TODO Auto-generated method stub
        return null;
    }
}
