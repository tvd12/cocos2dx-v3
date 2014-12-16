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

package com.tdgc.cocos2dx.popup.creator.model;

import java.util.ArrayList;

import com.tdgc.cocos2dx.popup.creator.constants.Attribute;
import com.tdgc.cocos2dx.popup.creator.constants.ModelType;
import com.tdgc.cocos2dx.popup.creator.constants.Tag;
import com.tdgc.cocos2dx.popup.creator.file.FileUtils;
import com.tdgc.cocos2dx.popup.creator.global.Config;
import com.tdgc.cocos2dx.popup.creator.model.basic.CommonObject;
import com.tdgc.cocos2dx.popup.creator.model.basic.Point;
import com.tdgc.cocos2dx.popup.creator.model.basic.Size;
import com.tdgc.cocos2dx.popup.creator.utils.StringUtils;

public class Table extends CommonObject {

	public Table() {
		super();
		this.mDeclareObjectName = "CCTableView";
		this.mSuffix = "Table";
		this.mType = ModelType.TABLE;
		this.mSuper = Config.getInstance().getDefaultSuper("table");
		this.mAnchorPoint = new Point(0, 0);
		this.mAnchorPointString = this.mAnchorPoint.toString();
		this.mXmlTagName = Tag.TABLE;
		
		this.mTemplateName = "CCTableView";
		this.mTemplateFile = "table.template";
		
		this.mCellGroups = new ArrayList<ItemGroup>();
	}
	
	@Override
	public String implement(boolean pInfunction) {
		StringBuilder builder = new StringBuilder("\n");
		String template = fetchTemplate(pInfunction);
		
		String parentName = Config.getInstance()
				.getDefaultBackgroundOnSupers(mParent.getType());
		if(mParent != null) {
			parentName = mParent.getName();
		}
		template = template.replace("{var_name}", mName)
			.replace("{size_name}", mSizeName)
			.replace("{position_name}", mPositionName)
			.replace("{rows}", "" + mRows)
			.replace("{columns}", "" + mColumns)
			.replace("{tab}", "\t")
			.replace("{parent_name}", parentName)
			.replace("{cell_position_name}", mCellPositionName)
			.replace("{cell_size_name}", mCellSizeName);
		
		builder.append(template);
		
		return builder.toString();
	}
	
	@Override
	public void setPositionName(String pPositionName) {
		super.setPositionName(pPositionName);
		mSizeName = mPositionName.replace("POSITION", "SIZE");
		mCellPositionName = mPositionName.replace("TABLE_POSITION", "CELL_POSITION");
		mCellSizeName = mPositionName.replace("TABLE_POSITION", "CELL_SIZE");
	}
	
	@Override
	public String declarePositions() {
		StringBuilder builder = new StringBuilder(super.declarePositions());
		FileUtils fileUtils = new FileUtils();
		String pointTemplate = fileUtils.fetchTemplate(
				getDeclaringPositionTemplateName(), 
				getPostionTemplateFilePath(), getProject());
		String sizeTemplate = fileUtils.fetchTemplate(
				getDeclaringSizeTemplateName(), 
				getSizeTemplateFilePath(), getProject());
		pointTemplate = pointTemplate
				.replace("{var_name}", mCellPositionName)
				.replace("{tab}", "\t");
		builder.append("\n")
			.append(pointTemplate)
			.append(sizeTemplate.replace("{tab}", "\t")
					.replace("{var_name}", mSizeName))
			.append(sizeTemplate.replace("{tab}", "\t")
					.replace("{var_name}", mCellSizeName));
		
		builder.append(mCell.declarePositions());
		
		return builder.toString();
	}
	
