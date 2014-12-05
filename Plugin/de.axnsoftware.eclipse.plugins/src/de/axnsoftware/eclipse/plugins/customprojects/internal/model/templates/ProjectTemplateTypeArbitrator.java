package de.axnsoftware.eclipse.plugins.customprojects.internal.model.templates;



public class ProjectTemplateTypeArbitrator
{
    private static ProjectTemplateTypeArbitrator instance;

    public static ProjectTemplateTypeArbitrator getInstance()
    {
        if (ProjectTemplateTypeArbitrator.instance == null)
        {
            ProjectTemplateTypeArbitrator.instance = new ProjectTemplateTypeArbitrator();
        }
        return ProjectTemplateTypeArbitrator.instance;
    }

    public EProjectTemplateType getProjectTemplateType()
    {
        throw new RuntimeException("not implemented yet.");
    }
}
