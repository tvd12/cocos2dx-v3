package de.axnsoftware.eclipse.plugins.customprojects.internal.model.content;


public class ProjectTemplateContent
{
    private final String                      path;
    private final EProjectTemplateContentType type;

    public ProjectTemplateContent(final String path,
            final EProjectTemplateContentType type)
    {
        this.path = path;
        this.type = type;
    }

    public String getPath()
    {
        return this.path;
    }

    public EProjectTemplateContentType getType()
    {
        return this.type;
    }
}
