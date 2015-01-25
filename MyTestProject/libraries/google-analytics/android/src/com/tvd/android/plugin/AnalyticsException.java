/**
 * Copyright (c) 2014 Dung Ta Van. All rights reserved.
 *
 * This file is part of Google analytics plugin.
 * Google analytics plugin is free library: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Google analytics plugin is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Google analytics plugin.  If not, see <http://www.gnu.org/licenses/>.
 */

package com.tvd.android.plugin;

public class AnalyticsException extends Exception {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	public AnalyticsException() {
		super("Analytics Exceptions, invalid tracker id");
	}
	
}
