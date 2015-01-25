Tích hợp Google Analytics plugin trên XCode cho ios

1. Trong thư mục project tạo một thư mục libraries

2. Copy thư mục google-analytics vào thư mục libraries vừa tạo

3. Từ dự án của bạn, chuột phải và chọn ‘Add Files To ‘${Your_Project}’ và chọn đến google-analytics/ios/goog-analytics.xcodeproj

4. Chọn dự án của bạn -> ios target -> build setting -> Search Paths -> Header Search paths. Thêm vào “$(SRCROOT)/../libraries/google-analytics/include” hoặc sẽ khác nếu bạn đặt google-analytics plugin-x ở nơi khác

5. Chọn dự án của bạn -> ios target -> build phases -> Link Binary With Libraries
Thêm các Frame work sau:
	1. CoreData.framework
	2. SystemConfiguration.framework
	3. libz.dylib

6. Trong hàm applicationDidFinishLaunching của AppDelegate thêm vào cuối hàm:
    
    GoogleAnalyticsHelper::getInstance()->setAppName(“${Your App Name});
    GoogleAnalyticsHelper::getInstance()->setAppVersion(“${Your App Version}”);
    GoogleAnalyticsHelper::getInstance()->setTrackingId(“${Your App Tracking Id}”);
    GoogleAnalyticsHelper::getInstance()->init();
    
    GoogleAnalyticsHelper::getInstance()->sendScreenView(“${Your First Screen}”); //option 

7. Vui lòng xem các hàm trong GoogleAnalyticsHelper.h để biết các chức năng có thể sử dụng

8. Follow me for updating

Tích hợp Google Analytics plugin trên eclipse cho android

1. Import thư viện google-analytics vào eclipse

2. Chọn dự án của bạn -> chuột phải -> properties -> android. Trong phần library chọn add -> google-analytics -> ok 

3. Trong gói chính của bạn -> New -> Class. Tạo một lớp (ví dụ MyApplication) extends AnalyticsApplication.

4. Override các hàm: ví dụ:

	@Override
	public String appTrackerId() {
		return “${TrackerId}”;
	}
	
	@Override
	public String appName() {
		return "My Test Project";
	}
	
	@Override
	public String appVersion() {
		return "1.0.0";
	}

* Tham khảo code để biết thêm chi tiết

5. Trong hàm onCreate của main activity: ngay sau super.onCreate(), thêm dòng lệnh sau:

	GoogleAnalyticsHelper.sApplication = (MyApplication)getApplication();

6. Tiếp tục từ bước 6 trong phần ios 
