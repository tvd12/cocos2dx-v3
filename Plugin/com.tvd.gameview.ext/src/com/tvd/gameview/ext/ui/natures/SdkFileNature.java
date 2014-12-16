/**
 * Copyright (c) 2014 Dung Ta Van. All rights reserved.
 * 
 * This file is part of com.tvd.gameview.ext.
 * com.tvd.gameview.ext is free eclipse plug-in: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * com.tvd.gameview.ext is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with com.tvd.gameview.ext.  If not, see <http://www.gnu.org/licenses/>.
 */

package com.tvd.gameview.ext.ui.natures;

import org.eclipse.core.resources.ICommand;
import org.eclipse.core.resources.IProject;
import org.eclipse.core.resources.IProjectDescription;
import org.eclipse.core.resources.IProjectNature;
import org.eclipse.core.runtime.CoreException;
import org.eclipse.core.runtime.IProgressMonitor;
import org.eclipse.core.runtime.NullProgressMonitor;
import org.eclipse.core.runtime.SubProgressMonitor;
import org.eclipse.jdt.core.JavaCore;

import com.tvd.gameview.ext.ui.builder.SdkPropertiesFileBuilder;
import com.tvd.gameview.ext.ui.builder.SdkXMLFileBuilder;

public class SdkFileNature implements IProjectNature {
	
	@Override
	public void configure() throws CoreException {
		System.out.println("SdkXMLFileNature::configure");
		configureXMLFileBuilder(mProject);
		configurePropertiesFileBuilder(mProject);
	}

	@Override
	public void deconfigure() throws CoreException {
		System.out.println("SdkXMLFileNature::deconfigure");
		removeBuilder(mProject, SdkXMLFileBuilder.ID);
		removeBuilder(mProject, SdkPropertiesFileBuilder.ID);
	}
	
	/**
     * Adds the Android Nature and the Java Nature to the project if it doesn't
     * already have them.
     *
     * @param project An existing or new project to update
     * @param monitor An optional progress monitor. Can be null.
     * @throws CoreException if fails to change the nature.
     */
    public static synchronized void setupProjectNatures(IProject project,
            IProgressMonitor monitor) throws CoreException {
        if (project == null || !project.isOpen()) return;
        if (monitor == null) monitor = new NullProgressMonitor();

        // Add the natures. We need to add the Java nature first, so it adds its builder to the
        // project first. This way, when the android nature is added, we can control where to put
        // the android builders in relation to the java builder.
        // Adding the java nature after the android one, would place the java builder before the
        // android builders.
        addNatureToProjectDescription(project, JavaCore.NATURE_ID, monitor);
        addNatureToProjectDescription(project, SdkFileNature.ID, monitor);
    }
    
    /**
     * Add the specified nature to the specified project. The nature is only
     * added if not already present.
     * <p/>
     * Android Natures are always inserted at the beginning of the list of natures in order to
     * have the jdt views/dialogs display the proper icon.
     *
     * @param project The project to modify.
     * @param natureId The Id of the nature to add.
     * @param monitor An existing progress monitor.
     * @throws CoreException if fails to change the nature.
     */
    private static void addNatureToProjectDescription(IProject project,
            String natureId, IProgressMonitor monitor) throws CoreException {
        if (!project.hasNature(natureId)) {

            IProjectDescription description = project.getDescription();
            String[] natures = description.getNatureIds();
            String[] newNatures = new String[natures.length + 1];

            // Android natures always come first.
            if (natureId.equals(SdkFileNature.ID)) {
                System.arraycopy(natures, 0, newNatures, 1, natures.length);
                newNatures[0] = natureId;
            } else {
                System.arraycopy(natures, 0, newNatures, 0, natures.length);
                newNatures[natures.length] = natureId;
            }

            description.setNatureIds(newNatures);
            project.setDescription(description, new SubProgressMonitor(monitor, 10));
        }
    }

	/**
     * Removes a builder from the project.
     * @param project The project to remove the builder from.
     * @param id The String ID of the builder to remove.
     * @return true if the builder was found and removed.
     * @throws CoreException
     */
    public static boolean removeBuilder(IProject project, String id) throws CoreException {
        IProjectDescription description = project.getDescription();
        ICommand[] commands = description.getBuildSpec();
        for (int i = 0; i < commands.length; ++i) {
            if (id.equals(commands[i].getBuilderName())) {
                ICommand[] newCommands = new ICommand[commands.length - 1];
                System.arraycopy(commands, 0, newCommands, 0, i);
                System.arraycopy(commands, i + 1, newCommands, i, commands.length - i - 1);
                description.setBuildSpec(newCommands);
                project.setDescription(description, null);
                return true;
            }
        }

        return false;
    }
	
    /**
     * Adds the ResourceManagerBuilder, if its not already there. It'll insert
     * itself as the first builder.
     * @throws CoreException
     *
     */
    public static void configureXMLFileBuilder(IProject project)
            throws CoreException {
        // get the builder list
        IProjectDescription desc = project.getDescription();
        ICommand[] commands = desc.getBuildSpec();

        // look for the builder in case it's already there.
        for (int i = 0; i < commands.length; ++i) {
            if (SdkXMLFileBuilder.ID.equals(commands[i].getBuilderName())) {
                return;
            }
        }

        // it's not there, lets add it at the beginning of the builders
        ICommand[] newCommands = new ICommand[commands.length + 1];
        System.arraycopy(commands, 0, newCommands, 1, commands.length);
        ICommand command = desc.newCommand();
        command.setBuilderName(SdkXMLFileBuilder.ID);
        newCommands[0] = command;
        desc.setBuildSpec(newCommands);
        project.setDescription(desc, null);
    }

    /**
     * Adds the PreCompilerBuilder if its not already there. It'll check for
     * presence of the ResourceManager and insert itself right after.
     * @param project
     * @throws CoreException
     */
    public static void configurePropertiesFileBuilder(IProject project)
            throws CoreException {
        // get the builder list
        IProjectDescription desc = project.getDescription();
        ICommand[] commands = desc.getBuildSpec();

        // look for the builder in case it's already there.
        for (int i = 0; i < commands.length; ++i) {
            if (SdkPropertiesFileBuilder.ID.equals(commands[i].getBuilderName())) {
                return;
            }
        }

        // we need to add it after the resource manager builder.
        // Let's look for it
        int index = -1;
        for (int i = 0; i < commands.length; ++i) {
            if (SdkXMLFileBuilder.ID.equals(commands[i].getBuilderName())) {
                index = i;
                break;
            }
        }

        // we're inserting after
        index++;

        // do the insertion

        // copy the builders before.
        ICommand[] newCommands = new ICommand[commands.length + 1];
        System.arraycopy(commands, 0, newCommands, 0, index);

        // insert the new builder
        ICommand command = desc.newCommand();
        command.setBuilderName(SdkPropertiesFileBuilder.ID);
        newCommands[index] = command;

        // copy the builder after
        System.arraycopy(commands, index, newCommands, index + 1, commands.length-index);

        // set the new builders in the project
        desc.setBuildSpec(newCommands);
        project.setDescription(desc, null);
    }
    
	@Override
	public IProject getProject() {
		return mProject;
	}

	@Override
	public void setProject(IProject project) {
		mProject = project;
	}

	public static final String ID = 
			"com.tvd.gameview.ext.SdkFileNature";
	private IProject mProject;
	
}
