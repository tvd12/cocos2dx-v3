package de.axnsoftware.eclipse.plugins.customprojects.internal.model.stores;

import java.io.FilenameFilter;
import java.net.URL;

public abstract class AbstractTemplateStore implements ITemplateStore
{
    private String               name;
    private URL                  url;
    private final FilenameFilter filter;

    public AbstractTemplateStore(final FilenameFilter filter,
            final String name, final URL url)
    {
        this.filter = filter;
        this.setName(name);
        this.setUrl(url);
    }

    protected AbstractTemplateStore(final String name, final URL url)
    {
        this(null, name, url);
    }

    public FilenameFilter getFilter()
    {
        return this.filter;
    }

    public String getName()
    {
        return this.name;
    }

    public URL getUrl()
    {
        return this.url;
    }

    public void setName(final String name)
    {
        this.name = name;
    }

    public void setUrl(final URL url)
    {
        this.url = url;
    }
}
