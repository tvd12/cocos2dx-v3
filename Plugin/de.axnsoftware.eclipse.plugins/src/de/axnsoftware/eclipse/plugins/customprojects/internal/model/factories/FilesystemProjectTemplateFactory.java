package de.axnsoftware.eclipse.plugins.customprojects.internal.model.factories;

import java.net.URL;

import de.axnsoftware.eclipse.plugins.customprojects.internal.model.templates.IProjectTemplate;

public class FilesystemProjectTemplateFactory implements IProjectTemplateFactory
{
    private static IProjectTemplateFactory instance;

    public static IProjectTemplateFactory getInstance()
    {
        if (FilesystemProjectTemplateFactory.instance == null)
        {
            FilesystemProjectTemplateFactory.instance = new FilesystemProjectTemplateFactory();
        }
        return FilesystemProjectTemplateFactory.instance;
    }

    public IProjectTemplate createNewProjectTemplate(final URL url)
    {
        throw new RuntimeException("not implemented yet.");
    }
}
