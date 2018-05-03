#include "MDebug.h"
#include "MLoger.h"
#include "ToolFrame.h"

NS_TOOL_FRAME_BEGIN

MDebug::MDebug()
{
}

MDebug::~MDebug()
{
}

bool MDebug::Point(const std::string& sTag)
{
	if (sTag.empty())return false;

	CCalCounterInt& counter = _vTagCount.GetValueRefByKeyForce(sTag);
	counter.AddCount();
	return true;
}

bool MDebug::PointRetain(const std::string& sTag)
{
	if (sTag.empty())return false;

	CCalCounterInt& counter = _vTagCount.GetValueRefByKeyForce(sTag);
	counter.AddCount();
	return true;
}

bool MDebug::PointReduce(const std::string& sTag)
{
	if (sTag.empty())return false;

	CCalCounterInt& counter = _vTagCount.GetValueRefByKeyForce(sTag);
	counter.ReduceCount();
	return true;
}

bool MDebug::ElapsedRetain(const std::string& sTag)
{
	if (sTag.empty())return false;

	XElapsedInfo& info = _vTagElapsed.GetValueRefByKeyForce(sTag);
	CLockWrite lock(info._mutex);
	++info._uCount;
	++info._uUsing;
	return true;
}

bool MDebug::ElapsedReduce(const std::string& sTag, uint64 uTimeElapsed, bool bInvaild /*= false*/)
{
	if (sTag.empty())return false;

	XElapsedInfo& info = _vTagElapsed.GetValueRefByKeyForce(sTag);

	CLockWrite lock(info._mutex);

	--info._uUsing;

	if (bInvaild)
	{
		++(info._uInvaild);
		info._uInvaildTotal += uTimeElapsed;
		return true;
	}


	info._tTimeAvg.AddTimeElapsed(uTimeElapsed);

	if (info._bFirst)
	{
		info._bFirst = false;
		info._uElapsedFirst = uTimeElapsed;
	}

	info._uElapsedLast = uTimeElapsed;

	info._uTimeMin = 0 == info._uTimeMin ? uTimeElapsed : ToolFrame::Min(info._uTimeMin, uTimeElapsed);
	info._uTimeMax = ToolFrame::Max(info._uTimeMax, uTimeElapsed);

	info._uTotal += uTimeElapsed;
	return true;
}

bool MDebug::TimeChain(const std::string& sType, const std::string& sID, const std::string& sTag)
{
	if (sType.empty())return false;
	if (sID.empty())return false;
	if (sTag.empty())return false;

	XTimeChain& info = _vTimeChain.GetValueRefByKeyForce(PairStringString(sType, sID));
	CLockWrite lock(info._mutex);
	info._sType = sType;
	info._sID = sID;

	return ToolFrame::InsertUnique(info._vTagTime, PairStringUint64(sTag,ToolFrame::GetNowTimeMill()));
}

std::string MDebug::DebugString(const VectorString& vDebug) const
{
	std::stringstream sStream;
	if (ToolFrame::IsHasValue(vDebug, "DebugPoint"))
	{
		sStream << "DebugPoint:" << std::endl;
		CLockRead lock(_vTagCount.GetMutex());

		MapTagCount::StdMap::const_iterator itr;
		foreach(itr, _vTagCount.GetMap()) {
			char sz[1024] = {0};
			sprintf_s(sz, "Tag:%-70s Count:%-5d", itr->first.c_str(), itr->second.GetCount());
			sStream << sz << std::endl;
		}
	}

	if (ToolFrame::IsHasValue(vDebug, "DebugElapsed"))
	{
		sStream << "DebugElapsed:" << std::endl;
		CLockRead lock(_vTagElapsed.GetMutex());

		MapTagElapsed::StdMap::const_iterator itr;
		foreach(itr, _vTagElapsed.GetMap()) {
			const XElapsedInfo& info = itr->second;
			CLockRead lock(info._mutex);
			char sz[1024] = { 0 };
			sprintf_s(sz,"Tag:%-70s Count:%-5d Using:%-3d TotalElapsed:%-10lld ElapsedMin:%-5lld TimeMax:%-5lld ElapsedAvg:%-5lld ElapsedFirst:%-5lld ElapsedLast:%-5lld Invaild:%-5lld InvaildTotal:%-5lld", itr->first.c_str(), info._uCount, info._uUsing, info._uTotal, info._uTimeMin, info._uTimeMax, info._tTimeAvg.GetAvgTime(), info._uElapsedFirst,info._uElapsedLast, info._uInvaild, info._uInvaildTotal);
			sStream << sz << std::endl;
		}
	}

	if (ToolFrame::IsHasValue(vDebug, "DebugTimeChain")) {
		sStream << "DebugTimeChain:" << std::endl;
		CLockRead lock(_vTimeChain.GetMutex());

		MapTimeChain::StdMap::const_iterator itr;
		foreach(itr, _vTimeChain.GetMap()) {
			const XTimeChain& info = itr->second;
			CLockRead lock(info._mutex);
			sStream<<"Type:"<< info._sType << " ID:" << info._sID << std::endl;

			//写入时间点统计
			uint64 uTimeLast = 0;
			VectorTagTime::const_iterator itrTagTime;
			foreach(itrTagTime, info._vTagTime) {
				sStream << "Time:" << ToolFrame::TimeToStringMill(itrTagTime->second) << " Tag:" << itrTagTime->first;

				if (0 == uTimeLast){
					uTimeLast = itrTagTime->second;
				}
				else {
					uint64 uWaste = itrTagTime->second - uTimeLast;
					uTimeLast = itrTagTime->second;
					sStream << " Waste:" << uWaste;
				}

				sStream << std::endl;
			}
		}

		sStream << std::endl;
	}

	return sStream.str();
}

const MDebug::MapTagCount& MDebug::GetTagCount() const
{
	return _vTagCount;
}
//////////////////////////////////////////////////////////////////////////
CDebugElapsed::CDebugElapsed()
{
	_bInvaild = false;
}

CDebugElapsed::CDebugElapsed(const std::string& sTag)
{
	SetTag(sTag);
}

bool CDebugElapsed::SetTag(const std::string& sTag)
{
	if (sTag.empty())return false;
	if (!_sTag.empty())return false;

	_sTag = sTag;
	MDebug::Singleton().ElapsedRetain(sTag);
	return true;
}

bool CDebugElapsed::ReStart()
{
	_tTimeElapse.ReStart();
	return true;
}

bool CDebugElapsed::SetInvaild(bool bInvaild /*= true*/)
{
	_bInvaild = bInvaild;
	return true;
}

CDebugElapsed::~CDebugElapsed()
{
	MDebug::Singleton().ElapsedReduce(_sTag, _tTimeElapse.TimeElapsed(), _bInvaild);
}

NS_TOOL_FRAME_END
