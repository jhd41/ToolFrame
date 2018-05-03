#pragma once

bool TestHttp() {
	std::string s1 = ToolFrame::HttpRequest("hypay.hao-games.com");
	std::string s2 = ToolFrame::HttpRequest("hypay.hao-games.com/creatorder.php");
	std::string s3 = ToolFrame::HttpRequest("hypay.hao-games.com/Alipay/creatorder.php");
	std::string s4 = ToolFrame::HttpRequest("hypay.hao-games.com/Alipay/creatorder.php?aaa&bb");
	std::string s5 = ToolFrame::HttpRequest("http://hypay.hao-games.com");
	std::string s6 = ToolFrame::HttpRequest("http://hypay.hao-games.com/Alipay/creatorder.php");
	std::string s7 = ToolFrame::HttpRequest("http://hypay.hao-games.com/Alipay/creatorder.php?aaa&bb");
	return true;
}
