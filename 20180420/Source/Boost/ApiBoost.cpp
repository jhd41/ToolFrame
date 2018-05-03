#include "Macro.h"

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/thread/thread.hpp>
#include <boost/regex.hpp>
#include <boost/asio.hpp>

#include "ApiBoost.h"

#ifdef MACRO_LIB_BOOST

#include "ToolStd.h"
#include "MLoger.h"

std::string ApiBoost::GetWorkingDir()
{
	return ToolFrame::TrimDir(boost::filesystem::initial_path<boost::filesystem::path>().string());
}

void ApiBoost::Sleep( uint64 uTimeMill )
{
	boost::this_thread::sleep_for(boost::chrono::milliseconds(uTimeMill));

//	boost::this_thread::sleep(boost::posix_time::milliseconds(uTimeMill));

	//boost::thread::sleep(boost::get_system_time()+boost::posix_time::milliseconds(nTimeMill));

	//boost::this_thread::sleep(boost::posix_time::milliseconds(nTimeMill));//这条语句会产生警告
}

UINT ApiBoost::GetThreadTotals()
{
	return boost::thread::hardware_concurrency();
}

bool ApiBoost::IsRegexMatch(const std::string& sString, const std::string& sRegex)
{
	boost::regex reg(sRegex);
	return IsRegexMatch(sString, reg);
}

bool ApiBoost::IsRegexMatch(const std::string& sString, const boost::regex& regex)
{
	return  boost::regex_match(sString, regex);
}

std::string ApiBoost::RegexReplace(const std::string& sString, const std::string& sRegex, const std::string& sReplaceTo)
{
	boost::regex reg(sRegex);
	return RegexReplace(sString, reg, sReplaceTo);
}

std::string ApiBoost::RegexReplace(const std::string& sString, const boost::regex& regex, const std::string& sReplaceTo)
{
	return boost::regex_replace(sString, regex, sReplaceTo);
}

bool ApiBoost::IsEmail(const std::string& sAddress)
{
	static const boost::regex reg("\\w+([-+.]\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*");
	return IsRegexMatch(sAddress, reg);
}

bool ApiBoost::IsTelNumber(const std::string& sTelNumber)
{
	static const boost::regex reg("^1[0-9]{10}$");
	return IsRegexMatch(sTelNumber, reg);
}

bool ApiBoost::IsIdentityNumber(const std::string& sAddress)
{
	static const boost::regex reg("(^\\d{15}$)|(^\\d{17}([0-9]|X|x)$)");
	return IsRegexMatch(sAddress, reg);
}

std::string ApiBoost::GetLocalIp()
{
	using boost::asio::ip::tcp;
	boost::asio::io_service io_service;
	tcp::resolver resolver(io_service); 
	tcp::resolver::query query(boost::asio::ip::host_name(), ""); 

	boost::system::error_code ec;
	tcp::resolver::iterator iter = resolver.resolve(query, ec);
	if (ec)return "";
	
	tcp::resolver::iterator end;
	// End marker. 
	while (iter != end) { 
		tcp::endpoint ep = *iter++; 
		boost::system::error_code eErrCode;
		std::string sResult = ep.address().to_string(eErrCode);
		if (eErrCode)continue;
		return sResult;
	} 

	return "";
}

std::string ApiBoost::GetHostName()
{
	return boost::asio::ip::host_name();
}

boost::asio::io_service& ApiBoost::GetGlobeIoService()
{
	static boost::asio::io_service g_ioService;
	return g_ioService;
}

void ApiBoost::SetGlobeServiceWork()
{
	boost::asio::io_service& ioService = GetGlobeIoService();
	//常驻工作(没有实际意义,目的始终保持ioService有工作 从而不去清理工作任务。使得其能够在IOS平台正确运行)
	static boost::asio::io_service::work g_workResolve(ioService);
}

#endif
