#include "NodeList.h"

#ifdef MACRO_LIB_COCOS2D

#include "ToolStd.h"
#include "ApiCocos2dx.h"

#include "MLoger.h"

NS_TOOL_FRAME_BEGIN

CNodeList::CNodeList(void)
{
	_bDirtyAdjust	= false;
	_rStandard		= Size(0, 0);

	//setIsRelativeAnchorPoint(true);
	setAnchorPoint(CCPoint(0.5,0.5));
	SetAlign(ALIGN_HORIZONTAL_CENTER);
	
	SetAdaptive(false);
	SetAutoCut(false);

	SetSize(CCDirector::sharedDirector()->getWinSize());

	SetMoveArg(1.0f,2);

	schedule(schedule_selector(CNodeList::Update));
}

CNodeList::~CNodeList(void)
{
}


bool CNodeList::SetSize( const CCSize& rSize )
{
	CCNodeRGBA::setContentSize(rSize);

	_rStandard = rSize;
	
	return true;
}

bool CNodeList::SetWithRect( const CCRect& rWorld )
{
	SetSize(rWorld.size);
	ApiCocos2dx::SetWorldPostion(this,ApiCocos2dx::GetRectCenterPoint(rWorld));
	return true;
}

void CNodeList::SetMoveArg( float fMoveTime,float fMoveRate )
{
	_fMoveTime = fMoveTime;
	_fMoveRate = fMoveRate;
}

void CNodeList::addChild( CCNode * child )
{
	addChild(child,child->getZOrder(),child->getTag());
}

void CNodeList::addChild( CCNode * child, int zOrder )
{
	addChild(child,zOrder,child->getTag());
}

void CNodeList::addChild( CCNode * child, int zOrder, int tag )
{
	_bDirtyAdjust = true;
	CCNodeRGBA::addChild(child,zOrder,tag);

	child->setPosition(ApiCocos2dx::GetContentSizeCenter(this));
}

void CNodeList::removeChild( CCNode* child, bool cleanup )
{
	_bDirtyAdjust = true;
	CCNodeRGBA::removeChild(child,cleanup);
}

void CNodeList::reorderChild( CCNode * child, int zOrder )
{
	_bDirtyAdjust = true;
	CCNodeRGBA::reorderChild(child,zOrder);
}

void CNodeList::Update( float dt )
{
	if (_bDirtyAdjust)
		Adjust();
}

bool CNodeList::Adjust()
{
	if (IsChildEmpty())return true;

	_bDirtyAdjust = false;
	
	//����Ƿ����̯�����ɵ��£�����������ɵ��� ����ԭ�еĶ��뷽ʽ������ ���վ��ֵĶ��뷽ʽ����
	switch (GetAlign())
	{
	case ALIGN_HORIZONTAL_CENTER:
		ASSERT_LOG_ERROR(AdjustCenterHorizontal());
		break;
	case ALIGN_HORIZONTAL_AVG:
		ASSERT_LOG_ERROR(AdjustAvgHorizonta());
		break;
	case ALIGN_VERTICAL_CENTER:
		ASSERT_LOG_ERROR(AdjustCenterVertical());
		break;
	case ALIGN_VERTICAL_AVG:
		ASSERT_LOG_ERROR(AdjustAvgVertical());
		break;
	default:
		{
			LOG_ERROR();
			return false;
		}
	}

	return true;
}

//ˮƽ����
bool CNodeList::AdjustCenterHorizontal()
{
	ASSERT_LOG_ERROR(!IsChildEmpty());

	//��������ռ�
	CCSize rNeed;
	if (!AdjustEnoughSpace(rNeed,ALIGN_HORIZONTAL_CENTER))
		return AdjustFullHorizontal();

	ASSERT_LOG_ERROR(IsEnoughSpace(rNeed));

	//�����������
	VectorPoint vPoint;
	CalPosTileHorizontal(vPoint,CCPoint(getContentSize().width/2-rNeed.width/2,getContentSize().height/2));

	MoveTo(vPoint);
	return true;
}

