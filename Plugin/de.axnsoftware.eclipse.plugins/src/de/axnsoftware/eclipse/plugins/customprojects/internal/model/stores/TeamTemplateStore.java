package de.axnsoftware.eclipse.plugins.customprojects.internal.model.stores;

import java.net.URL;

import de.axnsoftware.eclipse.plugins.customprojects.internal.model.templates.IProjectTemplate;

public class TeamTemplateStore extends AbstractTemplateStore
{
    private AbstractTemplateStore backend;
    private String                checkoutPath;
    private String                exportPath;

    public TeamTemplateStore(final String name, final URL url)
    {
        super(name, url);
    }

    public IProjectTemplate[] enumerateTemplates()
    {
        throw new RuntimeException("not implemented yet.");
    }

    public boolean exists()
    {
        boolean result = false;
        if (this.backend != null)
        {
            result = this.backend.exists();
        }
        if (!result)
        {
            throw new RuntimeException("not implemented yet.");
        }
        return result;
    }

    private boolean repositoryExists()
    {
        throw new RuntimeException("not implemented yet.");
    }
}
