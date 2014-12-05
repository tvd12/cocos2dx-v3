package de.axnsoftware.eclipse.plugins.customprojects.internal.model.stores;

import java.net.URL;

import de.axnsoftware.eclipse.plugins.customprojects.internal.model.templates.IProjectTemplate;

public interface ITemplateStore
{
    public abstract IProjectTemplate[] enumerateTemplates();

    public abstract boolean exists();

    public String getName();

    public URL getUrl();

    public void setName(String name);

    public void setUrl(URL url);
}