//ˮƽ����
bool CNodeList::AdjustAvgHorizonta()
{
	ASSERT_LOG_ERROR(!IsChildEmpty());

	//��������ռ�
	CCSize rNeed;
	if (!AdjustEnoughSpace(rNeed,ALIGN_HORIZONTAL_AVG))
		return AdjustFullHorizontal();
	
	ASSERT_LOG_ERROR(IsEnoughSpace(rNeed));
	//�����������
	VectorPoint vPoint;
	CalPosAvgHorizontal(vPoint);

	MoveTo(vPoint);
	return true;
}

bool CNodeList::AdjustCenterVertical()
{
	ASSERT_LOG_ERROR(!IsChildEmpty());

	//��������ռ�
	CCSize rNeed;
	if (!AdjustEnoughSpace(rNeed,ALIGN_VERTICAL_CENTER))
		return AdjustFullVertical();

	ASSERT_LOG_ERROR(IsEnoughSpace(rNeed));

	//�����������
	VectorPoint vPoint;
	CalPosTileVertical(vPoint,CCPoint(getContentSize().width/2,getContentSize().height/2-rNeed.height/2));

	MoveTo(vPoint);
	return true;
}

bool CNodeList::AdjustAvgVertical()
{
	ASSERT_LOG_ERROR(!IsChildEmpty());

	//��������ռ�
	CCSize rNeed;
	if (!AdjustEnoughSpace(rNeed,ALIGN_VERTICAL_AVG))
		return AdjustFullVertical();

	ASSERT_LOG_ERROR(IsEnoughSpace(rNeed));

	//�����������
	VectorPoint vPoint;
	CalPosAvgVertical(vPoint);

	MoveTo(vPoint);
	return true;
}

//ˮƽ���
bool CNodeList::AdjustFullHorizontal()
{
	ASSERT_LOG_ERROR(!IsChildEmpty());

	//Ŀǰû�п����ⲿ�ӿ��ܹ���������ֻ���ܹ�������
	ASSERT_LOG_ERROR(!IsAdaptive());
	
	//��������ռ�
	CCSize rNeed;
	if (!AdjustEnoughSpace(rNeed,ALIGN_HORIZONTAL_FULL))
		return false;
	
	ASSERT_LOG_ERROR(IsEnoughSpace(rNeed));

	//�����������
	VectorPoint vPoint;
	CalPosFullHorizontal(vPoint);

	MoveTo(vPoint);
	return true;
}

//��ֱ���
bool CNodeList::AdjustFullVertical()
{
	ASSERT_LOG_ERROR(!IsChildEmpty());

	//Ŀǰû�п����ⲿ�ӿ��ܹ���������ֻ���ܹ�������
	ASSERT_LOG_ERROR(!IsAdaptive());
	
	//��������ռ�
	CCSize rNeed;
	if (!AdjustEnoughSpace(rNeed,ALIGN_VERTICAL_FULL))
		return false;

	ASSERT_LOG_ERROR(IsEnoughSpace(rNeed));

	//�����������
	VectorPoint vPoint;
	CalPosFullVertical(vPoint);

	MoveTo(vPoint);
	return true;
}

bool CNodeList::CalPosTileHorizontal( VectorPoint& vPoint,const CCPoint& ptOffset)
{
	ASSERT_LOG_ERROR(!IsChildEmpty());

	CCPoint ptCur = ptOffset;
	for (UINT uIndex =0;uIndex<GetChildCount();++uIndex)
	{
		CCNode* pNode = FindChildAtIndex(uIndex);
		ASSERT_LOG_ERROR(pNode);

		CCSize rBoundingBox = pNode->boundingBox().size;
		ptCur.x += rBoundingBox.width / 2;

		vPoint.push_back(ptCur);

		ptCur.x += rBoundingBox.width / 2;
	}
	ASSERT_LOG_ERROR(GetChildCount() == vPoint.size());

	return true;
}

