package de.axnsoftware.eclipse.plugins.customprojects.internal.model.templates;

import java.io.InputStream;
import java.net.URL;

import de.axnsoftware.eclipse.plugins.customprojects.internal.model.content.ProjectTemplateContent;
import de.axnsoftware.eclipse.plugins.customprojects.internal.model.stores.ITemplateStore;

public class TeamProjectTemplate extends AbstractProjectTemplate
{
    protected TeamProjectTemplate(final String name,
            final ITemplateStore store, final URL url)
    {
        super(name, store, url);
        // TODO Auto-generated constructor stub
    }

    public ProjectTemplateContent[] enumerateContents()
    {
        // TODO Auto-generated method stub
        return null;
    }

    public InputStream fetchContent(final URL url)
    {
        // TODO Auto-generated method stub
        return null;
    }
}
