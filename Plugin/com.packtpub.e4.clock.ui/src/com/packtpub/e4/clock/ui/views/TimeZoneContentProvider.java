package com.packtpub.e4.clock.ui.views;

import java.util.Collection;
import java.util.Map;

import org.eclipse.jface.viewers.ITreeContentProvider;
import org.eclipse.jface.viewers.Viewer;

public class TimeZoneContentProvider implements ITreeContentProvider {

	@Override
	public void dispose() {

	}

	@Override
	public void inputChanged(Viewer viewer, Object oldInput, Object newInput) {

	}

	@Override
	public Object[] getElements(Object inputElement) {
		if(inputElement instanceof Object[]) {
			return (Object[])inputElement;
		}
		else {
			return new Object[0];
		}
	}

	@SuppressWarnings("rawtypes")
	@Override
	public Object[] getChildren(Object parentElement) {
		if (parentElement instanceof Map) {
	        return ((Map) parentElement).entrySet().toArray();
		} else if (parentElement instanceof Map.Entry) {
	        return getChildren(((Map.Entry)parentElement).getValue());
		} else if (parentElement instanceof Collection) {
	        return ((Collection) parentElement).toArray();
	    } else {
	        return new Object[0];
	    }
	}
	
	@Override
	public Object getParent(Object element) {
		return null;
	}

	@SuppressWarnings("rawtypes")
	@Override
	public boolean hasChildren(Object element) {
		if (element instanceof Map) {
			return !((Map) element).isEmpty();
	    } else if (element instanceof Map.Entry) {
	        return hasChildren(((Map.Entry)element).getValue());
	    } else if (element instanceof Collection) {
	        return !((Collection) element).isEmpty();
	    } else {
	    	return false;
	    }
	}

}