//����ˮƽ����
bool CNodeList::CalPosAvgHorizontal( VectorPoint& vPoint)
{
	ASSERT_LOG_ERROR(!IsChildEmpty());

	float fSpace = getContentSize().width / GetChildCount();

	for(size_t uIndex =0;uIndex<GetChildCount();++uIndex){
		vPoint.push_back(CCPoint(fSpace * uIndex + fSpace / 2,getContentSize().height/2));
	}

	return vPoint.size() == GetChildCount();
}

bool CNodeList::CalPosTileVertical( VectorPoint& vPoint,const CCPoint& ptOffset /*=CCPoint(0,0) */ )
{
	ASSERT_LOG_ERROR(!IsChildEmpty());

	CCPoint ptCur = ptOffset;
	for (UINT uIndex =0;uIndex<GetChildCount();++uIndex)
	{
		CCNode* pNode = FindChildAtIndex(uIndex);
		ASSERT_LOG_ERROR(pNode);

		CCSize rBoundingBox = pNode->boundingBox().size;
		ptCur.y += rBoundingBox.height / 2;

		vPoint.push_back(ptCur);

		ptCur.y += rBoundingBox.height / 2;
	}

	ASSERT_LOG_ERROR(GetChildCount() == vPoint.size());

	return true;
}

bool CNodeList::CalPosAvgVertical( VectorPoint& vPoint)
{
	ASSERT_LOG_ERROR(!IsChildEmpty());

	float fSpace = getContentSize().height / GetChildCount();
	
	for(size_t uIndex =0;uIndex<GetChildCount();++uIndex){
		vPoint.push_back(CCPoint(getContentSize().width/2,fSpace * uIndex + fSpace / 2));
	}

	return vPoint.size() == GetChildCount();
}

//ˮƽ���(�����һ��Ϊƽ�����Ƚ��д��)
bool CNodeList::CalPosFullHorizontal( VectorPoint& vPoint)
{
	ASSERT_LOG_ERROR(!IsChildEmpty());
	ASSERT_LOG_ERROR(GetChildCount() > 1);//�������1��Ϊ �������1 ��ôҲ����˵ �����Ķ��뷽ʽ��1�����Ų��£��������

	CCSize rLast = FindChildLast()->boundingBox().size;

	float fUnit = (getContentSize().width-rLast.width) / (GetChildCount() -1);

	for(size_t uIndex =0;uIndex<GetChildCount();++uIndex){
		float fPos = fUnit * uIndex + rLast.width / 2;

		vPoint.push_back(CCPoint(fPos,getContentSize().height/2));
	}

	return true;
}

//��ֱ���(�����һ��Ϊƽ�����Ƚ��д��)
bool CNodeList::CalPosFullVertical( VectorPoint& vPoint)
{
	ASSERT_LOG_ERROR(!IsChildEmpty());
	ASSERT_LOG_ERROR(GetChildCount() > 1);//�������1��Ϊ �������1 ��ôҲ����˵ �����Ķ��뷽ʽ��1�����Ų��£��������

	CCSize rLast = FindChildLast()->boundingBox().size;

	float fUnit = (getContentSize().height-rLast.height) / (GetChildCount() -1);

	for(size_t uIndex =0;uIndex<GetChildCount();++uIndex){
		float fPos = fUnit * uIndex + rLast.height / 2;

		vPoint.push_back(CCPoint(getContentSize().width/2,fPos));
	}

	return true;
}

bool CNodeList::MoveTo( const VectorPoint& vPoint )
{
	ASSERT_LOG_ERROR(!IsChildEmpty());
	ASSERT_LOG_ERROR(GetChildCount() == vPoint.size());

	for (size_t uIndex =0;uIndex<vPoint.size();++uIndex)
	{
		const CCPoint& ptDes = vPoint[uIndex];

		CCNode* pNode = FindChildAtIndex(uIndex);
		ASSERT_LOG_ERROR(pNode);

		const CCPoint& ptSrc = pNode->getPosition();
		if (!ptSrc.equals(ptDes))
		{
			ActionInterval*  pMoveTo = MoveTo::create(_fMoveTime, ptDes);
			ASSERT_LOG_ERROR(pMoveTo);
			EaseInOut* pEaseInOut = EaseInOut ::create(pMoveTo,_fMoveRate);
			ASSERT_LOG_ERROR(pEaseInOut);
			pNode->runAction(pEaseInOut);
		}
	}
	return true;
}

