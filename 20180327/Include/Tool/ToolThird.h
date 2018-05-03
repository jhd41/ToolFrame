#pragma once
#include "MacroThird.h"

namespace ToolFrame
{
	//渠道转换
	bool			InitChannelString();
	MapIntString&	GetMapChannelString();
	MapStringInt&	GetMapStringChannel();

	//添加渠道
	bool			InsertChannelString(int eChannelID,const std::string& sChannelString);
	
	//转换渠道
	std::string		TranChannelType( int eChannelType ) ;
	int				TranChannelString( const std::string& sChannelID ) ;
}