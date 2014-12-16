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

import java.io.File;
import java.io.FileInputStream;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.Reader;
import java.net.URL;

import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;

import org.eclipse.core.resources.IFile;
import org.xml.sax.ErrorHandler;
import org.xml.sax.InputSource;
import org.xml.sax.XMLReader;
import org.xml.sax.helpers.DefaultHandler;

import com.tdgc.cocos2dx.popup.creator.log.Log;
import com.tdgc.cocos2dx.popup.creator.model.View;

public class XmlFetcher {
	
	public XmlFetcher() {
		this.mHandler = new XmlFileParser();
		this.mErrorHandler = new XMLErrorHandler();
	}

	public void fetchData(String pOutputPath) {
		try {
			File file = new File(pOutputPath);
			InputStream inputStream = new FileInputStream(file);
			Reader reader = new InputStreamReader(inputStream, "UTF-8");
			InputSource inputSource = new InputSource(reader);
			inputSource.setEncoding("UTF-8");
			
			URL url = getClass().getResource("/com/tvd/xml/view_2_0.xsd");
			
			SAXParserFactory spf = SAXParserFactory.newInstance();
			spf.setNamespaceAware(true);
			spf.setValidating(true);
			SAXParser sp = spf.newSAXParser();
			sp.setProperty( "http://java.sun.com/xml/jaxp/properties/schemaLanguage", 
                    "http://www.w3.org/2001/XMLSchema");
			sp.setProperty( "http://java.sun.com/xml/jaxp/properties/schemaSource", 
					url.toURI().toString());
			XMLReader xr = sp.getXMLReader();
			xr.setContentHandler(mHandler);
			xr.setErrorHandler(mErrorHandler);
			xr.parse(inputSource);
			
		} catch (Exception e) {
			Log.e(e);
		}
		
	}
	
	//tvd update
	public void fetchData(IFile xmlFile) {
		try {
			Reader reader = new InputStreamReader(xmlFile.getContents(), xmlFile.getCharset());
			InputSource inputSource = new InputSource(reader);
			inputSource.setEncoding(xmlFile.getCharset());
			
			SAXParserFactory spf = SAXParserFactory.newInstance();
			spf.setNamespaceAware(true);
			spf.setValidating(true);
			
			SAXParser sp = spf.newSAXParser();
			sp.setProperty( "http://java.sun.com/xml/jaxp/properties/schemaLanguage", 
                    "http://www.w3.org/2001/XMLSchema");
			
			URL url = getClass().getResource("/com/tvd/xml/view_2_0.xsd");
			sp.setProperty( "http://java.sun.com/xml/jaxp/properties/schemaSource", 
					url.toURI().toString());
			
			XMLReader xr = sp.getXMLReader();
			xr.setContentHandler(mHandler);
			xr.setErrorHandler(mErrorHandler);
			xr.parse(inputSource);
			
		} catch (Exception e) {
			Log.e(e);
		}
		
	}
	
	public View fetchView(String pOutputPath) {
		fetchData(pOutputPath);
		View view = ((XmlFileParser)mHandler).getView();
		view.setXmlFilePath(pOutputPath);
		
		return view;
	}
	
	public View fetchView(IFile xmlFile) {
		fetchData(xmlFile);
		View view = ((XmlFileParser)mHandler).getView();
		view.setXmlFilePath(xmlFile.getProjectRelativePath().toString());
		view.setXmlFile(xmlFile);
		return view;
	}
	
	public int getWarningCount() {
		return ((XMLErrorHandler)mErrorHandler).getWarningCount();
	}
	
	public int getFatalErrorCount() {
		return ((XMLErrorHandler)mErrorHandler).getFatalErrorCount();
	}
	
	public int getNonFatalErrorCount() {
		return ((XMLErrorHandler)mErrorHandler).getNonFatalErrorCount();
	}
	
	public boolean isError() {
		return getFatalErrorCount() > 0
				|| getNonFatalErrorCount() > 0;
	}
	
	protected DefaultHandler mHandler;
	protected ErrorHandler mErrorHandler;
	
}