void CNodeList::SetAdjustScreenCenter()
{
	SetAlign(ALIGN_HORIZONTAL_CENTER);
	this->setPosition(ApiCocos2dx::GetScreenCenterPoint());
	SetSize(CCDirector::sharedDirector()->getWinSize());
}

CCSize CNodeList::CalTotalSize()
{
	CCSize size;
	for (UINT uIndex =0;uIndex<GetChildCount();++uIndex)
	{
		CCNode* pNode = FindChildAtIndex(uIndex);
		ASSERT_LOG_ERROR(pNode);

		ApiCocos2dx::SelfPlus(size,pNode->boundingBox().size);
	}

	return size;
}



void CNodeList::SetSizeWhithScreenSize()
{
	SetSize(CCDirector::sharedDirector()->getWinSize());
}

void CNodeList::SetAdaptive( const CCSize& rNeed )
{
	//��������ϵ��
	float fRate =  GetAdaptiveRate(getContentSize(),rNeed);
	//���еȱ�������
	for (UINT uIndex =0;uIndex<GetChildCount();++uIndex)
	{
		CCNode* pNode = FindChildAtIndex(uIndex);
		ASSERT_LOG_ERROR(pNode);

		ApiCocos2dx::SetScale(pNode,fRate,fRate);
	}
}

float CNodeList::GetAdaptiveRate( const CCSize& rContent,const CCSize& rNeed )
{
	//��������ϵ��
	float fRateX = rContent.width / rNeed.width;
	float fRateY = rContent.height/ rNeed.height;

	return  ToolFrame::Min(fRateX,fRateY);
}

CCSize CNodeList::GetAdaptiveSize(const CCSize& rContent,const CCSize& rNeed)
{
	float fRate =  GetAdaptiveRate(rContent,rNeed);
	ASSERT_LOG_ERROR(fRate <= 1.0);
	return CCSize(rNeed.width * fRate,rNeed.height * fRate );
}

CCSize CNodeList::GetNeedSizeHorizontalTile()
{
	const CCSize& rSizeContent = CalTotalSize();

	CCNode* pNode =  FindChildByBoundingBoxMostHigh();
	ASSERT_LOG_ERROR(pNode);

	return CCSize(rSizeContent.width,pNode->boundingBox().size.height);
}

CCSize CNodeList::GetNeedSizeHorizontalAvg()
{
	CCNode* pNodeHeight =  FindChildByBoundingBoxMostHigh();
	ASSERT_LOG_ERROR(pNodeHeight);

	CCNode* pNodeWidth =  FindChildByBoundingBoxMostWide();
	ASSERT_LOG_ERROR(pNodeWidth);

	float fContent = pNodeWidth->boundingBox().size.width * GetChildCount();

	return CCSize( ToolFrame::Max(fContent,getContentSize().width),pNodeHeight->boundingBox().size.height);
}

CCSize CNodeList::GetNeedSizeHorizontalFull()
{
	CCNode* pNode =  FindChildByBoundingBoxMostHigh();
	ASSERT_LOG_ERROR(pNode);

	return CCSize(getContentSize().width,pNode->boundingBox().size.height);
}

CCSize CNodeList::GetNeedSizeVerticalTile()
{
	const CCSize& rSizeContent = CalTotalSize();

	CCNode* pNode =  FindChildByBoundingBoxMostWide();
	ASSERT_LOG_ERROR(pNode);

	return CCSize(pNode->boundingBox().size.width,rSizeContent.height);
}

