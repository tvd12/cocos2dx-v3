package de.axnsoftware.eclipse.plugins.customprojects.internal.model.factories;

import java.net.URL;

import de.axnsoftware.eclipse.plugins.customprojects.internal.model.templates.IProjectTemplate;

public interface IProjectTemplateFactory
{
    public IProjectTemplate createNewProjectTemplate(final URL url);
}