	@Override
	public String implementPositions() {
		declarePositions();
		StringBuilder builder = new StringBuilder();
		String cellPositionString = mCell.getPositionString();
		String cellSizeString = mCell.getSizeString();
		
		FileUtils fileUtils = new FileUtils();
		String pointTemplate = fileUtils.fetchTemplate(
				getImplementingPositionTemplateName(), 
				getPostionTemplateFilePath(), getProject());
		
		String sizeTemplate = fileUtils.fetchTemplate(
				getImplementingSizeTemplateName(), 
				getSizeTemplateFilePath(), getProject());
		
		builder.append(pointTemplate.replace("{var_name}", mPositionName)
				.replace("{position}", mPositionString)
				.replace("{spaces}", StringUtils.space(60 - mPositionName.length())))
			.append("\t" + sizeTemplate.replace("{var_name}", mSizeName)
				.replace("{size}", mSizeString)
				.replace("{spaces}", StringUtils.space(60 - mSizeName.length())))
			.append("\t" + pointTemplate.replace("{var_name}", mCellPositionName)
				.replace("{position}", cellPositionString)
				.replace("{spaces}", StringUtils.space(60 - mCellPositionName.length())))
			.append("\t" + sizeTemplate.replace("{var_name}", mCellSizeName)
				.replace("{size}", cellSizeString)
				.replace("{spaces}", StringUtils.space(60 - mCellSizeName.length())));
		
		builder.append("\t" + mCell.implementPositions());
		
		return builder.toString().replace("{tab}", "\t");
	}
	
	@Override
	public void setSize(String size) {
		this.mSizeString = size;
		if(size != null && size.contains(",")) {
			String[] strs = mSizeString.split(",");
			float w = Float.parseFloat(strs[0].trim());
			float h = Float.parseFloat(strs[1].trim());
			this.mSize = new Size(w, h);
		}
	}
	
	@Override
	public void setSize(Size size) {
		super.setSize(size);
		if(size != null && mCell != null) {
			mCell.setSize(size.getWidth(), (int)size.getHeight()/mRows);
		}
	}
	
	public void setRows(int pRows) {
		this.mRows = pRows;
	}
	
	public void setColumns(int pColumns) {
		this.mColumns = pColumns;
	}
	
	public int getRows() {
		return this.mRows;
	}
	
	public int getColumns() {
		return this.mColumns;
	}
	
	public void addCell(Cell cell) {
		this.mCell = cell;
	}
	
	@Override
	public void update() {
		this.mCell.setTabCount(mTabCount + 2);
	}
	
	public Cell getCell() {
		return mCell;
	}
	
	@Override
	public void setImage(Image img) {
		img.setExists(true);
		this.mImage = img;
	}
	
	@Override
	public CommonObject clone() {
		Table table = new Table();
		this.setAllPropertiesForObject(table);
		table.mCell = mCell;
		table.mColumns = mColumns;
		table.mRows = mColumns;
		table.mSizeName = mSizeName;
		table.mCellSizeName = mCellSizeName;
		table.mCellPositionName = mCellPositionName;
		return table;
	}
	
	@Override
	public String toXML() {
		String tab = StringUtils.tab(mTabCount);
		StringBuilder builder = new StringBuilder(tab);
		builder.append("<" + mXmlTagName + " " + Attribute.ROWS + "=\"" + mRows + "\" ")
			.append(Attribute.COLUMNS + "=\"" + mColumns + "\" ")
			.append(Attribute.VISIBLE + "=\"true\" ")
			.append("\n" + tab + "\t\t" + Attribute.COMMENT + "=\"\">");
		builder.append("\n" + tab + "\t")
			.append("<" + Tag.POSITION_NAME + " " + Attribute.VALUE 
					+ "=\"" + mXmlPositionName + "\" />");
		builder.append("\n" + tab + "\t")
		.append("<" + Tag.ANCHORPOINT + " " + Attribute.VALUE 
				+ "=\"" + mAnchorPointString + "\" />");
		builder.append("\n" + tab + "\t")
		.append("<" + Tag.POSITION + " " + Attribute.VALUE 
				+ "=\"" + mPosition + "\" />");
		builder.append("\n" + tab + "\t")
		.append("<" + Tag.SIZE + " " + Attribute.VALUE 
				+ "=\"" + mSize + "\" />");
		builder.append("\n" + tab + "\t")
		.append("<" + Tag.Z_INDEX + " " + Attribute.VALUE 
				+ "=\"" + mZIndex + "\" />");
		
		builder.append("\n" + mImage.toXML());
		builder.append("\n" + mCell.toXML());
		
		builder.append("\n")
			.append(super.toXML())
			.append(tab)
			.append("</" + mXmlTagName + ">");
		
		builder.append("\n");
		
		return builder.toString();
	}
	
	protected String mCellSizeName;
	protected String mCellPositionName;
	protected String mSizeName;
	protected Cell mCell;
	protected int mRows;
	protected int mColumns;
	
}
