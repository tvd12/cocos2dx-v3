package de.axnsoftware.eclipse.plugins.customprojects.internal.model.factories;

import java.net.URL;

import de.axnsoftware.eclipse.plugins.customprojects.internal.model.templates.IProjectTemplate;

public class ProjectTemplateAbstractFactory implements IProjectTemplateFactory
{
    private static ProjectTemplateAbstractFactory instance;

    public static IProjectTemplateFactory getInstance()
    {
        if (ProjectTemplateAbstractFactory.instance == null)
        {
            ProjectTemplateAbstractFactory.instance = new ProjectTemplateAbstractFactory();
        }
        return ProjectTemplateAbstractFactory.instance;
    }

    public IProjectTemplate createNewProjectTemplate(final URL url)
    {
        IProjectTemplateFactory factory = null;
        final String protocol = url.getProtocol();
        if ("file://".equals(protocol))
        {
            factory = FilesystemProjectTemplateFactory.getInstance();
        }

        if (factory == null)
        {
            throw new RuntimeException("unsupported protocol: '" + protocol
                    + "'.");
        }

        return factory.createNewProjectTemplate(url);
    }
}
