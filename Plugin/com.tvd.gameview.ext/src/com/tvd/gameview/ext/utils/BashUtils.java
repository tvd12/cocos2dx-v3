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
import java.io.InputStreamReader;

public class BashUtils {

	public static void run(String pCommand) {
		Runtime run = Runtime.getRuntime();
		Process pr;
		try {
			pr = run.exec(pCommand);
			pr.waitFor();
			BufferedReader buf = new BufferedReader(
					new InputStreamReader(pr.getInputStream()));
			String line = buf.readLine();
			while ( line != null ) {
			  System.out.println(line);
			  line = buf.readLine();
			}
		} catch (IOException e) {
			e.printStackTrace();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		
		


	}
	
}
