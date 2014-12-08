package de.axnsoftware.eclipse.plugins.customprojects.internal.model.templates;

import java.util.Arrays;
import java.util.Comparator;


public class ProjectTemplateSorter
{
    private static class ProjectTemplateComparator implements
            Comparator<IProjectTemplate>
    {
        private static Comparator<IProjectTemplate> instance;

        public static Comparator<IProjectTemplate> getInstance()
        {
            if (ProjectTemplateComparator.instance == null)
            {
                ProjectTemplateComparator.instance = new ProjectTemplateComparator();
            }
            return ProjectTemplateComparator.instance;
        }

        public int compare(final IProjectTemplate o1, final IProjectTemplate o2)
        {
            return o1.getName().compareTo(o2.getName());
        }
    }

    private static ProjectTemplateSorter instance;

    public static ProjectTemplateSorter getInstance()
    {
        if (ProjectTemplateSorter.instance == null)
        {
            ProjectTemplateSorter.instance = new ProjectTemplateSorter();
        }
        return ProjectTemplateSorter.instance;
    }

    public IProjectTemplate[] sort(final IProjectTemplate[] templates)
    {
        final Comparator<IProjectTemplate> comparator = ProjectTemplateComparator
                .getInstance();
        Arrays.<IProjectTemplate> sort(templates, comparator);
        return templates;
    }
}
