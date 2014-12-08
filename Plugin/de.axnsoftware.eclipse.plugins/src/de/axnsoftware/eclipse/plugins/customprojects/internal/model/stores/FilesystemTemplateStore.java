package de.axnsoftware.eclipse.plugins.customprojects.internal.model.stores;

import java.io.File;
import java.io.FilenameFilter;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.ArrayList;

import de.axnsoftware.eclipse.plugins.customprojects.internal.model.factories.IProjectTemplateFactory;
import de.axnsoftware.eclipse.plugins.customprojects.internal.model.factories.ProjectTemplateAbstractFactory;
import de.axnsoftware.eclipse.plugins.customprojects.internal.model.templates.IProjectTemplate;

public class FilesystemTemplateStore extends AbstractTemplateStore
{
    public FilesystemTemplateStore(final FilenameFilter filter,
            final String name, final URL url)
    {
        super(filter, name, url);
    }

    public FilesystemTemplateStore(final String name, final URL url)
    {
        super(name, url);
    }

    @Override
    public IProjectTemplate[] enumerateTemplates()
    {
        final ArrayList<IProjectTemplate> result = new ArrayList<IProjectTemplate>();
        final IProjectTemplateFactory factory = ProjectTemplateAbstractFactory
                .getInstance();
        final File store = new File(this.getUrl().getPath());
        if (store.exists() && store.isDirectory())
        {
            for (final File candidate : store.listFiles())
            {
                if (candidate.isDirectory())
                {
                    try
                    {
                        final URL url = new URL("file://"
                                + candidate.getAbsolutePath());
                        result.add(factory.createNewProjectTemplate(url));
                    }
                    catch (final MalformedURLException e)
                    {
                        // must never happen
                        throw new RuntimeException(e);
                    }
                }
            }
        }

        return result.toArray(new IProjectTemplate[] {});
    }

    @Override
    public boolean exists()
    {
        final File store = new File(this.getUrl().getPath());
        return store.exists();
    }
}
