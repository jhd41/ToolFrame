#pragma once
#include "MacroThird.h"

namespace ToolFrame
{
	//����ת��
	bool			InitChannelString();
	MapIntString&	GetMapChannelString();
	MapStringInt&	GetMapStringChannel();

	//�������
	bool			InsertChannelString(int eChannelID,const std::string& sChannelString);
	
	//ת������
	std::string		TranChannelType( int eChannelType ) ;
	int				TranChannelString( const std::string& sChannelID ) ;
}