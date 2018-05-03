#include "TouchAnalyzer.h"
#include "TouchListener.h"

#ifdef MACRO_LIB_COCOS2D

#include "ToolFrame.h"
#include "ApiCocos2dx.h"
#include "MLoger.h"

CTouchListener::CTouchListener(void)
{
	Construction();
}

CTouchListener::~CTouchListener(void)
{
	Destructor();
}

bool CTouchListener::SetNode( Node* pNode )
{
	_pNode = pNode;
	return true;
}

bool CTouchListener::OnTouchBegan( Touch* touch, Event *unusedEvent )
{
	if (!ApiCocos2dx::IsHitted(_pNode,touch,unusedEvent))return false;

	ToolFrame::Insert(_vTouch,touch);

	VectorAnalyzer::iterator itr;
	foreach(itr,_vAnalyzer){
		ITouchAnalyzer* pAnalyzer = *itr;
		ASSERT_LOG_ERROR(pAnalyzer);

		pAnalyzer->OnTouchBegan(touch,unusedEvent);
	}
	return true;
}

void CTouchListener::OnTouchMoved( Touch* touch, Event *unusedEvent )
{
	VectorAnalyzer::iterator itr;
	foreach(itr,_vAnalyzer){
		ITouchAnalyzer* pAnalyzer = *itr;
		ASSERT_LOG_ERROR(pAnalyzer);

		pAnalyzer->OnTouchMoved(touch,unusedEvent);
	}
}

void CTouchListener::OnTouchEnded( Touch* touch, Event *unusedEvent )
{
	ToolFrame::Erase(_vTouch,touch);

	VectorAnalyzer::iterator itr;
	foreach(itr,_vAnalyzer){
		ITouchAnalyzer* pAnalyzer = *itr;
		ASSERT_LOG_ERROR(pAnalyzer);

		pAnalyzer->OnTouchEnded(touch,unusedEvent);
	}
}

void CTouchListener::OnTouchCancelled( Touch* touch, Event *unusedEvent )
{
	ToolFrame::Erase(_vTouch,touch);

	VectorAnalyzer::iterator itr;
	foreach(itr,_vAnalyzer){
		ITouchAnalyzer* pAnalyzer = *itr;
		ASSERT_LOG_ERROR(pAnalyzer);

		pAnalyzer->OnTouchCancelled(touch,unusedEvent);
	}
}

const VectorTouch& CTouchListener::GetTouches() const
{
	return _vTouch;
}

bool CTouchListener::SetHandler( HTouchListener* hHandler )
{
	_hHandler = hHandler;
	return true;
}

HTouchListener* CTouchListener::GetHandler() const
{
	return _hHandler;
}

Node* CTouchListener::GetNode() const
{
	return _pNode;
}

bool CTouchListener::Construction()
{
	_pNode = nullptr;
	_hHandler = nullptr;

	ToolFrame::Insert(_vAnalyzer,new CTouchAnalyzerIdel());
	ToolFrame::Insert(_vAnalyzer,new CTouchAnalyzerDrag());
	ToolFrame::Insert(_vAnalyzer,new CTouchAnalyzerScaleView());
	ToolFrame::Insert(_vAnalyzer,new CTouchAnalyzerSingleTouch());
	ToolFrame::Insert(_vAnalyzer,new CTouchAnalyzerDelay());
	ToolFrame::Insert(_vAnalyzer,new CTouchAnalyzerManual());
	ToolFrame::Insert(_vAnalyzer, new CTouchAnalyzerSlip());
	
	VectorAnalyzer::iterator itr;
	foreach(itr,_vAnalyzer){
		ITouchAnalyzer* pAnalyzer = *itr;
		ASSERT_LOG_ERROR(pAnalyzer);

		pAnalyzer->SetTouchLister(this);
	}

	return true;
}

bool CTouchListener::Destructor()
{
	ToolFrame::Delete(_vAnalyzer);
	return true;
}

CTouchListener::CTouchListener( const CTouchListener& lister )
{
	Construction();
	
	*this = lister;
}

CTouchListener& CTouchListener::operator=( const CTouchListener& lister )
{
	SetNode(lister.GetNode());
	SetHandler(lister.GetHandler());
	SetEnabled(lister.IsEnabled());

	return *this;
}

bool CTouchListener::SetEnabled( bool bEnabled )
{
	_bEnabled = bEnabled;
	return true;
}

bool CTouchListener::IsEnabled() const
{
	return _bEnabled;
}

#endif //MACRO_LIB_COCOS2D
