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

package com.tdgc.cocos2dx.popup.creator.xml;

import org.xml.sax.SAXException;
import org.xml.sax.SAXParseException;
import org.xml.sax.helpers.DefaultHandler;

public class XMLErrorHandler extends DefaultHandler {
	public XMLErrorHandler() {
		mWarningCount = 0;
		mFatalErrorCount = 0;
		mNonFatalErrorCount = 0;
	}
	
	@Override
	public void fatalError(SAXParseException exception) 
			throws SAXException {
		System.out.println("**Parsing Fatal Error**\n" + "Line: " +
				exception.getLineNumber( ) + "\n" + "URI: "+
				                              exception.getSystemId( ) + "\n" +
				                           "  Message: " +
				                              exception.getMessage( ));
		mFatalErrorCount ++;
	}
	
	@Override
	public void error(SAXParseException exception) 
			throws SAXException {
		System.out.println("**Parsing Non-Fatal Error**\n" + "Line: " +
				exception.getLineNumber( ) + "\n" + "URI: "+
				                              exception.getSystemId( ) + "\n" +
				                           "  Message: " +
				                              exception.getMessage( ));
		mNonFatalErrorCount ++;
	}
	
	@Override
	public void warning(SAXParseException exception)
			throws SAXException{
		System.out.println("**Parsing Warning**\n" + "Line: " +
				exception.getLineNumber( ) + "\n" + "URI: "+
				                              exception.getSystemId( ) + "\n" +
				                           "  Message: " +
				                              exception.getMessage( ));
		mWarningCount ++;
	}
	
	public int getWarningCount() {
		return this.mWarningCount;
	}
	
	public int getFatalErrorCount() {
		return mFatalErrorCount;
	}
	
	public int getNonFatalErrorCount() {
		return this.mNonFatalErrorCount;
	}
	
	private int mWarningCount;
	private int mFatalErrorCount;
	private int mNonFatalErrorCount;
	
}
