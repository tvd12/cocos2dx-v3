package com.tdgc.videopokerjackpot.inapp.models;

public class PokerSku implements Comparable<PokerSku> {
	
	private String skuId;
	private String price;
	
	public PokerSku() {
		
	}
	
	public PokerSku(String skuId, String price) {
		this.skuId = skuId;
		this.price = price;
	}
	
	public String getSkuId() {
		return skuId;
	}
	public void setSkuId(String skuId) {
		this.skuId = skuId;
	}
	public String getPrice() {
		return price;
	}
	public void setPrice(String price) {
		this.price = price;
	}
	
	@Override
	public String toString() {
		StringBuilder builder = new StringBuilder();
		builder.append("productId: " + skuId);
		builder.append(", price: " + price + "\n");
		return builder.toString();
	}

	@Override
	public int compareTo(PokerSku sku) {
		return this.getSkuId().compareTo(sku.getSkuId());
	}
}
