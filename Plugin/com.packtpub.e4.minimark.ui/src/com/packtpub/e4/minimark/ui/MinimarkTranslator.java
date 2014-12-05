package com.packtpub.e4.minimark.ui;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.Reader;
import java.io.Writer;

public class MinimarkTranslator {

	public static void convert(Reader reader, Writer writer) 
			throws IOException {
		BufferedReader lines = new BufferedReader(reader);
	    String line = null;
	    String title = String.valueOf(lines.readLine());
	    writer.write("<html><head><title>");
	    writer.write(title);
	    writer.write("</title></head><body><h1>");
	    writer.write("</h1><p>");
	    while (null != (line = lines.readLine())) {
	      if ("".equals(line)) {
	        writer.write("</p><p>");
	      } else {
	        writer.write(line);
	        writer.write('\n');
	      }
	    }
	    writer.write("</p></body></html>");
	    writer.flush();
	}
	
	public static void main(String[] args) 
			throws IOException {
		convert(new FileReader("input.txt"), 
				new FileWriter("output.txt"));
	}
}
