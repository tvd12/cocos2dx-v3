/**
 * Copyright (c) 2014 Dung Ta Van . All rights reserved.
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

package com.tdgc.cocos2dx.popup.creator.file;

import java.io.File;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class FileParser {
	
	public FileParser(String pRootPath) {
		this.mRootPath = pRootPath;
		this.mFilePaths = new ArrayList<String>();
		
	}
	
	private void parseFilePaths(String pFilePath) {
		  File file = new File(pFilePath);
		  if((file.isDirectory() || pFilePath.contains(".png"))
				  && !pFilePath.contains("spam")) {
			  String end = pFilePath.substring(
					  pFilePath.lastIndexOf(mRootDirectory)).trim();
			  mFilePaths.add(new String(end));
		  }
		  
		  for(int i = 0 ; file != null && file.isDirectory() && i < file.listFiles().length ; i++) {
			  parseFilePaths(file.listFiles()[i].getAbsolutePath());
		  }
	}
	
	public List<String> getFilePaths(boolean sort) {
		this.mRootDirectory = mRootPath.substring(mRootPath.lastIndexOf("/") + 1);
		parseFilePaths(mRootPath);
		if(sort) {
			Collections.sort(mFilePaths);
		}
		
		return mFilePaths;
	}
	
	public List<String> fetchFilePaths() {
		this.mRootDirectory = mRootPath.substring(mRootPath.lastIndexOf("/") + 1);
		fetchFilePaths(mRootPath);
		Collections.sort(mFilePaths);
		
		return mFilePaths;
	}
	
	private void fetchFilePaths(String pFilePath) {
		  File file = new File(pFilePath);
		  if((file.isDirectory() || pFilePath.contains(".png"))) {
			  String end = pFilePath.substring(
					  pFilePath.lastIndexOf(mRootDirectory)).trim();
			  mFilePaths.add(new String(end));
		  }
		  
		  for(int i = 0 ; file != null && file.isDirectory() && i < file.listFiles().length ; i++) {
			  fetchFilePaths(file.listFiles()[i].getAbsolutePath());
		  }
	}
	
	private String mRootPath;
	private String mRootDirectory;
	private List<String> mFilePaths;
}
