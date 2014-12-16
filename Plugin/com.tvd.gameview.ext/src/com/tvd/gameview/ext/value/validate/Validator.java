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

package com.tvd.gameview.ext.value.validate;

public class Validator {
	
	public static boolean isNumeric(String str) {
		//match a number with optional '-' and decimal.
		boolean valid = str.matches("-?\\d+(\\.\\d+)?");
		if(!valid) {
			System.err.println("ERROR::isNumeric " 
					+ str + " is invalid value");
		}
		
		return valid;
	}
	
	public static boolean isValidDoubleValueString(String doubleValue) {
		boolean valid = true;
		if(doubleValue == null || doubleValue.equals("")
				|| !doubleValue.contains(",")) {
			valid = false;
		} else {
			String values[] = doubleValue.split(",");
			if(values.length < 2) {
				valid = false;
			} else {
				values[0] = values[0].trim();
				values[1] = values[1].trim();
				if(values[0].equals("") || !isNumeric(values[0])) {
					valid = false;
				}
				if(values[1].equals("") || !isNumeric(values[1])) {
					valid = false;
				}
			}
		}
		
		if(!valid) {
			System.err.println("ERROR::validateDoubleValueString " 
					+ doubleValue + " is invalid value");
		}
		return valid;
	}
}
