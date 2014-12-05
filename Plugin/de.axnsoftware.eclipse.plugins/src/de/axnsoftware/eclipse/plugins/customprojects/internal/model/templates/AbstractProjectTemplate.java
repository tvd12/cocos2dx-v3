package de.axnsoftware.eclipse.plugins.customprojects.internal.model.templates;

import java.net.URL;

import de.axnsoftware.eclipse.plugins.customprojects.internal.model.stores.ITemplateStore;

public abstract class AbstractProjectTemplate implements IProjectTemplate
{
    private final String         name;
    private final ITemplateStore store;
    private final URL            url;

    protected AbstractProjectTemplate(final String name,
            final ITemplateStore store, final URL url)
    {
        this.name = name;
        this.store = store;
        this.url = url;
    }

    public final String getName()
    {
        return this.name;
    }

    public final ITemplateStore getStore()
    {
        return this.store;
    }

    public final URL getUrl()
    {
        return this.url;
    }
}
