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

package com.tvd.gameview.ext.utils;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;


public class MessageUtils {

	public static String getString(String pKey) {
		InputStream inputStream = MessageUtils.class
				.getResourceAsStream("/com/message/message.properties");
		return getString(inputStream, pKey);
	}
	
	public static String getGlobalProperty(String pKey) {
		return null;
	}
	
	public static String getString(InputStream pInputStream, String pKey) {
		try {
			InputStreamReader inputStreamReader = new InputStreamReader(pInputStream, "utf-8");
			BufferedReader bufferedReader = new BufferedReader(inputStreamReader);
			String lineContent = bufferedReader.readLine();
			while(lineContent != null) {
				String strs[] = lineContent.split("=");
				if(strs[0].trim().equals(pKey)) {
					return strs[1].trim();
				}
				lineContent = bufferedReader.readLine();
			}
			
			bufferedReader.close();
			inputStreamReader.close();
			pInputStream.close();
		} 
		catch(IOException e) {
			e.printStackTrace();
		} finally {
		}
		return "Default message";
	}
	
}
