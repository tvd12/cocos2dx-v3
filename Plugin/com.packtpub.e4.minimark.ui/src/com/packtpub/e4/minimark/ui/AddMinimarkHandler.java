package com.packtpub.e4.minimark.ui;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Iterator;
import java.util.List;

import org.eclipse.core.commands.AbstractHandler;
import org.eclipse.core.commands.ExecutionEvent;
import org.eclipse.core.commands.ExecutionException;
import org.eclipse.core.commands.IHandler;
import org.eclipse.core.commands.IHandlerListener;
import org.eclipse.core.resources.IProject;
import org.eclipse.core.resources.IProjectDescription;
import org.eclipse.core.runtime.CoreException;
import org.eclipse.jface.viewers.ISelection;
import org.eclipse.jface.viewers.IStructuredSelection;
import org.eclipse.ui.handlers.HandlerUtil;

public class AddMinimarkHandler extends AbstractHandler {

	@Override
	public Object execute(ExecutionEvent event) throws ExecutionException {
		ISelection sel = HandlerUtil.getCurrentSelection(event);
		if(sel instanceof IStructuredSelection) {
			Iterator<?> it = ((IStructuredSelection)sel).iterator();
			while(it.hasNext()) {
				Object object = (Object)it.next();
				if(object instanceof IProject) {
					try {
						this.addProjectNature((IProject) object, MinimarkNature.ID);
					} catch(CoreException e) {
						throw new ExecutionException("Failed to set nature on "
								+ object, e);
					}
				}
			}
		}
		return null;
	}

	private void addProjectNature(IProject project, String nature) 
		throws CoreException {
		IProjectDescription description = project.getDescription();
		List<String> natures = new ArrayList<String>(
				Arrays.asList(description.getNatureIds()));
		if(!natures.contains(natures)) {
			natures.add(nature);
			description.setNatureIds(natures.toArray(new String[0]));
			project.setDescription(description, null);
		}
		
	}


}
