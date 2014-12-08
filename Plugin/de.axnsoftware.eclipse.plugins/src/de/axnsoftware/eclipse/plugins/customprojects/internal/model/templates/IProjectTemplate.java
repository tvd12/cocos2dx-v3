package de.axnsoftware.eclipse.plugins.customprojects.internal.model.templates;

import java.io.InputStream;
import java.net.URL;

import de.axnsoftware.eclipse.plugins.customprojects.internal.model.content.ProjectTemplateContent;
import de.axnsoftware.eclipse.plugins.customprojects.internal.model.stores.ITemplateStore;

public interface IProjectTemplate
{
    public ProjectTemplateContent[] enumerateContents();

    public InputStream fetchContent(final URL url);

    public String getName();

    public ITemplateStore getStore();

    public URL getUrl();
}
