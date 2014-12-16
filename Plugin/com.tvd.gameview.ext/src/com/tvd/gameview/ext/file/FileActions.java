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

package com.tvd.gameview.ext.file;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.ByteArrayInputStream;
import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.List;

import org.eclipse.core.resources.IFile;
import org.eclipse.core.resources.IProject;
import org.eclipse.core.runtime.CoreException;
import org.eclipse.core.runtime.Path;

import com.tvd.gameview.ext.GameViewSdk;
import com.tvd.gameview.ext.constants.Constant;
import com.tvd.gameview.ext.constants.Key;

public class FileActions {
	
	public static String readFromFile(String pFilePath) {
		FileInputStream fstream = null;
		DataInputStream inputStream = null;
		BufferedReader bufferedReader = null;
		StringBuilder builder = new StringBuilder();
		try {
			fstream = new FileInputStream(new File(pFilePath));
			inputStream = new DataInputStream(fstream);
			bufferedReader = new BufferedReader(new InputStreamReader(inputStream));
			
			String lineContent = bufferedReader.readLine();
			while(lineContent != null) {
				builder.append(lineContent).append("\n");
				lineContent = bufferedReader.readLine();
			}
			fstream.close();
			inputStream.close();
			bufferedReader.close();
		} catch(IOException e) {
			e.printStackTrace();
		} finally {

		}
		return builder.toString();
	}
	
	public static String readFromFile(InputStream pInputStream) {
		try {
			InputStreamReader inputStreamReader = new InputStreamReader(pInputStream, "utf-8");
			BufferedReader bufferedReader = new BufferedReader(inputStreamReader);
			String lineContent = bufferedReader.readLine();
			StringBuilder builder = new StringBuilder();
			while(lineContent != null) {
				builder.append(lineContent).append("\n");
				lineContent = bufferedReader.readLine();
			}
			
			bufferedReader.close();
			inputStreamReader.close();
			pInputStream.close();
			
			return builder.toString();
		} 
		catch(IOException e) {
			e.printStackTrace();
		} finally {
		}
		return "";
	}
	
	public static void replaceContent(String pFilePath, String pContent) {
		try {
			
		File file = new File(pFilePath);
		
		//if file doesn't exists, then create it
		if(!file.exists()) {
			file.createNewFile();
		}
		
		FileWriter fileWriter = new FileWriter(file.getAbsoluteFile());
		BufferedWriter bufferedWriter = new BufferedWriter(fileWriter);
		bufferedWriter.write(pContent);
		
		bufferedWriter.close();
		} catch(IOException e) {
			e.printStackTrace();
		}
	}
	
	public static void copyFile(String pSource, String pDesPath) {
	    File in = new File(pSource);
	    File des = new File(pDesPath);
	    if(in.isDirectory() && !des.exists()) {
	    	des.mkdir();
	    } else if(!(des.exists() && des.isDirectory())) {
	    	try {
				FileUtil.copyFile(pSource, pDesPath, true);
			} catch (IOException e) {
				e.printStackTrace();
			}
	    }
	    
	}
	
	public static void copySourceCodeFiles(String pDesPath) {
		String templateRoot = GameViewSdk.getDefault()
				.getPreferenceStore().getString(Key.TEMPLATE_ROOT);
		List<String> filePaths = new FileParser().getFilePaths(templateRoot, 
				Constant.SOURCE_CODE_DIRECTORY);
		
		//to avoid losing data, rename game project
		new File(pDesPath).renameTo(new File(pDesPath + "_old"));
		new File(pDesPath).mkdir(); 
		
		for(int i = 0 ; i < filePaths.size() ; i++) {
			copyFile(templateRoot + "/" + Constant.SOURCE_CODE_DIRECTORY
					+ filePaths.get(i), pDesPath + filePaths.get(i));
		}
	}
	
	/**
	 * 
	 * @param pProject
	 * @param pSrcFolder
	 * @param pDesPath
	 * 
	 * modify from 
	 * copyFiles (File srcFolder, IContainer destFolder) {
    	for (File f: srcFolder.listFiles()) {
	        if (f.isDirectory()) {
	            IFolder newFolder = destFolder.getFolder(new Path(f.getName()));
	            newFolder.create(true, true, null);
	            copyFiles(f, newDest);
	        } else {
	            IFile newFile = project.getFile(new Path(f.getName())));
	            newFile.create(new FileInputStream(f), true, null);
	        }
    	}
	}
	 */
	public static void copyFiles(IProject pProject, File pSrcFolder, 
			String pDesPath) {
		try {
			File files[] = pSrcFolder.listFiles();
			for(int i = 0 ; files != null && i < files.length ; i++) {
				File file = files[i];
				if(file.getName().endsWith(".xml")
	    				|| file.getName().endsWith(".DS_Store")) {
					continue;
				}
				
				if(file.isDirectory()) {
//					IFolder newFolder = pDesFolder.getFolder(new Path(file.getName()));
//					newFolder.create(true, true, null);
//					copyFiles(pProject, file, newFolder.getParent());
					
				} else {
					IFile newFile = pProject.getFile(
							new Path(pDesPath + "/" + file.getName()));
					//IResource.FORCE
					if(newFile.exists()) {
						newFile.setContents(new FileInputStream(file), true, false, null);
					} else {
						newFile.create(new FileInputStream(file), true, null);
					}
				}
			}
		}
		catch (CoreException e) {
			e.printStackTrace();
		}
		catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public static void copyFiles(IProject pProject, String pSrcFolder, 
			String pDesFolder) {
		FileActions.copyFiles(pProject, new File(pSrcFolder), pDesFolder);
	}
	
	public static void writeToFile(IProject pProject, String pFolder, 
			String pFile, String pContent) {
		StringBuilder builder = new StringBuilder();
		try {
			IFile newFile = pProject.getFile(
					new Path(pFolder + "/" + pFile));
			File file = newFile.getLocation().toFile();
			if(file.exists()) {
				builder.append(readFromFile(file.getAbsolutePath()))
					.append("\n");
			}
			builder.append(pContent);
			InputStream inputStream = new ByteArrayInputStream(pContent.getBytes());
			if(newFile.exists()) {
				newFile.setContents(inputStream, true, false, null);
			} else {
				newFile.create(inputStream, true, null);
			}
		} catch (CoreException e) {
			e.printStackTrace();
		}
	}
}