CCSize CNodeList::GetNeedSizeVerticalAvg()
{
	CCNode* pNodeHeight =  FindChildByBoundingBoxMostHigh();
	ASSERT_LOG_ERROR(pNodeHeight);

	CCNode* pNodeWidth =  FindChildByBoundingBoxMostWide();
	ASSERT_LOG_ERROR(pNodeWidth);

	float fContent = pNodeHeight->boundingBox().size.height * GetChildCount();

	return CCSize(pNodeWidth->boundingBox().size.width, ToolFrame::Max(fContent,getContentSize().height));
}

CCSize CNodeList::GetNeedSizeVerticalFull()
{
	CCNode* pNode =  FindChildByBoundingBoxMostWide();
	ASSERT_LOG_ERROR(pNode);

	return CCSize(pNode->boundingBox().size.width,getContentSize().height);
}

bool CNodeList::IsEnoughSpace( const CCSize& rNeed )
{
	return IsEnoughSpace( getContentSize(),rNeed);
}

bool CNodeList::IsEnoughSpace( const CCSize& rContent,const CCSize& rNeed )
{
	//���0.1��Ϊ�˼��ݸ������������
	return rNeed.width <= rContent.width+0.1 && rNeed.height <= rContent.height+0.1;
}

bool CNodeList::IsChildEmpty()
{
	return getChildren().empty();

}

UINT CNodeList::GetChildCount()
{
	return getChildren().size();
}

CCNode* CNodeList::FindChildAtIndex(UINT nIndex)
{
	return getChildren().at(nIndex);
}

CCNode* CNodeList::FindChildLast()
{
	return getChildren().back();
}

CCNode* CNodeList::FindChildByBoundingBoxMostHigh()
{
	return ApiCocos2dx::FindNodeByBoundingBoxMostHigh(getChildren());
}

CCNode* CNodeList::FindChildByBoundingBoxMostWide()
{
	return ApiCocos2dx::FindNodeByBoundingBoxMostWide(getChildren());
}

bool CNodeList::Cut(CCSize rNeed)
{
	ASSERT_LOG_ERROR(!IsChildEmpty());

	if (!IsEnoughSpace( _rStandard,rNeed))
	{
		if (IsAdaptive())
		{
			rNeed = GetAdaptiveSize(_rStandard,rNeed);
		}else
		{
			return false;
		}
	}
	ASSERT_LOG_ERROR(IsEnoughSpace( _rStandard,rNeed));

	CCNodeRGBA::setContentSize(rNeed);
	return true;
}

bool CNodeList::Cut()
{
	CCSize rNeed = GetNeedSize(GetAlign());
	return Cut(rNeed);
}

CCSize CNodeList::GetNeedSize( int eAlign )
{
	switch(eAlign)
	{
	case ALIGN_HORIZONTAL_CENTER:
		return GetNeedSizeHorizontalTile();
		break;
	case ALIGN_HORIZONTAL_AVG:
		return GetNeedSizeHorizontalAvg();
		break;
	case ALIGN_VERTICAL_CENTER:
		return GetNeedSizeVerticalTile();
		break;
	case ALIGN_VERTICAL_AVG:
		return GetNeedSizeVerticalAvg();
		break;
	case ALIGN_HORIZONTAL_FULL:
		return GetNeedSizeHorizontalFull();
		break;
	case ALIGN_VERTICAL_FULL:
		return GetNeedSizeVerticalFull();
		break;
	}

	LOG_ERROR();
	return Size(0,0);
}

bool CNodeList::AdjustEnoughSpace( CCSize& rNeed,int eAlign )
{
	//��������ռ�
	rNeed = GetNeedSize(eAlign);

	//�ü�
	if (IsAutoCut())
		Cut(rNeed);

	//����Ӧ
	if (IsAdaptive())
	{
		//ʹ�ÿռ�������ɵ�������ռ�
		SetAdaptive(rNeed);
		rNeed = GetNeedSize(eAlign);
		return true;
	}
	
	return IsEnoughSpace(rNeed);
}

NS_TOOL_FRAME_END

#endif //MACRO_LIB_COCOS2D
