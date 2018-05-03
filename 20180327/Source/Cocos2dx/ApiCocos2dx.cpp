#include "ApiCocos2dx.h"

#ifdef MACRO_LIB_COCOS2D

#include "Cocos2dxEx.h"

#include "ToolFrame.h"
#include "MLoger.h"

#include "ActionIntervalEx.h"

#include "ActionTimeline/CSLoader.h"
#include "spine/extension.h"
#include "ActionTimeline/CCActionTimelineCache.h"

#include "AudioEngine.h"

bool ApiCocos2dx::g_bAutoPurgeCache = true;

MapStringSkeletonData	ApiCocos2dx::g_vSpineSkeletonData;
MapStringAtlas			ApiCocos2dx::g_vSpineAtlas;

bool ApiCocos2dx::g_bSoundMute = false;
bool ApiCocos2dx::g_bMusicMute = false;

int ApiCocos2dx::g_nAudioMusic = experimental::AudioEngine::INVALID_AUDIO_ID;

bool ApiCocos2dx::SetWorldPostionWithScreenCenter( Node* pNode )
{
	if (!pNode)return false;
	ApiCocos2dx::SetWorldPostion(pNode,GetScreenCenterPoint());
	return true;
}

bool ApiCocos2dx::SetWorldPostionWithScreenPoint( Node* pNode,float fX,float fY )
{
	if (!pNode)return false;
	ApiCocos2dx::SetWorldPostion(pNode,ApiCocos2dx::GetScreenPoint(fX,fY));
	return true;
}

Point ApiCocos2dx::GetScreenCenterPoint()
{
	return GetScreenPoint(0.5,0.5);
}

Point ApiCocos2dx::GetScreenPoint( const Point& pt )
{
	return GetScreenPoint(pt.x,pt.y);
}

Point ApiCocos2dx::GetScreenPoint( float fX,float fY )
{
	Size xSize = CCDirector::sharedDirector()->getWinSize();
	return ccp(xSize.width * fX, xSize.height * fY);
}

bool ApiCocos2dx::SetVisible( VectorNode& vNode,bool bVisible )
{
	VectorNode::iterator itr;
	foreach(itr,vNode){
		Node* node = *itr;
		if (node)
			node->setVisible(bVisible);
	}

	return true;
}

CCTexture2D* ApiCocos2dx::CacheTexture( const std::string& sPath)
{
	return CCTextureCache::getInstance()->addImage(sPath); 
}

Sprite* ApiCocos2dx::CreateSprite( const std::string& sPath)
{
	return Sprite::create(sPath);
}

SpriteBatchNode* ApiCocos2dx::CreateSpriteBatch( const std::string& sPath )
{
	return CCSpriteBatchNode::create(sPath);
}

SpriteBatchNode* ApiCocos2dx::CreateSpriteBatch( CCTexture2D* pTexture )
{
	return CCSpriteBatchNode::createWithTexture(pTexture);
}

Sprite* ApiCocos2dx::CreateSprite( CCTexture2D* pTexture )
{
	if (!pTexture)return nullptr;
	return Sprite::createWithTexture(pTexture);
}

bool ApiCocos2dx::RezorderBySeq(Node* pNodeParent,VectorSprite& vNode )
{
	if(vNode.empty())return true;

	MultiSetInt vOrder;

	//获取所有Z-Order并排序
	{
		VectorSprite::iterator itr;
		foreach(itr,vNode){
			Node* pNode = *itr;
			if (!ToolFrame::Insert(vOrder,pNode->getLocalZOrder()))return false;
		}
	}

	//设置进新的Order顺序
	{
		VectorSprite::iterator	itrNode;
		MultiSetInt::iterator	itrOrder;
		foreachDouble(itrNode,vNode,itrOrder,vOrder){
			Node* pNode = *itrNode;
			int nZorder = *itrOrder;
			pNodeParent->reorderChild(pNode,nZorder);
		}
	}

	return vOrder.size() == vNode.size();
}

bool ApiCocos2dx::SetZorderBySeq( Node* pNodeParent,VectorSprite& vNode,int nZ/*=0*/ )
{
	for (int nIndex =0;nIndex<(int)vNode.size();++nIndex)
	{
		Node* pNode = vNode[nIndex];
		pNodeParent->reorderChild(pNode,nIndex + nZ);
	}

	return true;
}

bool ApiCocos2dx::SetZorderBySeq( Node* pNodeParent,VectorNode& vNode,int nZ/*=0*/ )
{
	for (int nIndex =0;nIndex<(int)vNode.size();++nIndex)
	{
		Node* pNode = vNode[nIndex];
		pNodeParent->reorderChild(pNode,nIndex + nZ);
	}

	return true;
}

bool ApiCocos2dx::FindTouchedNode( VectorNode& vNodeDes,VectorNode& vNodeSrc,CCTouch *pTouch )
{
	VectorNode::iterator itr;
	foreach(itr,vNodeSrc){
		Node* pNode = *itr;
		if (pNode->isVisible())
		{
			if (IsTouchedNode(pNode,pTouch))
				vNodeDes.push_back(pNode);	
		}
	}

	return !vNodeDes.empty();
}

Size ApiCocos2dx::Plus( const Size& a,const Size& b )
{
	return Size(a.width + b.width,a.height+b.height);
}

Point ApiCocos2dx::Plus( const Point& a,const Point& b )
{
	return ccp(a.x+b.x,a.y+b.y);
}

Size& ApiCocos2dx::SelfPlus(Size& self,const Size& other )
{
	self.width += other.width;
	self.height+= other.height;
	return self;
}

Node* ApiCocos2dx::FindNodeByBoundingBoxMostWide( const VectorNode& vNode )
{
	if (vNode.empty())return nullptr;

	Node* pNodeMost = *vNode.begin();

	float fMost = pNodeMost->boundingBox().size.width;

	VectorNode::const_iterator itr;
	foreach(itr,vNode){
		Node* pNode = *itr;
		float fWidth = pNode->boundingBox().size.width ;
		if (fWidth > fMost)
		{
			fMost = fWidth;
			pNodeMost = pNode;
		}
	}

	return pNodeMost;
}

Node* ApiCocos2dx::FindNodeByBoundingBoxMostWide( const Vector<Node*>& vNode )
{
	if (vNode.empty())return nullptr;

	Node* pNodeMost = *vNode.begin();

	float fMost = pNodeMost->boundingBox().size.width;

	VectorNode::const_iterator itr;
	foreach(itr,vNode){
		Node* pNode = *itr;
		float fWidth = pNode->boundingBox().size.width ;
		if (fWidth > fMost)
		{
			fMost = fWidth;
			pNodeMost = pNode;
		}
	}

	return pNodeMost;
}

Node* ApiCocos2dx::FindNodeByBoundingBoxMostHigh( const VectorNode& vNode )
{
	if (vNode.empty())return nullptr;

	Node* pNodeMost = *vNode.begin();

	float fMost = pNodeMost->boundingBox().size.height;

	VectorNode::const_iterator itr;
	foreach(itr,vNode){
		Node* pNode = *itr;
		float fHeight = pNode->boundingBox().size.height ;
		if (fHeight > fMost)
		{
			fMost = fHeight;
			pNodeMost = pNode;
		}
	}

	return pNodeMost;
}

Node* ApiCocos2dx::FindNodeByBoundingBoxMostHigh(const Vector<Node*>& vNode)
{
	if (vNode.empty())return nullptr;

	Node* pNodeMost = *vNode.begin();

	float fMost = pNodeMost->boundingBox().size.height;

	VectorNode::const_iterator itr;
	foreach(itr,vNode){
		Node* pNode = *itr;
		float fHeight = pNode->boundingBox().size.height ;
		if (fHeight > fMost)
		{
			fMost = fHeight;
			pNodeMost = pNode;
		}
	}

	return pNodeMost;
}

Point ApiCocos2dx::GetCenterByBoundingBox( Node* pNode )
{
	Rect rRect = pNode->boundingBox();

	return ccp(rRect.origin.x + rRect.size.width / 2 ,rRect.origin.y + rRect.size.height / 2);
}

bool ApiCocos2dx::GetParentNodes( VectorNode& vNodes,Node* pNode )
{
	while(pNode){
		vNodes.push_back(pNode);
		pNode = pNode->getParent();
	}
	return true;
}

class CNodePathTemp
{
public:
	Node* pNode;
	VectorNode vPath;
public:
	// 		//是否在后面
	bool operator < (const CNodePathTemp& rTemp)const
	{
		//路径的比较:
		//思路:通过前一步骤输入至此的必然是类似这样的路径:
		//nullptr/CCSence/CCLayer/Sprite
		//nullptr/CCSence/CCLayer/CCButton
		//nullptr/CCSence/CCButton
		//nullptr/CCSence/CCButton/CCButton
		//因此我们只需要从头比较过去就可以了。因为前面部分必然是一样的。
		//若不一样。我们认为，起始节点不为Sence的是不显示的节点,我们将其视为最底层
		//我们定义 底 < 高

		//两个都是不可见节点
		if (vPath.empty() && rTemp.vPath.empty())
			return pNode < rTemp.pNode;//随意找个规则返回

		//一个可见一个不可见
		if (vPath.empty() && !rTemp.vPath.empty())
			return true;
		if (!vPath.empty() && rTemp.vPath.empty())
			return false;

		//将是否可见的 和 不可见的进行比较 比较根节点
		{
			Node* pNodeA = *vPath.rbegin();
			Node* pNodeB = *rTemp.vPath.rbegin();

			CCScene* pSceneA = nullptr;
			CCScene* pSceneB = nullptr;
			
			ASSERT_LOG_ERROR(ToolFrame::DynamicCast(pSceneA,pNodeA));
			ASSERT_LOG_ERROR(ToolFrame::DynamicCast(pSceneB,pNodeB));

			if (pSceneA && !pSceneB)return false;
			if (!pSceneA && pSceneB)return true;
			if (!pSceneA && !pSceneB)return pNode < rTemp.pNode;

			//我们认为所有节点的根节点至多来自同一个Scene
			ASSERT_LOG_ERROR(pSceneA && pSceneB && pSceneA == pSceneB);
		}

		//开始从头比较
		VectorNode::const_reverse_iterator itr1;
		VectorNode::const_reverse_iterator itr2;
		foreachDoubleR(itr1,vPath,itr2,rTemp.vPath){
			Node* pNodeA = *itr1;
			Node* pNodeB = *itr2;

			ASSERT_LOG_ERROR(pNodeA);
			ASSERT_LOG_ERROR(pNodeB);

			if (pNodeA == pNodeB)continue;//若当前节点一样,说明是父节点,则比较下一个

			//若当前节点不一样,则比较两者在父节点中的前后次序
			ASSERT_LOG_ERROR(pNodeA->getParent() == pNodeB->getParent());

			Node* pParent = pNodeA->getParent();
			ASSERT_LOG_ERROR(pParent);

			const Vector<Node*>& vChildren = pParent->getChildren();

			return vChildren.getIndex(pNodeA) < vChildren.getIndex(pNodeB);
		}

		//若运行到此,则只有可能在前面的比较中,所有已知节点都是一样的,也就是说要么是自己和自己比较,要么就是父节点和子节点比较。
		
		ASSERT_LOG_ERROR(vPath.size() != rTemp.vPath.size());//我们认为 不可以自己和自己比较
		//如果是 父节点 和 子节点比较,那么比较长的那个是子节点,我们定义认为在前面
		return vPath.size() < rTemp.vPath.size() ;
	}

	//让指针支持比较 加速
	FUN_PTR_CMP(CNodePathTemp);

};

//按照前后层次关系进行排序
//思路:利用Map的有序性,将节点的parent的parent....视为路径。
//通过重载比较符来使得树有序。
bool ApiCocos2dx::SortByTop( VectorNode& vNodes )
{
	typedef std::set<CNodePathTemp*,CNodePathTemp> SetTemp;
	SetTemp vTemp;

	{
		VectorNode::const_iterator itr;
		foreach(itr,vNodes){
			Node* pNode = *itr;
			ASSERT_LOG_ERROR(pNode);

			CNodePathTemp* temp = new CNodePathTemp();
			temp->pNode = pNode;
			GetParentNodes(temp->vPath,pNode);

			vTemp.insert(temp);
		}
	}

	//返回结果
	{
		ASSERT_LOG_ERROR(vNodes.size() == vTemp.size());
		vNodes.clear();

		SetTemp::reverse_iterator itr;
		foreachR(itr,vTemp){
			CNodePathTemp* pTemp = *itr;
			ASSERT_LOG_ERROR(pTemp);
			vNodes.push_back(pTemp->pNode);
		}
	}

	//收尾
	ToolFrame::Delete(vTemp);
	return true;
}

bool ApiCocos2dx::SetZOrder( Node* pNode,int nZOrder )
{
	if (!pNode)return false;
	if (!pNode->getParent())return false;

	pNode->getParent()->reorderChild(pNode,nZOrder);
	return true;
}

Point ApiCocos2dx::GetWorldPostion(const Node* pNode )
{
	return pNode->getParent()->convertToWorldSpace(pNode->getPosition());
}

Vec2 ApiCocos2dx::GetWorldAnchorPointInPoints( Node* pNode )
{
	return pNode->getParent()->convertToWorldSpace(pNode->getAnchorPointInPoints()+pNode->getPosition());
}

bool ApiCocos2dx::SetWorldPostion( Node* pNode,const Point& ptWorld )
{
	if (!pNode)return false;
	if (!pNode->getParent())return false;
	pNode->setPosition(pNode->getParent()->convertToNodeSpace(ptWorld));
	return true;
}

bool ApiCocos2dx::SetWorldPostion( Node* pNode,const Node* pOther )
{
	if (!pNode)return false;
	if (!pOther)return false;
	return SetWorldPostion(pNode,GetWorldPostion(pOther));
}

Node* ApiCocos2dx::FindLastNode( CCArray* pArray )
{
	if (ApiCocos2dx::IsEmpty(pArray))return nullptr;

	Node* pNode = nullptr;

	ToolFrame::DynamicCast(pNode,pArray->lastObject());

	return pNode;
}

Node* ApiCocos2dx::FindFirstNode(CCArray* pArray )
{
	if (ApiCocos2dx::IsEmpty(pArray))return nullptr;

	Node* pNode = nullptr;

	ToolFrame::DynamicCast(pNode,pArray->objectAtIndex(0));

	return pNode;
}

bool ApiCocos2dx::IsEmpty( CCArray* pArray )
{
	if (!pArray)return true;
	return 0==pArray->count();
}

Node* ApiCocos2dx::FindNodeAtIndex( CCArray* pArray,UINT uIndex)
{
	if (IsEmpty(pArray))return nullptr;

	Node* pNode = nullptr;
	ToolFrame::DynamicCast(pNode,pArray->objectAtIndex(uIndex));
	return pNode;
}

Rect ApiCocos2dx::GetWorldBoundingBox(const Node* pNode )
{
	if (!pNode)return Rect::ZERO;
	if (!pNode->getParent())return Rect::ZERO;

	Rect rRect = pNode->getBoundingBox();
	rRect.origin = pNode->getParent()->convertToWorldSpace(rRect.origin);
	rRect.size	 = ApiCocos2dx::CalWorldSize(rRect.size,pNode->getParent());
	return rRect;
}

bool ApiCocos2dx::SetWorldBoundingBox( Node* pNode,const Rect& rWorld )
{
	if (!pNode)return false;

	const Rect rRect			= pNode->getBoundingBox();
	const Point& ptAnchorPoint	= pNode->getAnchorPoint();
	Point ptWorldPosition		= ccp(rWorld.origin.x + rWorld.size.width*ptAnchorPoint.x, rWorld.origin.y + rWorld.size.height*ptAnchorPoint.y);//计算世界中的位置坐标

	//设置位置坐标
	pNode->setPosition(CalPointInParent(ptWorldPosition, pNode));

	//调整大小
	if (rRect.size.width > 0 || rRect.size.height > 0)
	{
		Size rDes = CalSizeInParent(rWorld.size, pNode);

		//当前绑定盒转换世界大小的缩放比
		float fRateX = rDes.width / rRect.size.width;
		float fRateY = rDes.height / rRect.size.height;
		pNode->setScaleX(pNode->getScaleX() * fRateX);
		pNode->setScaleY(pNode->getScaleY() * fRateY);
	}
	return true;
}

bool ApiCocos2dx::SetWorldBoundingBox(Node* pNode, const Rect& rWorld, const Point& ptWorldPosition)
{
	if (!pNode)return false;

	const Rect rRect = pNode->getBoundingBox();

	//设置位置坐标
	pNode->setPosition(CalPointInParent(ptWorldPosition, pNode));

	//调整大小
	if (rRect.size.width > 0 || rRect.size.height > 0)
	{
		Size rDes = CalSizeInParent(rWorld.size, pNode);

		//当前绑定盒转换世界大小的缩放比
		float fRateX = rDes.width / rRect.size.width;
		float fRateY = rDes.height / rRect.size.height;
		pNode->setScaleX(pNode->getScaleX() * fRateX);
		pNode->setScaleY(pNode->getScaleY() * fRateY);
	}
	return true;
}

Point ApiCocos2dx::Subtract( const Point& a,const Point& b )
{
	return ccp(a.x - b.x,a.y-b.y);
}

Size ApiCocos2dx::CalWorldSize( const Size& rSizeNode,const Node* pNode )
{
	Point ptZero(0,0);
	Point ptSize(rSizeNode.width,rSizeNode.height);

	ptZero = pNode->convertToWorldSpace(ptZero);
	ptSize = pNode->convertToWorldSpace(ptSize);

	Point ptResult = Subtract(ptSize,ptZero);
	return Size(ptResult.x,ptResult.y);
}

Size ApiCocos2dx::CalSizeInParent(const Size& rSizeWorld,Node* pNode )
{
	Point ptZero(0,0);
	Point ptSize(rSizeWorld.width,rSizeWorld.height);
	ptZero = pNode->getParent()->convertToNodeSpace(ptZero);
	ptSize = pNode->getParent()->convertToNodeSpace(ptSize);

	Point ptResult = Subtract(ptSize,ptZero);
	return Size(ptResult.x,ptResult.y);
}

Point ApiCocos2dx::CalPointInParent( const Point& ptWorld,Node* pNode )
{
	return pNode->getParent()->convertToNodeSpace(ptWorld);
}

Point ApiCocos2dx::CalPointInNode( const Point& ptWorld,Node* pNode )
{
	return pNode->convertToNodeSpace(ptWorld);
}

Point ApiCocos2dx::GetRectCenterPoint( const Rect& rRect )
{
	return ccp(rRect.origin.x + rRect.size.width/2,rRect.origin.y + rRect.size.height/2);
}

bool ApiCocos2dx::SetWorldingBoundingWithOther( Node* pNode, Node* pOther )
{
	if (!pNode)return false;
	ApiCocos2dx::SetWorldBoundingBox(pNode,ApiCocos2dx::GetWorldBoundingBox(pOther),ApiCocos2dx::GetWorldPostion(pOther));
	return true;
}

Point ApiCocos2dx::GetWorldCenter(const Node* pNode )
{
	return pNode->convertToWorldSpace(GetContentSizeCenter(pNode));
}

Point ApiCocos2dx::GetWorldCenter( const Node* pNode,const Point& pt )
{
	return pNode->convertToWorldSpace(GetContentSizeCenter(pNode,pt));
}

bool ApiCocos2dx::SetWorldCenterWithOther( Node* pNode,const Node* pOther )
{
	if (!pNode)return false;
	if (!pOther)return false;

	return SetWorldPostion(pNode,GetWorldCenter(pOther));
}

Point ApiCocos2dx::GetContentSizeCenter(const Node* pNode )
{
	static Point s_pt = ccp(0.5,0.5);
	return GetContentSizeCenter(pNode,s_pt);
}

Point ApiCocos2dx::GetContentSizeCenter( const Node* pNode,const Point& pt )
{
	const Size& rSize = pNode->getContentSize();
	return ccp(rSize.width * pt.x,rSize.height * pt.y);
}

bool ApiCocos2dx::IsChildEmpty(const  Node* pNode )
{
	return pNode->getChildren().empty();
}

UINT ApiCocos2dx::GetChildCount( Node* pNode )
{
	return pNode->getChildren().size();
}

Node* ApiCocos2dx::FindChildByIndex( Node* pNode,uint uIndex )
{
	if (!pNode)return nullptr;

	if (pNode->getChildren().empty())return nullptr;
	
	if (!ToolFrame::IsInClosedInterval(uIndex,0,pNode->getChildren().size()-1))return nullptr;

	return pNode->getChildren().at(uIndex);
}

bool ApiCocos2dx::RemoveChildByTag( Node* pWidget,int tag, bool cleanup){
	if(!pWidget)return false;

	 Node* pNode = pWidget->getChildByTag(tag);
	 if (!pNode)return false;

	pWidget->removeChild(pNode,cleanup);
	return true;
}

UINT ApiCocos2dx::GetCount( CCArray* pArray )
{
	if (!pArray)return 0;

	return pArray->count();
}

std::string ApiCocos2dx::GetWriteableDir(){
	return CCFileUtils::sharedFileUtils()->getWritablePath();
}

// CCRenderTexture* ApiCocos2dx::CreateStroke( CCLabelTTF* pFont,float fFontSize,const ccColor3B& ccColor )
// {
// 	//参考自 http://www.cocos2d-iphone.org/forum/topic/12126
// 
// 	Point		ptOrigialPos		= pFont->getPosition();
// 	ccColor3B	clrOriginal			= pFont->getColor();
// 	ccBlendFunc	originalBlend		= pFont->getBlendFunc();
// 	bool				bOriginalVisibility = pFont->isVisible();
// 
// 	Size rSizeContent = pFont->getContentSize();
// 	rSizeContent.width	+= fFontSize * 2;
// 	rSizeContent.height += fFontSize * 2;
// 
// 	CCRenderTexture* rt =CCRenderTexture::create(int(rSizeContent.width),int(rSizeContent.height));
// 
// 	pFont->setColor(ccColor);
// 	pFont->setVisible(true);
// 
// 	ccBlendFunc newBlend ;
// 	newBlend.src = GL_SRC_ALPHA;
// 	newBlend.dst = GL_ONE;
// 	pFont->setBlendFunc(newBlend);
// 
// 	const Size& rTextureSize = pFont->getTexture()->getContentSize();
// 	const Point& ptAnchorPoint	 = pFont->getAnchorPointInPoints();
// 	Point ptBottomLeft= ccp(ptAnchorPoint.x + fFontSize,ptAnchorPoint.y + fFontSize);
// 	Point	ptPosOffSet = ccp(ptAnchorPoint.x - rTextureSize.width/2,ptAnchorPoint.y - rTextureSize.height/2);
// 	Point	ptPostion	= ccpSub(ptOrigialPos,ptPosOffSet);
// 
// 	rt->begin();
// 	for (int i=0; i<360; i+=15)
// 	{
// 		pFont->setPosition(ccp(ptBottomLeft.x + sin(CC_DEGREES_TO_RADIANS(i))*fFontSize, ptBottomLeft.y + cos(CC_DEGREES_TO_RADIANS(i))*fFontSize));
// 		pFont->visit();
// 	}
// 	rt->end();
// 
// 	pFont->setPosition(ptOrigialPos);
// 	pFont->setColor(clrOriginal);
// 	pFont->setBlendFunc(originalBlend);
// 	pFont->setVisible(bOriginalVisibility);
// 
// 	rt->setPosition(ptPostion);
// 	rt->setContentSize(rSizeContent);
// 
// 	// 	rt->setIsRelativeAnchorPoint(true);
// 	// 	rt->setAnchorPoint(ccp(0.5,0.5));
// 
// 
// 	return rt;
// }

bool ApiCocos2dx::SetString( LabelTTF* pNode,const std::string& sString )
{
	if (!pNode)return false;
	pNode->setString(sString.c_str());
	return true;
}

bool ApiCocos2dx::SetTexture( Sprite* pSprite,const std::string& sPath )
{
	if (!pSprite)return false;
	pSprite->setTexture(ApiCocos2dx::CacheTexture(sPath));
	return true;
}

ccColor3B ApiCocos2dx::ToColor( UINT32 uColor )
{
	return Color3B(GLubyte(uColor/0xffff%0xff),GLubyte(uColor/0xff%0xff),GLubyte(uColor%0xff));
}

std::string	ApiCocos2dx::LoadFile( const std::string& sFileName )
{
	ssize_t uSize=0;
	unsigned char * pBuffer = CCFileUtils::sharedFileUtils()->getFileData(sFileName.c_str(), "rt", &uSize);
	if (!pBuffer) return "";

	std::string sFile = (const char*)pBuffer;
	CC_SAFE_DELETE_ARRAY(pBuffer);
	return sFile;
}

bool ApiCocos2dx::SetPointSize( float fSize )
{
#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	glPointSize(fSize);
#else
	ccPointSize(fSize);
#endif
	return true;
}

bool ApiCocos2dx::Release( VectorNode& vNode )
{
	VectorNode::iterator itr;
	foreach(itr,vNode){
		(*itr)->release();
	}
	vNode.clear();

	return true;
}

bool ApiCocos2dx::SetContentSizeWithScreenSize( Node* pNode )
{
	if (!pNode)return false;
	pNode->setContentSize(CCDirector::sharedDirector()->getWinSize());
	return true;
}

bool ApiCocos2dx::SetDesignResolutionSize( float fWidth,float fHeight )
{
	if (0.0f == fWidth)
		fWidth  = CCDirector::sharedDirector()->getWinSize().width * fHeight / CCDirector::sharedDirector()->getWinSize().height;
	if (0.0f == fHeight)
		fHeight = CCDirector::sharedDirector()->getWinSize().height * fWidth / CCDirector::sharedDirector()->getWinSize().width;
	
	Director::getInstance()->getOpenGLView()->setDesignResolutionSize(fWidth, fHeight,kResolutionShowAll);
	return true;
}

bool ApiCocos2dx::SetContentSizeWithDesignSize( Node* pNode )
{
	if (!pNode)return false;
	pNode->setContentSize(Director::getInstance()->getOpenGLView()->getDesignResolutionSize());
	return true;
}

bool ApiCocos2dx::SetContentSizeWithDesignSize( Node* pNode,bool bWidth )
{
	if (!pNode)return false;
	const Size& sizeDesign = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
	
	Size sizeContent = pNode->getContentSize();

	if (bWidth)
		sizeContent.width = sizeDesign.width;
	else
		sizeContent.height = sizeDesign.height;

	pNode->setContentSize(sizeContent);
	return true;
}

bool ApiCocos2dx::ActionsTurnOver( Node* pFace,Node* pBack,float fTurnTime,float fDelayTime )
{
	float fHalfTurnOver = fTurnTime / 4.0f;
	//设置正面
	{
		CCFiniteTimeAction *seq = CCSequence::create(CCScaleTo::create(fHalfTurnOver,0,1),CCHide::create(),CCDelayTime::create(fHalfTurnOver * 2 + fDelayTime),CCShow::create(),CCScaleTo::create(fHalfTurnOver,1,1),nullptr);
		pFace->runAction(seq);
	}
	//设置背面
	{
		pBack->setPosition(pFace->getPosition());
		pBack->setScaleX(0);
		pBack->setScaleY(1);
		pBack->setVisible(false);

		CCFiniteTimeAction *seq = CCSequence::create(CCDelayTime::create(fHalfTurnOver),CCShow::create(),CCScaleTo::create(fHalfTurnOver,1,1),CCDelayTime::create(fDelayTime),CCScaleTo::create(fHalfTurnOver,0,1),CCHide::create(),CCRemoveSelf::create(),nullptr);
		pBack->runAction(seq);

		pFace->getParent()->addChild(pBack);
	}
	return true;
}

Sprite* ApiCocos2dx::ApiEffectSpriteShow(float fVisibleTime,float fFade, float fDelay,const std::string& sPath )
{
	Sprite* pSprite = Sprite::create(sPath.c_str());
	if (!pSprite)return nullptr;

	pSprite->setPosition(GetScreenCenterPoint());

	Vector<FiniteTimeAction*> vArray;

	if (fVisibleTime > 0.0f)
	{
		CCFiniteTimeAction*  pAcVisibleFalse= CCHide::create();
		CCFiniteTimeAction*  pAcVisibleTime	= CCDelayTime::create(fVisibleTime);
		CCFiniteTimeAction*  pAcVisibleTrue	= CCShow::create();

		vArray.pushBack(pAcVisibleFalse);
		vArray.pushBack(pAcVisibleTime);
		vArray.pushBack(pAcVisibleTrue);
	}

	CCFiniteTimeAction*  pAcFadeIn	= CCFadeIn::create(fFade);
	CCFiniteTimeAction*  pAcDelay	= CCDelayTime::create(fDelay);
	CCFiniteTimeAction*  pAcFadeOut	= CCFadeOut::create(fFade);
	CCFiniteTimeAction*  pAcRemove	= CCRemoveSelf::create();

	vArray.pushBack(pAcFadeIn);
	vArray.pushBack(pAcDelay);
	vArray.pushBack(pAcFadeOut);
	vArray.pushBack(pAcRemove);

	pSprite->runAction(CCSequence::create(vArray));

	return pSprite;
}

bool ApiCocos2dx::ActionsSpriteShow( Node* pNode,float fFade, float fDelay,const std::string& sPath )
{
	VectorString vPath;
	vPath.push_back(sPath);

	return ActionsSpriteShow(pNode,fFade,fDelay,vPath);
}

bool ApiCocos2dx::ActionsSpriteShow( Node* pNode,float fFade, float fDelay,const std::string& sPath ,SEL_CallFunc fnCallBack )
{
	VectorString vPath;
	vPath.push_back(sPath);

	return ActionsSpriteShow(pNode,fFade,fDelay,vPath,fnCallBack);
}

bool ApiCocos2dx::ActionsSpriteShow( Node* pNode,float fFade, float fDelay,const std::string& sPath1 ,const std::string& sPath2 )
{
	VectorString vPath;
	vPath.push_back(sPath1);
	vPath.push_back(sPath2);

	return ActionsSpriteShow(pNode,fFade,fDelay,vPath);
}

bool ApiCocos2dx::ActionsSpriteShow( Node* pNode,float fFade, float fDelay,const std::string& sPath1 ,const std::string& sPath2,SEL_CallFunc fnCallBack )
{
	VectorString vPath;
	vPath.push_back(sPath1);
	vPath.push_back(sPath2);

	return ActionsSpriteShow(pNode,fFade,fDelay,vPath,fnCallBack);
}

bool ApiCocos2dx::ActionsSpriteShow( Node* pNode,float fFade, float fDelay,const VectorString& vPath )
{
	if (!pNode)return false;

	for (uint uIndex =0;uIndex<vPath.size();++uIndex)
	{
		Sprite* pSprite = ApiEffectSpriteShow(uIndex * (2.0f * fFade +  fDelay),fFade,fDelay,vPath[uIndex]);
		if (!pSprite)return false;

		pNode->addChild(pSprite);
	}
	return true;
}

bool ApiCocos2dx::ActionsSpriteShow( Node* pNode,float fFade, float fDelay,const VectorString& vPath ,SEL_CallFunc fnCallBack )
{
	if (!ActionsSpriteShow(pNode,fFade,fDelay,vPath))return false;

	CCFiniteTimeAction*  pAcDelay = CCDelayTime::create(vPath.size() * (2.0f * fFade +  fDelay));
	CCFiniteTimeAction*  pAcCallBack = CCCallFunc::create(pNode,fnCallBack);

	pNode->runAction(CCSequence::create(pAcDelay,pAcCallBack,nullptr));

	return true;

}

bool ApiCocos2dx::AddTouchEvent( VectorNode& vWidget,Ref* target,SEL_TouchEvent selector )
{
	VectorNode::const_iterator itr;
	foreach(itr,vWidget){
		AddTouchEvent(*itr,target,selector);
	}
	return true;
}

bool ApiCocos2dx::AddTouchEvent( Node* pWidget,Ref* target,SEL_TouchEvent selector )
{
	if (!pWidget)return false;

	Widget* pNode = dynamic_cast<Widget*>(pWidget);
	if (!pNode)return false;

	pNode->addTouchEventListener(target,selector);
	return true;
}

bool ApiCocos2dx::AddTouchEvent( Node* pWidgetRoot,const std::string& sName,Ref* target,SEL_TouchEvent selector )
{
	Node* pWidget = ApiCocos2dx::FindNode(pWidgetRoot,sName);
	if (!pWidget)return false;

	return ApiCocos2dx::AddTouchEvent(pWidget,target,selector);
}

bool ApiCocos2dx::AddTouchEvent( Node* pWidget,Widget::ccWidgetTouchCallback fnCallBack )
{
	if (!pWidget)return false;
	
	Widget* pNode = dynamic_cast<Widget*>(pWidget);
	if (!pNode)return false;

	pNode->addTouchEventListener(fnCallBack);
	return true;
}

bool ApiCocos2dx::SetClickCallBack(Widget* pNode, Widget::ccWidgetClickCallback fn)
{
	if (!pNode)return false;

	pNode->addClickEventListener(fn);
	return true;
}

bool ApiCocos2dx::SetClickCallBack(Node* pRoot, const std::string& sName, Widget::ccWidgetClickCallback fn)
{
	Widget* pNode = ApiCocos2dx::FindNode<Widget>(pRoot, sName);
	if (!pNode)return false;
	
	return SetClickCallBack(pNode, fn);
}

bool ApiCocos2dx::SetTouchCallBack(Widget* pNode, Widget::ccWidgetTouchCallback fn)
{
	if (!pNode)return false;

	pNode->addTouchEventListener(fn);
	return true;
}

bool ApiCocos2dx::SetTouchCallBack(Node* pRoot, const std::string& sName, Widget::ccWidgetTouchCallback fn)
{
	Widget* pNode = ApiCocos2dx::FindNode<Widget>(pRoot, sName);
	if (!pNode)return false;

	return SetTouchCallBack(pNode, fn);
}

Node* ApiCocos2dx::LoadUIFile(const std::string& sFileName)
{
	return CSLoader::getInstance()->createNodeWithVisibleSize(sFileName);
}

int ApiCocos2dx::GetChildZOrderMax(const Node* pNode )
{
	const Vector<Node*>& vChildren = pNode->getChildren();
	if (vChildren.empty())return 0;

	Vector<Node*>::const_iterator itr = vChildren.begin();
	int nZOrder = (*itr)->getLocalZOrder();
	++itr;
	while (itr != vChildren.end())
	{
		const Node* pNodeChild = *itr;
		ASSERT_LOG_ERROR(pNodeChild);
		if (nZOrder < pNodeChild->getLocalZOrder())
			nZOrder = pNodeChild->getLocalZOrder();
		++itr;
	}

	return nZOrder;
}

bool ApiCocos2dx::AddChildTop( Node* pParent,Node* pChild )
{
	if (!pParent)return false;
	if (!pChild)return false;
	
	pParent->addChild(pChild,GetChildZOrderMax(pParent)+1);
	return true;
}

bool ApiCocos2dx::SetValue( TextAtlas* pWidget,int nValue )
{
	if (nValue < 0)
		return false;
	pWidget->setString(ToolFrame::ToString(nValue));
	return true;
}

bool ApiCocos2dx::SetValue( TextAtlas* pWidget,const std::string& sValue )
{
	pWidget->setString(sValue);
	return true;
}

bool ApiCocos2dx::SetValue( TextAtlas* pWidget,int nValue,const std::string& sTexturePath )
{
	if (nValue < 0)
		return false;
	return ApiCocos2dx::SetValue(pWidget,ToolFrame::ToString(nValue),sTexturePath);
}

bool ApiCocos2dx::SetValue( TextAtlas* pWidget,const std::string& sValue,const std::string& sTexturePath )
{
	if (!pWidget)return false;
	
	const Texture2D* pTexture2D = ApiCocos2dx::CacheTexture(sTexturePath);
	if (!pTexture2D)return false;

	int nFontWidth = pTexture2D->getPixelsWide()/10;
	int nFontHeigh = pTexture2D->getPixelsHigh();
	pWidget->setProperty(sValue,sTexturePath,nFontWidth,nFontHeigh,"0");
	return true;
}

bool ApiCocos2dx::SetValue( Text* pWidget,const std::string& sValue )
{
	return ApiCocos2dx::SetText(pWidget,sValue);
}

bool ApiCocos2dx::SetValue( Text* pWidget,const int& nValue )
{
	return ApiCocos2dx::SetText(pWidget,ToolFrame::ToString(nValue));
}
bool ApiCocos2dx::SetValue( Text* pWidget,const float& fValue )
{
	return ApiCocos2dx::SetText(pWidget,ToolFrame::ToString(fValue));
}

bool ApiCocos2dx::SetValue( LoadingBar* pWidget,int nValue )
{
	if (!pWidget)return false;

	if (nValue<0)nValue = 0;
	if (nValue>100)nValue = 100;
	pWidget->setPercent(nValue);
	return true;
}

bool ApiCocos2dx::SetValue( LoadingBar* pWidget,float fValue )
{
	return SetValue(pWidget,int(fValue));
}

bool ApiCocos2dx::SetValue( LoadingBar* pWidget,int nCur,int nMax )
{
	if (0 == nMax)return false;
	return SetValue(pWidget,int(1.0f * nCur / nMax * 100));
}

bool ApiCocos2dx::SetValue( ImageView* pWidget,const std::string& sPath,Widget::TextureResType texType)
{
	if (!pWidget)return false;
	if (sPath.empty())return false;

	return LoadTexture(pWidget, sPath, texType);
}

bool ApiCocos2dx::SetValue( Layout* pWidget,const std::string& sPath,Widget::TextureResType texType /*= Widget::TextureResType::LOCAL*/ )
{
	if (!pWidget)return false;
	if (sPath.empty())return false;

	pWidget->setBackGroundImage(sPath,texType);
	return true;
}

bool ApiCocos2dx::SetGroupVisible( Node* pRootWidget,const std::string& sName,int nCount,int nValue )
{
	VectorNode vWidget;
	if (!ApiCocos2dx::FindNode(vWidget,pRootWidget,sName,nCount))return false;

	for (uint nIndex =0;nIndex<vWidget.size();++nIndex)
		vWidget[nIndex]->setVisible((int)nIndex < nValue);

	return true;
}

bool ApiCocos2dx::SetValue( CheckBox* pWidget,bool bChecked )
{
	if (!pWidget)return false;

	pWidget->setSelectedState(bChecked);
	return true;
}

bool ApiCocos2dx::SetValue( Button* pWidget,const std::string& sValue,Widget::TextureResType texType)
{
	if (sValue.empty())return false;

	return LoadTexture(pWidget,sValue,texType);
}

bool ApiCocos2dx::SetValue( Button* pWidget,const char* szValue,Widget::TextureResType texType)
{
	if (!szValue)return false;
	return LoadTexture(pWidget,szValue,texType);
}

bool ApiCocos2dx::SetValue( TextField* pWidget,const std::string& sValue )
{
	return ApiCocos2dx::SetText(pWidget,sValue);
}

bool ApiCocos2dx::SetValue( LabelBMFont* pWidget,int nValue )
{
	if (!pWidget)return false;

	pWidget->setString(MAKE_STRING(nValue));
	return true;
}

bool ApiCocos2dx::SetValue( LabelBMFont* pWidget,const std::string& sValue )
{
	if (!pWidget)return false;

	pWidget->setString(sValue);
	return true;
}

bool ApiCocos2dx::SetValue( LabelBMFont* pWidget,int nValue,const std::string& sFontPath )
{
	if (!pWidget)return false;

	pWidget->setFntFile(sFontPath);
	pWidget->setString(MAKE_STRING(nValue));
	return true;
}

bool ApiCocos2dx::SetValue( LabelBMFont* pWidget,const std::string& sValue,const std::string& sFontPath )
{
	if (!pWidget)return false;

	pWidget->setFntFile(sFontPath);
	pWidget->setString(sValue);
	return true;
}

bool ApiCocos2dx::SetValue( TextBMFont* pWidget,int nValue )
{
	if (!pWidget)return false;

	pWidget->setString(MAKE_STRING(nValue));
	return true;
}

bool ApiCocos2dx::SetValue( TextBMFont* pWidget,const std::string& sValue )
{
	if (!pWidget)return false;

	pWidget->setString(sValue);
	return true;
}

bool ApiCocos2dx::SetValue( TextBMFont* pWidget,int nValue,const std::string& sFontPath )
{
	if (!pWidget)return false;

	pWidget->setFntFile(sFontPath);
	pWidget->setString(MAKE_STRING(nValue));
	return true;
}

bool ApiCocos2dx::SetValue( TextBMFont* pWidget,const std::string& sValue,const std::string& sFontPath )
{
	if (!pWidget)return false;

	pWidget->setFntFile(sFontPath);
	pWidget->setString(sValue);
	return true;
}

bool ApiCocos2dx::SetVisible( Node* pWidget,bool bVisible )
{
	if (!pWidget)return false;

	pWidget->setVisible(bVisible);
	return true;
}

bool ApiCocos2dx::SetVisible( Widget* pWidget,bool bVisible )
{
	if (!pWidget)return false;

	pWidget->setVisible(bVisible);
	return true;
}

bool ApiCocos2dx::SetVisible(const VectorNode& vWidget,bool bVisible )
{
	VectorNode::const_iterator itr;
	foreach(itr,vWidget){
		Node* pWidget = *itr;
		ASSERT_LOG_ERROR(pWidget);

		ApiCocos2dx::SetVisible(pWidget,bVisible);
	}

	return true;
}

bool ApiCocos2dx::SetVisible( Node* pRootWidget,const std::string& sName,int nCount,bool bVisible )
{
	VectorNode vWidget;
	ASSERT_LOG_ERROR(ApiCocos2dx::FindNode(vWidget,pRootWidget,sName,nCount));

	return ApiCocos2dx::SetVisible(vWidget,bVisible);
}

bool ApiCocos2dx::SetVisible( Node* pRootWidget,const std::string& sName,bool bVisible )
{
	Node* pWidget = ApiCocos2dx::FindNode(pRootWidget,sName);
	if (!pWidget)return false;

	return ApiCocos2dx::SetVisible(pWidget,bVisible);
}

bool ApiCocos2dx::Clear( ListView* pLv )
{
	if (!pLv)return false;
	pLv->removeAllItems();
	return true;
}

bool ApiCocos2dx::Clear( PageView* pPv )
{
	if (!pPv)return false;
	pPv->removeAllPages();
	return true;
}

bool ApiCocos2dx::PushBack( ListView* pLv,Node* pNode )
{
	if (!pLv  || !pNode)return false;
	Widget* pWidget = dynamic_cast<Widget*>(pNode);
	if (!pWidget)return false;
	pLv->pushBackCustomItem(pWidget);
	return true;
}

bool ApiCocos2dx::PushBack( PageView* pPageView,Node* pNode )
{
	if (!pPageView  || !pNode)return false;
	if (pNode->getParent())return false;

	Widget* pWidget = dynamic_cast<Widget*>(pNode);
	if (!pWidget)return false;

	Layout* pLayout = dynamic_cast<Layout*>(pWidget);
	if (pLayout)
	{
		pPageView->addPage(pWidget);
		return true;
	}

	pLayout = Layout::create();
	if (!pLayout)return false;

	pLayout->setSize(pPageView->getSize());
	pLayout->addChild(pWidget);

	ApiCocos2dx::SetPostionCenter(pWidget);

	pPageView->addPage(pLayout);
	return true;
}

CheckBox* ApiCocos2dx::AddEventListenerCheckBox( const Node* pRootWidget,const std::string& sName,Ref* target,SEL_SelectedStateEvent selector )
{
	CheckBox* pCheckBox = nullptr;
	if (!ApiCocos2dx::FindNode(pCheckBox,pRootWidget,sName))return nullptr;

	return AddEventListenerCheckBox(pCheckBox,target,selector);
}

CheckBox* ApiCocos2dx::AddEventListenerCheckBox( CheckBox* pCheckBox,Ref* target,SEL_SelectedStateEvent selector )
{
	if (!pCheckBox)return nullptr;
	pCheckBox->addEventListenerCheckBox(target,selector);
	return pCheckBox;
}

bool ApiCocos2dx::SetGray(Node* pNode, bool bGray, bool bChildren)
{
	if (!pNode)return false;
	
	//先设置自己的灰色状态
	pNode->setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(bGray ? GLProgram::SHADER_NAME_POSITION_GRAYSCALE: GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));
	
	//再设置孩子的灰色状态
	if (bChildren)
	{
		const Vector<Node*>& vChildren = pNode->getChildren();
		Vector<Node*>::const_iterator itr;
		foreach(itr, vChildren) {
			SetGray(*itr, bGray,bChildren);
		}
	}
	
	return true;
}

bool ApiCocos2dx::SetGray(Node* pRoot, const std::string& sName, bool bGray, bool bChildren)
{
	Node* pNode = FindNode(pRoot, sName);
	if (!pNode)return false;
	return SetGray(pNode, bGray, bChildren);
}

bool ApiCocos2dx::SetGray(VectorNode& vNode, bool bGray, bool bChildren)
{
	if (vNode.empty())return true;

	VectorNode::iterator itr;
	foreach(itr, vNode) {
		ApiCocos2dx::SetGray(*itr, bGray, bChildren);
	}

	return true;
}

bool ApiCocos2dx::IsChecked(CheckBox* pWidget)
{
	return pWidget->getSelectedState();
}

bool ApiCocos2dx::IsChecked( Widget* pRootWidget,const std::string& sName )
{
	CheckBox* pCbBtn = nullptr;
	if (!ApiCocos2dx::FindNode(pCbBtn,pRootWidget,sName))return false;
	return pCbBtn->getSelectedState();
}

bool ApiCocos2dx::IsTargetWidget(const Ref* pObj,const std::string& sName)
{
	if (!pObj)return false;
	if (sName.empty())return false;

	const Widget* pWidget = dynamic_cast<const Widget*>(pObj);
	if (!pWidget)return false;

	return sName == pWidget->getName();
}

bool ApiCocos2dx::IsTargetWidgetRange(const Ref* pObj,const std::string& sName,int nBegin,int nEnd )
{
	if (!pObj)return false;
	if (sName.empty())return false;

	const Widget* pWidget = dynamic_cast<const Widget*>(pObj);
	if (!pWidget)return false;

	std::string sFormat = sName + "%d";int n=0;
	sscanf(pWidget->getName().c_str(),sFormat.c_str(),&n);

	return ToolFrame::IsInClosedInterval(n,nBegin,nEnd);
}

bool ApiCocos2dx::IsTargetWidget( const Ref* pObj,const std::string& sName1,const std::string& sName2 )
{
	if (!pObj)return false;

	const Widget* pWidget = dynamic_cast<const Widget*>(pObj);
	if (!pWidget)return false;

	if (sName1 == pWidget->getName())
		return true;
	
	if (sName2 == pWidget->getName())
		return true;

	return false;
}

bool ApiCocos2dx::IsTargetWidget( const Ref* pObj,const std::string& sName1,const std::string& sName2,const std::string& sName3 )
{
	if (!pObj)return false;

	const Widget* pWidget = dynamic_cast<const Widget*>(pObj);
	if (!pWidget)return false;

	if (sName1 == pWidget->getName())
		return true;

	if (sName2 == pWidget->getName())
		return true;

	if (sName3 == pWidget->getName())
		return true;

	return false;
}

bool ApiCocos2dx::IsTargetWidget( const Ref* pObj,const std::string& sName1,const std::string& sName2,const std::string& sName3,const std::string& sName4 )
{
	if (!pObj)return false;

	const Widget* pWidget = dynamic_cast<const Widget*>(pObj);
	if (!pWidget)return false;

	if (sName1 == pWidget->getName())
		return true;

	if (sName2 == pWidget->getName())
		return true;

	if (sName3 == pWidget->getName())
		return true;

	if (sName4 == pWidget->getName())
		return true;

	return false;
}

bool ApiCocos2dx::IsTargetWidget( const Ref* pObj,const std::string& sName1,const std::string& sName2,const std::string& sName3,const std::string& sName4,const std::string& sName5 )
{
	if (!pObj)return false;

	const Widget* pWidget = dynamic_cast<const Widget*>(pObj);
	if (!pWidget)return false;

	if (sName1 == pWidget->getName())
		return true;

	if (sName2 == pWidget->getName())
		return true;

	if (sName3 == pWidget->getName())
		return true;

	if (sName4 == pWidget->getName())
		return true;

	if (sName5 == pWidget->getName())
		return true;

	return false;
}

bool ApiCocos2dx::SetEnabled( Ref* pSender,bool bEnabled )
{
	return SetEnabled(dynamic_cast<Node*>(pSender),bEnabled);
}

bool ApiCocos2dx::SetEnabled( Node* pNode,bool bEnabled )
{
	if (!pNode)return false;

	//备注:觉得触控科技蛋疼
	//pWidget->setEnabled(bEnabled);

	Widget* pWidget = dynamic_cast<Widget*>(pNode);
	if (!pWidget)return false;
	pWidget->setBright(bEnabled);
	pWidget->setTouchEnabled(bEnabled);
	return true;
}

bool ApiCocos2dx::SetEnabled( Node* pRootWidget,const std::string& sName,bool bEnabled )
{
	Widget* pWidget = nullptr;
	if (!ApiCocos2dx::FindNode(pWidget,pRootWidget,sName))return false;
	return SetEnabled(pWidget,bEnabled);
}

bool ApiCocos2dx::SetTouchEnabled(Node* pNode, bool bEnabled)
{
	if (!pNode)return false;

	//备注:觉得触控科技蛋疼
	//pWidget->setEnabled(bEnabled);

	Widget* pWidget = dynamic_cast<Widget*>(pNode);
	if (!pWidget)return false;
	pWidget->setTouchEnabled(bEnabled);
	return true;
}

bool ApiCocos2dx::SetChecked( CheckBox* pWidget ,bool bChecked)
{
	if (!pWidget)return false;

	pWidget->setSelectedState(bChecked);
	return true;
}

bool ApiCocos2dx::SetChecked( VectorCheckBox& vCheckBox,bool bChecked )
{
	VectorCheckBox::iterator itr;
	foreach(itr,vCheckBox){
		SetChecked(*itr,bChecked);
	}

	return true;
}

bool ApiCocos2dx::SetChecked( Widget* pRoot,const std::string& sName,bool bChecked )
{
	CheckBox* pCheckBox = nullptr;
	if (!FindNode(pCheckBox,pRoot,sName))return false;
	
	return SetChecked(pCheckBox,bChecked);
}

bool ApiCocos2dx::SetSingleChoices( ListView* pLvTeam,const Ref* pSender,const std::string& sCheckBoxName )
{
	if (!pLvTeam)return false;

	bool bFind = false;

	const Vector<Widget*>& vItem = pLvTeam->getItems();
	Vector<Widget*>::const_iterator itr;
	foreach(itr,vItem){
		Widget* pCell = *itr;
		if (!pCell)return false;

		CheckBox* pCheckBoxCur = nullptr;
		if (!ApiCocos2dx::FindNode(pCheckBoxCur,pCell,sCheckBoxName))return false;
		ASSERT_LOG_ERROR(pCheckBoxCur);

		const CheckBox* pCheckBox = dynamic_cast<const CheckBox*>(pSender);
		ASSERT_LOG_ERROR(pCheckBox);

		ApiCocos2dx::SetChecked(pCheckBoxCur,pCheckBoxCur == pCheckBox);
		if (pCheckBoxCur == pCheckBox)
			bFind = true;
	}

	return bFind;
}

bool ApiCocos2dx::SetTag( Node* pNode,int nTag )
{
	if (!pNode)return false;

	pNode->setTag(nTag);
	return true;
}

bool ApiCocos2dx::SetTag( Node* pRootWidget,const std::string& sName,int nTag )
{
	Widget* pWidget = nullptr;
	if (!ApiCocos2dx::FindNode(pWidget,pRootWidget,sName))return false;
	pWidget->setTag(nTag);
	return true;
}

bool ApiCocos2dx::SetTag( Action* pAction,int nTag )
{
	if (!pAction)return false;
	
	pAction->setTag(nTag);
	return true;
}

int ApiCocos2dx::GetTag(const Node* pNode )
{
	if (!pNode)return 0;
	return pNode->getTag();
}

int ApiCocos2dx::GetTag(const Node* pRootWidget,const std::string& sName )
{
	Node* pWidget = nullptr;
	if (!ApiCocos2dx::FindNode(pWidget,pRootWidget,sName))return false;
	return pWidget->getTag();
}

int ApiCocos2dx::GetTag(const Ref* pSender )
{
	return GetTag(dynamic_cast<const Node*>(pSender));
}
bool ApiCocos2dx::SetPostion( Node* pTarget,const Node* pSrc )
{
	if (!pTarget || !pSrc)
		return false;

	pTarget->setPosition(ToolFrame::ConstCast(pSrc)->getPosition());
	return true;
}

bool ApiCocos2dx::SetPostion( Node* pTarget,const Point& ptPostion )
{
	if (!pTarget)return false;

	pTarget->setPosition(ptPostion);

	return true;
}

bool ApiCocos2dx::SetPostion( Node* pTarget,float fX,float fY )
{
	if (!pTarget)return false;

	pTarget->setPosition(fX,fY);
	return true;
}

bool ApiCocos2dx::SetLayoutParameter( Node* pDes,const Node* pSrc,LayoutParameter::Type eLayout )
{
	if (!pDes)return false;
	if (!pSrc)return false;

	Widget* pWidgetSrc = dynamic_cast<Widget*>(ToolFrame::ConstCast(pSrc));
	if (!pWidgetSrc)return false;

	Widget* pWidgetDes = dynamic_cast<Widget*>(pDes);
	if (!pWidgetDes)return false;

	LayoutParameter* pParameter = pWidgetSrc->getLayoutParameter(eLayout);
	if (!pParameter)return false;

	pWidgetDes->setLayoutParameter(pParameter->clone());
	return true;
}

bool ApiCocos2dx::SetLayoutParameter( Node* pDes,const Node* pSrc )
{
	if (!pDes)return false;
	if (!pSrc)return false;

	SetLayoutParameter(pDes,pSrc,LayoutParameter::Type::NONE);
	SetLayoutParameter(pDes,pSrc,LayoutParameter::Type::LINEAR);
	SetLayoutParameter(pDes,pSrc,LayoutParameter::Type::RELATIVE);
	return true;
}

bool ApiCocos2dx::InsertBackNode(Node* pSrc, Node* pBack)
{
	if (!pSrc || !pBack)return false;

	Node* pParent = pSrc->getParent();
	if (!pParent)return false;

	pBack->setLocalZOrder(pSrc->getLocalZOrder());
	pBack->setPosition(pSrc->getPosition());
	pParent->addChild(pBack, pSrc->getLocalZOrder());

	ApiCocos2dx::ChangeParentNode(pSrc, pBack);
	return true;
}

Node* ApiCocos2dx::Clone( const Node* pSrc,bool bVisible)
{
	if(!pSrc)return nullptr;
	Widget* pWidget = dynamic_cast<Widget*>(ToolFrame::ConstCast(pSrc));
	if (!pWidget)return nullptr;

	Node* pTarget = pWidget->clone();
	if (!pTarget)return nullptr;

	if (bVisible)
		pTarget->setVisible(true);
	return pTarget;
}

Node* ApiCocos2dx::Clone( const Node* pSrc,const Node* pTargetPostion ,bool bVisible)
{
	if(!pSrc)return nullptr;
	if(!pTargetPostion)return nullptr;
	if(!pTargetPostion->getParent())return nullptr;

	Node* pClone = Clone(pSrc);
	if (!pClone)return nullptr;

	ApiCocos2dx::SetLayoutParameter(pClone,pTargetPostion);//复制布局方式
	ApiCocos2dx::SetPostion(pClone,pTargetPostion);		//复制坐标
	ToolFrame::ConstCast(pTargetPostion)->getParent()->addChild(pClone,ToolFrame::ConstCast(pTargetPostion)->getZOrder());//添加至定位点同级节点下
	ApiCocos2dx::SetVisible(pClone,bVisible);				//设置可视属性
	return pClone;
}

Armature* ApiCocos2dx::CreateArmature( const std::string& sName )
{
	if (sName.empty())return nullptr;

	return Armature::create(sName);
}

bool ApiCocos2dx::CacheArmatureFile( const std::string& sFileName)
{
	if (sFileName.empty())
		return false;

	std::string sArmature = ToolFrame::PickFileNameWithOutExt(sFileName);
	if (ArmatureDataManager::getInstance()->getArmatureData(sArmature))return true;

	ArmatureDataManager::getInstance()->addArmatureFileInfo(sFileName);
	return true;
}

bool ApiCocos2dx::RemoveFromParentAndCleanup( VectorWidget& vWidget,bool bCleanUp /*= true*/,bool bClearVector /*= true*/ )
{
	VectorWidget::const_iterator itr;
	foreach(itr,vWidget){
		Widget* pWidget = *itr;
		if (!pWidget)return false;

		pWidget->removeFromParentAndCleanup(bCleanUp);
	}

	if (bClearVector)
		vWidget.clear();

	return true;
}

bool ApiCocos2dx::RemoveFromParentAndCleanup( Node* pNode,bool bCleanUp /*= true*/ )
{
	if (!pNode)return false;
	pNode->removeFromParentAndCleanup(bCleanUp);
	return true;
}

bool ApiCocos2dx::RemoveFromParentAndCleanup( VectorNode& vNode,bool bCleanUp /*= true*/,bool bClearVector /*= true*/ )
{
	VectorNode::const_iterator itr;
	foreach(itr,vNode){
		Node* pNode = *itr;
		if (!pNode)return false;

		pNode->removeFromParentAndCleanup(bCleanUp);
	}

	if (bClearVector)
		vNode.clear();

	return true;
}

bool ApiCocos2dx::SetScale( Node* pTarget,float fScale )
{
	pTarget->setScale(fScale);
	return true;
}

bool ApiCocos2dx::SetScale( Node* pTarget,float fScaleX,float fScaleY )
{
	pTarget->setScale(fScaleX,fScaleY);
	return true;
}

const Point& ApiCocos2dx::GetPostion( Node* pTarget )
{
	return pTarget->getPosition();
}

bool ApiCocos2dx::IsVisible( Node* pWidget )
{
	return pWidget->isVisible();
}

Point ApiCocos2dx::GetVisibleCenter()
{
	CCSize xSize = Director::getInstance()->getVisibleSize();
	return Director::getInstance()->getVisibleOrigin() + ccp(xSize.width/2, xSize.height/2);
}

Rect ApiCocos2dx::GetVisibleRect()
{
	Rect rect;
	rect.origin = Director::getInstance()->getVisibleOrigin();
	rect.size = Director::getInstance()->getVisibleSize();
	return rect;
}

bool ApiCocos2dx::AddDisplay( Armature* pArmature,const std::string& sBone,Node* pNode ,int nIndex ,bool bRemoveFromParent ,bool bCleanUp)
{
	if (!pArmature)return false;
	if (sBone.empty())return false;
	if (!pNode)return false;

	Bone* pBone = pArmature->getBone(sBone);
	if (!pBone)return false;

	//开始添加
	pNode->retain();

	if (bRemoveFromParent)
		pNode->removeFromParentAndCleanup(bCleanUp);

	pBone->addDisplay(pNode,nIndex);

	pNode->release();
	return true;
}

bool ApiCocos2dx::ReplaceDisplay( Armature* pArmature,const std::string& sBone,Node* pNode ,bool bRemoveFromParent ,bool bCleanUp)
{
	if (!pArmature)return false;
	if (sBone.empty())return false;
	if (!pNode)return false;

	Bone* pBone = pArmature->getBone(sBone);
	if (!pBone)return false;

	//开始替换
	pNode->retain();

	if (bRemoveFromParent)
		pNode->removeFromParentAndCleanup(bCleanUp);

	pBone->addDisplay(pNode,0);
	pBone->changeDisplayWithIndex(0,true);

	pNode->release();

	return true;
}

bool ApiCocos2dx::SetSpeed( Armature* pArmature ,float fSpeed)
{
	if (!pArmature)return false;
	ArmatureAnimation* pAnimation = pArmature->getAnimation();
	if (!pAnimation)return false;
	pAnimation->setSpeedScale(fSpeed);

	return true;
}

bool ApiCocos2dx::SetSpeed( SkeletonAnimation* pArmature,float fSpeed /*= 1.0f*/ )
{
	if (!pArmature)return false;
	pArmature->setTimeScale(fSpeed);
	return true;
}

bool ApiCocos2dx::ChangeParentNode( Node* pNode,Node* pParent ,bool bKeepWorld,bool bCleanUp,int nZOrder)
{
	if (!pNode)return false;
	if (!pParent)return false;

	if (pNode->getParent() == pParent)return true;

	Rect rWorld; Point ptWorldPosition;
	if (bKeepWorld) {
		rWorld = GetWorldBoundingBox(pNode);
		ptWorldPosition = GetWorldPostion(pNode);
	}

	pNode->retain();
	pNode->removeFromParentAndCleanup(bCleanUp);
	pParent->addChild(pNode,nZOrder);
	pNode->release();

	if (bKeepWorld)
		SetWorldBoundingBox(pNode,rWorld, ptWorldPosition);

	return true;
}

bool ApiCocos2dx::RemoveDisplay( Armature* pArmature,const std::string& sBone,int nIndex )
{
	if (!pArmature)return false;
	if (sBone.empty())return false;

	Bone* pBone = pArmature->getBone(sBone);
	if (!pBone)return false;

	pBone->removeDisplay(nIndex);
	return true;
}

bool ApiCocos2dx::ChangeDisplay( Armature* pArmature,const std::string& sBone,int nIndex/*=0*/,bool bForce /*= true*/ )
{
	if (!pArmature)return false;
	if (sBone.empty())return false;

	Bone* pBone = pArmature->getBone(sBone);
	if (!pBone)return false;

	pBone->changeDisplayWithIndex(nIndex,bForce);
	return true;
}

bool ApiCocos2dx::SetOpacity( Node* pNode,GLubyte uOpacity,bool bChildren /*= true*/ )
{
	if (!pNode)return false;

	CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(pNode);
	if (pRGBAProtocol)
		pRGBAProtocol->setOpacity(uOpacity);

	Vector<Node*>& vChildren = pNode->getChildren();
	Vector<Node*>::iterator itr;
	foreach(itr,vChildren){
		SetOpacity(*itr,uOpacity,bChildren);
	}

	return true;
}

bool ApiCocos2dx::SetRotation( Node* pNode,float fRotation )
{
	if (!pNode)return false;

	pNode->setRotation(fRotation);
	return true;
}

const Size& ApiCocos2dx::GetDesignResolutionSize()
{
	return Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
}

bool ApiCocos2dx::AddBone( Armature* pArmature,const std::string& sParentBone,const std::string& sNewBone,Node* pNode )
{
	if (!pArmature)return false;
	if (sParentBone.empty())return false;

	Bone *pBone  = Bone::create(sNewBone);
	if(!pBone)return false;

	pBone->addDisplay(pNode, 0);
	pBone->changeDisplayWithIndex(0, true);
	pBone->setIgnoreMovementBoneData(true);
	pBone->setLocalZOrder(ApiCocos2dx::GetChildZOrderMax(pArmature));
	pArmature->addBone(pBone, sParentBone);

	return true;
}

size_t ApiCocos2dx::GetAnimationCount( const ArmatureAnimation* pArmature )
{
	if (!pArmature)return 0;
	return pArmature->getMovementCount();
}

size_t ApiCocos2dx::GetAnimationCount( const Armature* pArmature )
{
	if (!pArmature)return 0;
	return GetAnimationCount(pArmature->getAnimation());
}

Layout* ApiCocos2dx::GetCurPage( PageView* pPv )
{
	if (!pPv)return nullptr;
	return pPv->getPage(pPv->getCurPageIndex());
}

bool ApiCocos2dx::ScrollToNext( PageView* pPv ,bool bNext,bool bCircle)
{
	if (!pPv)return false;
	//计算Index
	const Vector<Layout*>& vPages = pPv->getPages();
	if (vPages.empty())return false;

	int nSize = (int)vPages.size();
	int nIndex = (int)pPv->getCurPageIndex();
	bNext ? ++nIndex : --nIndex;

	//临界值
	if (nIndex >= nSize)
		nIndex = bCircle ? 0:nSize-1;
	if (nIndex < 0)
		nIndex = bCircle ? nSize-1:0;

	pPv->scrollToPage(nIndex);
	return true;
}

int ApiCocos2dx::GetAnimationFrameCount( const Armature* pArmature )
{
	if (!pArmature)return 0;

	return GetAnimationFrameCount(pArmature->getAnimation());
}

int ApiCocos2dx::GetAnimationFrameCount( const ArmatureAnimation* pArmature )
{
	if (!pArmature)return 0;

	return pArmature->getRawDuration();
}

int ApiCocos2dx::GetAnimationCurrentFrameIndex( const Armature* pArmature )
{
	if (!pArmature)return 0;

	return GetAnimationCurrentFrameIndex(pArmature->getAnimation());
}

int ApiCocos2dx::GetAnimationCurrentFrameIndex( const ArmatureAnimation* pArmature )
{
	if (!pArmature)return 0;

	return ToolFrame::ConstCast(pArmature)->getCurrentFrameIndex();
}

bool ApiCocos2dx::GotoAndPlay( Armature* pArmature,int nFrameIndex )
{
	if (!pArmature)return false;

	return GotoAndPlay(pArmature->getAnimation(),nFrameIndex);
}

bool ApiCocos2dx::GotoAndPlay( ArmatureAnimation* pArmature, int nFrameIndex )
{
	if (!pArmature)return false;

	if (nFrameIndex < 0)
		nFrameIndex = pArmature->getRawDuration() - 2;//最后一帧会再次触发播放完成

	if (nFrameIndex < 0)
		return false;

	pArmature->gotoAndPlay(nFrameIndex);
	return true;
}

bool ApiCocos2dx::GotoAndPause( Armature* pArmature, int nFrameIndex )
{
	if (!pArmature)return false;

	return GotoAndPause(pArmature->getAnimation(),nFrameIndex);
}

bool ApiCocos2dx::GotoAndPause( ArmatureAnimation* pArmature, int nFrameIndex )
{
	if (!pArmature)return false;

	if (!GotoAndPlay(pArmature,nFrameIndex))return false;

	pArmature->pause();
	return true;
}

bool ApiCocos2dx::SetCallFuncNull( Armature* pArmature )
{
	if (!pArmature)return false;
	return SetCallFuncNull(pArmature->getAnimation());
}

bool ApiCocos2dx::SetCallFuncNull( ArmatureAnimation* pArmature )
{
	if (!pArmature)return false;
	pArmature->setMovementEventCallFunc(nullptr);
	pArmature->setMovementEventCallFunc(nullptr,nullptr);
	return true;
}

bool ApiCocos2dx::SetCallFuncNull( SkeletonAnimation* pArmature )
{
	pArmature->setStartListener(nullptr);
	pArmature->setEndListener(nullptr);
	pArmature->setCompleteListener(nullptr);
	pArmature->setEventListener(nullptr);
	return true;
}

Armature* ApiCocos2dx::SetAnimationCallBackMovement(Armature* pArmature, FnActionArmatureMovement fnMovement)
{
	if (!pArmature)return nullptr;

	CActionArmatureMonitor* pAction = dynamic_cast<CActionArmatureMonitor*>(pArmature->getActionByTag(COCOS_ACTION_ARMATURE_MONITOR));
	if (pAction)
		pAction->SetCallBackMovement(fnMovement);

	return pArmature;
}

Armature* ApiCocos2dx::SetAnimationCallBackOver(Armature* pArmature, FnActionArmatureOver fnOver)
{
	if (!pArmature)return nullptr;

	CActionArmatureMonitor* pAction = dynamic_cast<CActionArmatureMonitor*>(pArmature->getActionByTag(COCOS_ACTION_ARMATURE_MONITOR));
	if (pAction)
		pAction->SetCallBackOver(fnOver);

	return pArmature;
}

Armature* ApiCocos2dx::CreateArmatureByFileName(const std::string& sName)
{
	std::string sArmature = ToolFrame::PickFileNameWithOutExt(sName);
	return CreateArmature(sArmature);
}

bool ApiCocos2dx::PurgeTextureCache( bool bRemoveAll /*= true*/ )
{
	if (!bRemoveAll)
	{
		TextureCache::getInstance()->removeUnusedTextures();
		return true;
	}
	TextureCache::getInstance()->removeAllTextures();
	return true;
}

bool ApiCocos2dx::PurgeSpriteFramesCache(bool bRemoveAll /*= true*/)
{
	if (!bRemoveAll)
	{
		SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
		return true;
	}
	SpriteFrameCache::getInstance()->removeSpriteFrames();
	return true;
}

bool ApiCocos2dx::ReplaceScene( Scene* pScene )
{
	if (!pScene)return false;
	if (Director::getInstance()->getRunningScene())
		Director::getInstance()->replaceScene(pScene);
	else
		Director::getInstance()->runWithScene(pScene);
	return true;
}

bool ApiCocos2dx::ChangeParentNode( const Node* pRoot,const std::string& sChild,const std::string& sParent,bool bKeepWorld,bool bCleanUp /*= true*/ )
{
	Node* pChild = ApiCocos2dx::FindNode(pRoot,sChild);
	Node* pParent= ApiCocos2dx::FindNode(pRoot,sParent);

	if (!pChild || !pParent)return false;

	return ApiCocos2dx::ChangeParentNode(pChild,pParent,bKeepWorld,bCleanUp);
}

Size ApiCocos2dx::CalDesignResolutionSizeResidue(const Node* pRoot,const VectorString& vName )
{
	Size sizeDesign = GetDesignResolutionSize();
	Size size		= CalSize(pRoot,vName);

	return sizeDesign - size;
}

Size ApiCocos2dx::CalDesignResolutionSizeResidue(const Node* pRoot,const std::string& sName1,const std::string& sName2/*=""*/,const std::string& sName3/*=""*/,const std::string& sName4/*=""*/,const std::string& sName5/*=""*/ )
{
	VectorString vName;
	if (!sName1.empty())
		vName.push_back(sName1);
	if (!sName2.empty())
		vName.push_back(sName2);
	if (!sName3.empty())
		vName.push_back(sName3);
	if (!sName4.empty())
		vName.push_back(sName4);
	if (!sName5.empty())
		vName.push_back(sName5);
	return CalDesignResolutionSizeResidue(pRoot,vName);
}

const Size& ApiCocos2dx::GetContentSize(const Node* pNode )
{
	return pNode->getContentSize();
}

bool ApiCocos2dx::SetContentSize( Node* pNode,const Size& size )
{
	pNode->setContentSize(size);
	return true;
}

bool ApiCocos2dx::SwitchScreen()
{
	const Size& r = Director::getInstance()->getOpenGLView()->getFrameSize();
	Director::getInstance()->getOpenGLView()->setFrameSize(r.height,r.width);
	return true;
}

bool ApiCocos2dx::SwitchScreen( bool bLandscape )
{
	const Size& r = Director::getInstance()->getOpenGLView()->getFrameSize();
	if ((bLandscape && r.width < r.height) || (!bLandscape && r.width > r.height))
	{
		Director::getInstance()->getOpenGLView()->setFrameSize(r.height,r.width);
		return true;
	}
	
	return false;
}

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS

//Cocos坐标系 转换成 屏幕坐标系
Rect ApiCocos2dx::TranWinRect(const Rect& rect){
	Rect r;

	Point ptBegin;
	ptBegin.x = rect.origin.x;
	ptBegin.y = rect.origin.y + rect.size.height;

	//转化成屏幕坐标
	Point ptUI = CCDirector::getInstance()->convertToUI(ptBegin);

	//计算比例
	const Size& rSize = CCDirector::getInstance()->getWinSize();
	GLView* pView=CCDirector::getInstance()->getOpenGLView();
	const Size& t_FSize=pView->getFrameSize();

	float p_x = (ptUI.x * t_FSize.width) / rSize.width;
	float p_y = (ptUI.y * t_FSize.height)/ rSize.height;
	float p_width = (rect.size.width + ptUI.x) * t_FSize.width / rSize.width;
	float p_height =(rect.size.height + ptUI.y) * t_FSize.height / rSize.height;

	r.origin.x = p_x;
	r.origin.y = p_y;
	r.size.width = p_width;
	r.size.height = p_height;

	return r;
}

#endif//MACRO_OS_WINDOWS

#if MACRO_TARGET_OS == MACRO_OS_IOS || MACRO_TARGET_OS == MACRO_OS_ANDROID

//Cocos坐标系 转换成 屏幕坐标系
Rect ApiCocos2dx::TranWinRect(const Rect& rect){
	Rect r;

	Point ptBegin;
	ptBegin.x = rect.origin.x;
	ptBegin.y = rect.origin.y + rect.size.height;

	//转化成屏幕坐标
	Point ptUI = CCDirector::getInstance()->convertToUI(ptBegin);

	//计算比例
	const Size& winSize = CCDirector::getInstance()->getWinSize();
	GLView* t_p=CCDirector::getInstance()->getOpenGLView();
	const Size& t_FSize=t_p->getFrameSize();

	float p_x=ptUI.x * t_FSize.width / winSize.width;
	float p_y=ptUI.y * t_FSize.height / winSize.height;
	float p_width=(rect.size.width) * t_FSize.width / winSize.width;
	float p_height=(rect.size.height) * t_FSize.height / winSize.height;


	r.origin.x = p_x;
	r.origin.y = p_y;
	r.size.width = p_width;
	r.size.height = p_height;

	return r;
}

#endif//MACRO_OS_IOS

Rect ApiCocos2dx::TranWinRect( const Size& szie )
{
	Rect rect;
	rect.size = szie;
	return rect;
}

Rect ApiCocos2dx::TranWinRect( const Node* pNode )
{
	return TranWinRect(ApiCocos2dx::GetWorldBoundingBox(pNode));
}

bool ApiCocos2dx::GetValue( const TextField* pWidget,std::string& sValue )
{
	if (!pWidget)return false;
	sValue = pWidget->getStringValue();
	return true;
}

bool ApiCocos2dx::GetValue( const Text* pWidget,std::string& sValue )
{
	if (!pWidget)return false;
	sValue = pWidget->getString();
	return true;
}

bool ApiCocos2dx::GetValue( const LoadingBar* pWidget,float& fValue )
{
	if (!pWidget)return false;
	fValue = pWidget->getPercent();
	return true;
}

bool ApiCocos2dx::GetValue( const LoadingBar* pWidget,int& nValue )
{
	if (!pWidget)return false;
	nValue = pWidget->getPercent();
	return true;
}

bool ApiCocos2dx::GetValue( const TextAtlas* pWidget,int& nValue )
{
	if (!pWidget)return false;
	return ToolFrame::ToValue(pWidget->getString(),nValue);
}

bool ApiCocos2dx::GetValue( const TextAtlas* pWidget,std::string& sValue )
{
	if (!pWidget)return false;
	sValue = pWidget->getString();
	return true;
}

bool ApiCocos2dx::GetValue( const Text* pWidget,int& nValue )
{
	if (!pWidget)return false;
	return ToolFrame::ToValue(pWidget->getString(),nValue);
}

bool ApiCocos2dx::GetValue( const Text* pWidget,float& fValue )
{
	if (!pWidget)return false;
	return ToolFrame::ToValue(pWidget->getString(),fValue);
}

bool ApiCocos2dx::SetAccelerometerEnabled( bool bEnabled )
{
	Device::setAccelerometerEnabled(bEnabled);
	return true;
}

bool ApiCocos2dx::ActionsTurn( Node* pNode,float fDuration /*= 0.3f*/ )
{
	if (!pNode)return false;
	pNode->runAction(CCRotateBy::create(fDuration, 180.0f));
	return true;
}

Size ApiCocos2dx::CalSize(const Node* pRoot,const std::string& sName1/*=""*/,const std::string& sName2/*=""*/,const std::string& sName3/*=""*/,const std::string& sName4/*=""*/,const std::string& sName5/*=""*/ )
{
	VectorString vName;
	if (!sName1.empty())
		vName.push_back(sName1);
	if (!sName2.empty())
		vName.push_back(sName2);
	if (!sName3.empty())
		vName.push_back(sName3);
	if (!sName4.empty())
		vName.push_back(sName4);
	if (!sName5.empty())
		vName.push_back(sName5);
	return CalSize(pRoot,vName);
}

Size ApiCocos2dx::CalSize(const Node* pRoot,const VectorString& vName )
{
	Size size;

	VectorString::const_iterator itr;
	foreach(itr,vName){
		const std::string& sName = *itr;

		const Node* pWidget = FindNode(pRoot,sName);
		if (pWidget)
			size = Plus(size,pWidget->getContentSize());
	}

	return size;
}

bool ApiCocos2dx::IsCurLastPage( PageView* pPageView )
{
	if (!pPageView)return false;
	
	return pPageView->getPages().size() ==  pPageView->getCurPageIndex()+1;
}

bool ApiCocos2dx::ScreenShot( const std::string& sFileName )
{
	CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
	if (!pScene)return false;

	CCSize size = CCDirector::sharedDirector()->getWinSize();  

	CCRenderTexture* pScreen = CCRenderTexture::create(size.width, size.height); 
	if (!pScreen)return false;
	pScreen->begin();  
	pScene->visit();//将当前的整个scene绘出来  
	pScreen->end();  
	pScreen->saveToFile(sFileName, kCCImageFormatPNG);
	return true;
}

bool ApiCocos2dx::Exit()
{
	Director::getInstance()->end();
	if (MACRO_OS_IOS == ToolFrame::GetPlatform())
		ToolFrame::Exit();

	return true;
}

const Size& ApiCocos2dx::GetSize( Widget* pWidget )
{
	return pWidget->getSize();
}

Point ApiCocos2dx::GetSizeCenter( Widget* pWidget )
{
	return pWidget->getSize()/2;
}

bool ApiCocos2dx::PurgeActionCache()
{
	ActionManagerEx::getInstance()->releaseActions();
	timeline::ActionTimelineCache::getInstance()->purge();
	return true;
}

std::string ApiCocos2dx::GetName( const Widget* pWidget )
{
	if (!pWidget)return "";
	return pWidget->getName();
}

bool ApiCocos2dx::PageAddImage( PageView* pPageView,const std::string& sImgPath,int nIndex /*= -1 */,bool bChangeSize) //添加子页面
{
	if (!pPageView)return false;

	if (-1 == nIndex)
		nIndex = (int)pPageView->getPages().size();

	ImageView* pImgWelcome = ApiCocos2dx::CreateImageView(sImgPath);
	if (!pImgWelcome)return false;

	Layout* pLayout = Layout::create();
	if (!pLayout)return false;

	pLayout->setSize(pImgWelcome->getSize());
	pImgWelcome->setNormalizedPosition(Vec2::ANCHOR_MIDDLE);
	pLayout->addChild(pImgWelcome);
	
	if (bChangeSize)
	{
		Size rPageSize = pPageView->getSize();
		rPageSize = ApiCocos2dx::Max(rPageSize, pLayout->getSize());
		pPageView->setSize(rPageSize);
	}

	pLayout->setPosition(pPageView->getSize() / 2);
	pPageView->addWidgetToPage(pLayout, nIndex, true);
	return true;
}

bool ApiCocos2dx::PageResetImage( PageView* pPageView )
{
	if (!pPageView)return false;

	const Vector<Layout*>& vLayout = pPageView->getPages();
	Vector<Layout*>::const_iterator itr;
	foreach(itr,vLayout){
		Layout* pLayout = *itr;
		if (pLayout)
		{
			const Vector<Node*>& vChild = pLayout->getChildren();
			if (!vChild.empty())
			{
				Node* pImg = *vChild.begin();
				if (!pImg)return false;
				pImg->setPosition(pPageView->getSize()/2);
			}
		}
	}

	return true;
}

//设置尺寸为所有子节点大小总和(必须全为 Widget)
bool ApiCocos2dx::SetContentSizeWithChildrenSum(Node* pWidget,bool bWidth){
	if (!pWidget)return false;

	Size rContent;

	const Vector<Node*>& vChild = pWidget->getChildren();
	Vector<Node*>::const_iterator itr;
	foreach(itr,vChild){
		Widget* pChild = dynamic_cast<Widget*>(*itr);
		if (!pChild)return false;

		rContent = rContent + pChild->getSize();
	}
	bWidth ? rContent.height = pWidget->getContentSize().height : rContent.width = pWidget->getContentSize().width ;
	pWidget->setContentSize(rContent);
	return true;
}

//设置尺寸为所有子节点大小总和(必须全为 Widget)
bool ApiCocos2dx::SetContentSizeWithChildrenMax(Node* pWidget,bool bWidth){
	if (!pWidget)return false;

	Size rContent;

	const Vector<Node*>& vChild = pWidget->getChildren();
	Vector<Node*>::const_iterator itr;
	foreach(itr,vChild){
		Widget* pChild = dynamic_cast<Widget*>(*itr);
		if (!pChild)return false;

		const Size& rSize = pChild->getSize();
		rContent.width	= ToolFrame::Max(rContent.width,rSize.width);
		rContent.height = ToolFrame::Max(rContent.height,rSize.height);
	}
	bWidth ? rContent.height = pWidget->getContentSize().height : rContent.width = pWidget->getContentSize().width ;
	pWidget->setContentSize(rContent);
	return true;
}

bool ApiCocos2dx::SetContentSizeWithChildren( Node* pWidget,bool bWidth )
{
	if (!pWidget)return false;

	Size rContent;

	const Vector<Node*>& vChild = pWidget->getChildren();
	Vector<Node*>::const_iterator itr;
	foreach(itr,vChild){
		Widget* pChild = dynamic_cast<Widget*>(*itr);
		if (!pChild)return false;

		const Size& rSize = pChild->getSize();
		if (bWidth)
		{
			rContent.width	+= rSize.width;
			rContent.height = ToolFrame::Max(rContent.height,rSize.height);
		}else
		{
			rContent.width = ToolFrame::Max(rContent.width,rSize.width);
			rContent.height	+= rSize.height;
		}
	}

	pWidget->setContentSize(rContent);
	return true;
}

bool ApiCocos2dx::IsOutOfScreen( const Node* pRoot,const VectorString& vWidget,bool bWidth )
{
	Size rSize = ApiCocos2dx::CalSize(pRoot,vWidget);
	return bWidth ? rSize.width > ApiCocos2dx::GetDesignResolutionSize().width : rSize.height > ApiCocos2dx::GetDesignResolutionSize().height;
}

bool ApiCocos2dx::IsOutOfScreen( const Node* pRoot,bool bWidth,const std::string& sName1/*=""*/,const std::string& sName2/*=""*/,const std::string& sName3/*=""*/,const std::string& sName4/*=""*/,const std::string& sName5/*=""*/ )
{
	VectorString vName;
	if (!sName1.empty())
		vName.push_back(sName1);
	if (!sName2.empty())
		vName.push_back(sName2);
	if (!sName3.empty())
		vName.push_back(sName3);
	if (!sName4.empty())
		vName.push_back(sName4);
	if (!sName5.empty())
		vName.push_back(sName5);

	return IsOutOfScreen(pRoot,vName,bWidth);
}

bool ApiCocos2dx::IsLandscape()
{
	const Size& r = Director::getInstance()->getOpenGLView()->getFrameSize();
	return r.width >= r.height;
}

int ApiCocos2dx::GetWidgetNameIndex(const Ref* pObj,const std::string& sName,int nInvaild /*= -1*/ )
{
	if (!pObj)return nInvaild;
	if (sName.empty())return nInvaild;

	const Widget* pWidget = dynamic_cast<const Widget*>(pObj);
	if (!pWidget)return nInvaild;

	std::string sIndex = ToolFrame::GetMidString(pWidget->getName(),sName,"");
	if (sIndex.empty())return nInvaild;

	int nValue = 0;
	if (!ToolFrame::ToValue(sIndex,nValue))return nInvaild;

	return nValue;
}

Size ApiCocos2dx::Max( const Size& rSize1,const Size& rSize2 )
{
	Size rSize;
	rSize.width	 = ToolFrame::Max(rSize1.width,rSize2.width);
	rSize.height = ToolFrame::Max(rSize1.height,rSize2.height);

	return rSize;
}

float ApiCocos2dx::GetAnimationInterval()
{
	return Director::getInstance()->getAnimationInterval();
}

bool ApiCocos2dx::FireTouchedWithUI( const Vec2& ptUI )
{
	intptr_t touchId = rand();

	Vec2 v = ptUI;
	v.x *= Director::getInstance()->getOpenGLView()->getScaleX();
	v.y *= Director::getInstance()->getOpenGLView()->getScaleY();
	Director::getInstance()->getOpenGLView()->handleTouchesBegin(1, &touchId, &v.x, &v.y);
	Director::getInstance()->getOpenGLView()->handleTouchesEnd(1, &touchId, &v.x, &v.y);
	return true;
}

bool ApiCocos2dx::FireTouchedWithGL( const Vec2& ptGL )
{
	return FireTouchedWithUI(Director::getInstance()->convertToUI(ptGL));
}

bool ApiCocos2dx::PostTouchedWithUI( const Vec2& ptUI )
{
	intptr_t touchId = rand();
	
	Vec2 v = ptUI;
	v.x *= Director::getInstance()->getOpenGLView()->getScaleX();
	v.y *= Director::getInstance()->getOpenGLView()->getScaleY();
	Scheduler *sched = Director::getInstance()->getScheduler();
	if (!sched)return false; 
	sched->performFunctionInCocosThread( [&](){
		Director::getInstance()->getOpenGLView()->handleTouchesBegin(1, &touchId, &v.x, &v.y);
		Director::getInstance()->getOpenGLView()->handleTouchesEnd(1, &touchId, &v.x, &v.y);
	});
	return true;
}

bool ApiCocos2dx::PostTouchedWithGL( const Vec2& ptGL )
{
	return PostTouchedWithUI(Director::getInstance()->convertToUI(ptGL));
}

const Vec2& ApiCocos2dx::GetTouchBeganPosition( const Ref* pObj )
{
	return GetTouchBeganPosition(dynamic_cast<const Widget*>(pObj));
}

const Vec2& ApiCocos2dx::GetTouchBeganPosition( const Widget* pWidget )
{
	return pWidget->getTouchBeganPosition();
}

const Vec2& ApiCocos2dx::GetTouchEndPosition( const Ref* pObj )
{
	return GetTouchEndPosition(dynamic_cast<const Widget*>(pObj));
}

const Vec2& ApiCocos2dx::GetTouchEndPosition( const Widget* pWidget )
{
	return pWidget->getTouchEndPosition();
}

bool ApiCocos2dx::CloneFireTouched( const Ref* pObj )
{
	if (!pObj)return false;
	const Vec2& v = ApiCocos2dx::GetTouchEndPosition(pObj);
	return FireTouchedWithGL(v);
}

bool ApiCocos2dx::ClonePostTouched( const Ref* pObj )
{
	if (!pObj)return false;
	const Vec2& v = ApiCocos2dx::GetTouchEndPosition(pObj);
	return PostTouchedWithGL(v);
}

bool ApiCocos2dx::SetStroke( LabelTTF* pText ,const Color4B &clrFont, float fSize)
{
	if (!pText)return false;

	Color3B clr(clrFont);
	pText->enableStroke(clr, fSize, true);
	return true;
}

bool ApiCocos2dx::SetStroke( Label* pText ,const Color4B &clrFont, float fSize)
{
	if (!pText)return false;
	pText->enableOutline(clrFont, fSize);
	return true;
}

bool ApiCocos2dx::SetStroke( Text* pText ,const Color4B &clrFont, float fSize)
{
	if (!pText)return false;
	pText->enableOutline(clrFont, fSize);
	return true;
}

bool ApiCocos2dx::SetShadow( LabelTTF* pText, const Color4B& clrShadow,const Size& fSize,float fBlur )
{
	if (!pText)return false;
	pText->enableShadow(fSize, clrShadow.a,fBlur);
	return true;
}

bool ApiCocos2dx::SetShadow( Label* pText, const Color4B& clrShadow,const Size& fSize, float fBlur )
{
	if (!pText)return false;
	pText->enableShadow(clrShadow, fSize,fBlur);
	return true;
}

bool ApiCocos2dx::SetShadow( Text* pText, const Color4B& clrShadow,const Size& fSize, float fBlur  )
{
	if (!pText)return false;
	pText->enableShadow(clrShadow, fSize,fBlur);
	return true;
}

bool ApiCocos2dx::RemoveEffect( LabelTTF* pText )
{
	if (!pText)return false;
	pText->disableShadow(true);
	pText->disableStroke(true);
	return true;
}

bool ApiCocos2dx::RemoveEffect( Label* pText )
{
	if (!pText)return false;
	pText->disableEffect();
	return true;
}

bool ApiCocos2dx::RemoveEffect( Text* pText )
{
	if (!pText)return false;
	pText->disableEffect();
	return true;
}

bool ApiCocos2dx::IsHitted( const Widget* pWidget,Touch *touch, Event *unusedEvent )
{
	if (!pWidget)return false;

	Widget* pWidgetNone = (Widget*)pWidget;

	if (pWidget->isVisible() && pWidget->isEnabled() && IsAncestorsEnabled(pWidget) && IsAncestorsVisible(pWidget))
	{
		Vec2 touchBeganPosition = touch->getLocation();
		auto camera = Camera::getVisitingCamera();
		if(pWidgetNone->hitTest(touchBeganPosition,camera,nullptr) && pWidgetNone->isClippingParentContainsPoint(touchBeganPosition))
			return true;
	}

	return false;
}

bool ApiCocos2dx::IsHitted( const Node* pNode,Touch *touch, Event *unusedEvent )
{
	if (!pNode)return false;

	if (!IsAncestorsVisible(pNode))return false;
	
	Vec2 nsp = pNode->convertToNodeSpace(touch->getLocation());
	
	Rect bb;
	bb.size = pNode->getContentSize();
	return bb.containsPoint(nsp);
}

bool ApiCocos2dx::IsAncestorsEnabled(const Widget* pWidget )
{
	if (!pWidget)return false;

	while (pWidget)
	{
		if (!pWidget->isEnabled())
			return false;

		pWidget = dynamic_cast<const Widget*>(pWidget->getParent());
	}

	return true;
}

bool ApiCocos2dx::IsAncestorsVisible(const Node* pNode)
{
	if (!pNode)return false;

	while (pNode)
	{
		if (!pNode->isVisible())
			return false;

		pNode = pNode->getParent();
	}

	return true;
}
bool ApiCocos2dx::IsAllHitted( const Widget* pWidget,const std::vector<Touch*>& vTouch, Event *unusedEvent )
{
	if (!pWidget)return false;

	std::vector<Touch*>::const_iterator itr;
	foreach(itr,vTouch){
		if(!IsHitted(pWidget,*itr,unusedEvent))return false;
	}

	return true;
}

float ApiCocos2dx::CalDistanceSquared( const Vec2& pt1,const Vec2& pt2 )
{
	return pt1.distanceSquared(pt2);
}

bool ApiCocos2dx::MakeInRect( Node* pNode,const Vec2& ptOffset,const Rect& rRect )
{
	if (!pNode)return false;

	Rect rDrag = ApiCocos2dx::GetWorldBoundingBox(pNode);
	Rect rDragOrg = rDrag;//保存原始
	if (rDrag.size.width <= rRect.size.width)
	{
		if (ptOffset.x > 0 && rDrag.getMaxX() > rRect.getMaxX())
			rDrag.origin.x -= rDrag.getMaxX() - rRect.getMaxX();

		if (ptOffset.x < 0 && rDrag.getMinX() < rRect.getMinX())
			rDrag.origin.x += rRect.getMinX() - rDrag.getMinX();
	}else
	{
		if (ptOffset.x > 0 && rDrag.getMinX() > rRect.getMinX())
			rDrag.origin.x -= rDrag.getMinX() - rRect.getMinX();

		if (ptOffset.x < 0 && rDrag.getMaxX() < rRect.getMaxX())
			rDrag.origin.x += rRect.getMaxX() - rDrag.getMaxX();
	}

	if (rDrag.size.height <= rRect.size.height){
		if (ptOffset.y > 0 && rDrag.getMaxY() > rRect.getMaxY())
			rDrag.origin.y -= rDrag.getMaxY() - rRect.getMaxY();

		if (ptOffset.y < 0 && rDrag.getMinY() < rRect.getMinY())
			rDrag.origin.y += rRect.getMinY() - rDrag.getMinY();
	}else
	{
		if (ptOffset.y > 0 && rDrag.getMinY() > rRect.getMinY())
			rDrag.origin.y -= rDrag.getMinY() - rRect.getMinY();

		if (ptOffset.y < 0 && rDrag.getMaxY() < rRect.getMaxY())
			rDrag.origin.y += rRect.getMaxY() - rDrag.getMaxY();
	}

	//如果发生变化
	if (!rDragOrg.equals(rDrag))
		ApiCocos2dx::SetWorldBoundingBox(pNode,rDrag);
	return true;
}

bool ApiCocos2dx::MakeInRect( Node* pNode,const Rect& rRect )
{
	if (!pNode)return false;
	ApiCocos2dx::MakeInRect(pNode,Vec2(-1,-1),rRect);
	ApiCocos2dx::MakeInRect(pNode,Vec2(1,1),rRect);
	return true;
}

bool ApiCocos2dx::MakeInScreen( Node* pNode,const Vec2& ptOffset)
{
	if (!pNode)return false;

	return MakeInRect(pNode,ptOffset,ApiCocos2dx::GetVisibleRect());
}

bool ApiCocos2dx::MakeInScreen( Node* pNode )
{
	if (!pNode)return false;
	Rect rRect = ApiCocos2dx::GetVisibleRect();
	ApiCocos2dx::MakeInRect(pNode,Vec2(-1,-1),rRect);
	ApiCocos2dx::MakeInRect(pNode,Vec2(1,1),rRect);
	return true;
}

bool ApiCocos2dx::ActionsChangeNodeFade( Node* pSrc,Node* pDes,float fTime )
{
	if(pSrc)
	{
		FiniteTimeAction*  pAcFadeOut	= FadeOut::create(fTime);
		FiniteTimeAction*  pAcRemoveSelf= RemoveSelf::create(true);
		pSrc->runAction(Sequence::create(pAcFadeOut,pAcRemoveSelf,nullptr));
	}

	if (pDes)
	{
		ApiCocos2dx::SetOpacity(pDes,0);
		FiniteTimeAction*  pAcFadeIn	= FadeIn::create(fTime);
		pDes->runAction(Sequence::create(pAcFadeIn,nullptr));  
	}

	return true;
}

bool ApiCocos2dx::RemoveFromParentAndCleanupNextFrame( Node* pNode,bool bCleanUp /*= true*/ )
{
	if (!pNode)return false;

	ReleaseNextFrame(pNode);

	pNode->removeFromParentAndCleanup(bCleanUp);
	return true;
}

bool ApiCocos2dx::Flip( Node* pNode,bool bHorizontal/*=false*/,bool bVertical/*=false*/ )
{
	if (!pNode)return false;
	
	if (bHorizontal)
		pNode->setScaleX(-pNode->getScaleX());
	if (bVertical)
		pNode->setScaleY(-pNode->getScaleY());
	return true;
}

bool ApiCocos2dx::IsHasMovementID( const Armature* pArmature,const std::string& sMovementID )
{
	if (!pArmature)return false;
	return IsHasMovementID(pArmature->getAnimation(),sMovementID);
}

bool ApiCocos2dx::IsHasMovementID( const ArmatureAnimation* pArmature,const std::string& sMovementID )
{
	if (!pArmature)return false;
	return !!pArmature->getAnimationData()->getMovement(sMovementID);
}

std::string ApiCocos2dx::GetCurMovementID( const Armature* pArmature )
{
	if (!pArmature)return ToolFrame::EmptyString();
	return GetCurMovementID(pArmature->getAnimation());
}

std::string ApiCocos2dx::GetCurMovementID( const ArmatureAnimation* pArmature )
{
	if (!pArmature)return ToolFrame::EmptyString();
	return pArmature->getCurrentMovementID();
}

bool ApiCocos2dx::IsCurMovementID( const Armature* pArmature,const std::string& sMovementID )
{
	if (!pArmature)return false;
	return IsCurMovementID(pArmature->getAnimation(),sMovementID);
}

bool ApiCocos2dx::IsCurMovementID( const ArmatureAnimation* pArmature,const std::string& sMovementID )
{
	if (!pArmature)return false;
	return pArmature->getCurrentMovementID() == sMovementID;
}

bool ApiCocos2dx::IsEmptyMovement(const ArmatureAnimation* pAnimation,const std::string& sName )
{
	if (!pAnimation)return true;
	const MovementData* pData = pAnimation->getAnimationData()->getMovement(sName);
	if (!pData)return true;

	return pData->duration <= 0;		
}

bool ApiCocos2dx::IsEmptyMovement( const Armature* pArmature,const std::string& sName )
{
	if (!pArmature)return true;
	return IsEmptyMovement(pArmature->getAnimation(),sName);
}

const std::string& ApiCocos2dx::GetMovementName( const Armature* pArmature,int nIndex )
{
	if (!pArmature)return ToolFrame::EmptyString();
	return GetMovementName(pArmature->getAnimation(),nIndex);
}

const std::string& ApiCocos2dx::GetMovementName( const ArmatureAnimation* pArmature,int nIndex )
{
	if (!pArmature)return ToolFrame::EmptyString();
	const VectorString& vName = pArmature->getAnimationData()->movementNames;
	if (!ToolFrame::IsVaildIndex(vName,nIndex))
		return ToolFrame::EmptyString();
	return ToolFrame::GetValueByIndex(vName,nIndex);
}

const VectorString& ApiCocos2dx::GetMovementName( const Armature* pArmature )
{
	if (!pArmature)return ToolFrame::EmptyVectorString();
	return GetMovementName(pArmature->getAnimation());
}

const VectorString& ApiCocos2dx::GetMovementName( const ArmatureAnimation* pArmature )
{
	if (!pArmature)return ToolFrame::EmptyVectorString();
	return pArmature->getAnimationData()->movementNames;
}

bool ApiCocos2dx::GetMovementName( VectorString& vMovementName,const Armature* pArmature,const VectorInt& vIndex )
{
	if (!pArmature)return false;
	return GetMovementName(vMovementName,pArmature->getAnimation(),vIndex);
}

bool ApiCocos2dx::GetMovementName( VectorString& vMovementName,const ArmatureAnimation* pArmature,const VectorInt& vIndex )
{
	if (!pArmature)return false;

	VectorInt::const_iterator itr;
	foreach(itr,vIndex){
		const std::string& sName = GetMovementName(pArmature,*itr);
		if (!sName.empty())
			vMovementName.push_back(sName);
	}

	return !vMovementName.empty();
}

Image* ApiCocos2dx::CreateImage( const Sprite* pSprite )
{
	if (!pSprite)return nullptr;

	Sprite* pNewSpr = Sprite::createWithSpriteFrame(pSprite->getSpriteFrame());
	pNewSpr->setAnchorPoint(Vec2::ZERO);
	CCRenderTexture* pRender = CCRenderTexture::create(pNewSpr->getContentSize().width, pNewSpr->getContentSize().height, kCCTexture2DPixelFormat_RGBA8888);
	pRender->begin();
	pNewSpr->visit();
	pRender->end();
	return pRender->newImage();
}

Image* ApiCocos2dx::CreateImage( const std::string& sPath)
{
	if (sPath.empty())return nullptr;

	Image* pImage = new Image();
	if (!pImage)return nullptr;

	if (!pImage->initWithImageFile(sPath))
	{
		delete pImage;
		return nullptr;
	}
	return pImage;
}

int ApiCocos2dx::GetOpacityWithPoint( const Sprite* pSprite, const Point& pt )
{
	return GetOpacityWithPoint(CreateImage(pSprite),pt);
}

int ApiCocos2dx::GetOpacityWithPoint( const Image* pImgView, const Point& pt )
{
	if (!pImgView)return -1;
	
	Image* pImage = ToolFrame::ConstCast(pImgView);

	//该data值是把二维数组展开成一个一维数组,因为每个像素值由RGBA组成,所以每隔4个char为一个RGBA,并且像素以横向排列
	ssize_t nIndex = 4 * ((pImage->getHeight() - (int)(pt.y) - 1) * pImage->getWidth() + (int)(pt.x)) + 3; 

	unsigned char* data = pImage->getData();
	if (nIndex >= pImage->getDataLen())return -1;

	return data[nIndex];
}

int ApiCocos2dx::GetOpacityWithPoint( const ImageView* pImgView, const Point& pt )
{
	if (!pImgView)return -1;

	return GetOpacityWithPoint(dynamic_cast<const Sprite*>(ToolFrame::ConstCast(pImgView)->getVirtualRenderer()),pt);
}

bool ApiCocos2dx::ActionsSetValue( LoadingBar* pNode,const float& nValue,float fDuration /*= 1.f*/ )
{
	if (!pNode)return false;

	if (fDuration <= 0.f)
		return ApiCocos2dx::SetValue(pNode,nValue);

	pNode->stopActionByTag(COCOS_ACTION_SET_VALUE);
	ActionInterval* pAction = TActionSetValue<LoadingBar,float>::create(nValue,fDuration);
	if (!pAction)return false;

	pNode->runAction(pAction);
	return true;
}

bool ApiCocos2dx::ActionsSetValue( TextAtlas* pNode,const int& nValue,float fDuration /*= 1.f*/ )
{
	if (!pNode)return false;

	if (fDuration <= 0.f)
		return ApiCocos2dx::SetValue(pNode,nValue);

	pNode->stopActionByTag(COCOS_ACTION_SET_VALUE);
	ActionInterval* pAction = TActionSetValue<TextAtlas,int>::create(nValue,fDuration);
	if (!pAction)return false;

	pNode->runAction(pAction);
	return true;
}

bool ApiCocos2dx::ActionsSetValue( Text* pNode,const int& nValue,float fDuration /*= 1.f*/ )
{
	if (!pNode)return false;

	if (fDuration <= 0.f)
		return ApiCocos2dx::SetValue(pNode,nValue);

	pNode->stopActionByTag(COCOS_ACTION_SET_VALUE);
	ActionInterval* pAction = TActionSetValue<Text,int>::create(nValue,fDuration);
	if (!pAction)return false;

	pNode->runAction(pAction);
	return true;
}

bool ApiCocos2dx::ActionsSetValue( Text* pNode,const float& fValue,float fDuration /*= 1.f*/ )
{
	if (!pNode)return false;

	if (fDuration <= 0.f)
		return ApiCocos2dx::SetValue(pNode,fValue);

	pNode->stopActionByTag(COCOS_ACTION_SET_VALUE);
	ActionInterval* pAction = TActionSetValue<Text,float>::create(fValue,fDuration);
	if (!pAction)return false;

	pNode->runAction(pAction);
	return true;
}

bool ApiCocos2dx::ActionsSetValue( Text* pNode,const std::string& sValue,float fDuration /*= 1.f*/ )
{
	if (!pNode)return false;

	if (fDuration <= 0.f)
		return ApiCocos2dx::SetValue(pNode,sValue);
	
	int nValueTarget=0;int nValueBegin=0;
	if (ToolFrame::ToValue(sValue,nValueTarget) && ToolFrame::ToValue(pNode->getString(),nValueBegin))
	{
		pNode->stopActionByTag(COCOS_ACTION_SET_VALUE);
		ActionInterval* pAction = TActionSetValue<Text,int>::create(nValueTarget,fDuration);
		if (!pAction)return false;

		pNode->runAction(pAction);
		return true;
	}
	
	return SetValue(pNode,sValue);
}

Size ApiCocos2dx::GetVisibleSize()
{
	return Director::getInstance()->getVisibleSize();
}

const VectorString& ApiCocos2dx::GetAnimationMovementNames( const Armature* pArmature )
{
	if (!pArmature)return ToolFrame::EmptyVectorString();

	return GetAnimationMovementNames(pArmature->getAnimation());
}

const VectorString& ApiCocos2dx::GetAnimationMovementNames( const ArmatureAnimation* pArmature )
{
	if (!pArmature)return ToolFrame::EmptyVectorString();

	return pArmature->getAnimationData()->movementNames;
}

bool ApiCocos2dx::ActionRotateTo( Node* pNode,float fAngle,float fDuration /*= 1.f*/ )
{
	if (!pNode)return false;

	pNode->stopActionByTag(COCOS_ACTION_ROTATE_TO);
	Action* pAc = RotateTo::create(fDuration,fAngle);
	if (!pAc)return false;
	pAc->setTag(COCOS_ACTION_ROTATE_TO);

	pNode->runAction(pAc);
	return true;
}

bool ApiCocos2dx::ActionRotateBy( Node* pNode,float fAngle,float fDuration /*= 1.f*/ )
{
	if (!pNode)return false;

	Action* pAc = RotateBy::create(fDuration,fAngle);
	if (!pAc)return false;

	pNode->runAction(pAc);
	return true;
}

bool ApiCocos2dx::ActionMoveTo( Node* pNode,const Vec2& ptPostion,float fDuration /*= 1.f*/ )
{
	if (!pNode)return false;

	pNode->stopActionByTag(COCOS_ACTION_MOVE_TO);
	Action* pAc = MoveTo::create(fDuration,ptPostion);
	if (!pAc)return false;
	pAc->setTag(COCOS_ACTION_MOVE_TO);

	pNode->runAction(pAc);
	return true;
}

bool ApiCocos2dx::ActionMoveBy( Node* pNode,const Vec2& ptPostion,float fDuration /*= 1.f*/ )
{
	if (!pNode)return false;
	
	Action* pAc = MoveBy::create(fDuration,ptPostion);
	if (!pAc)return false;

	pNode->runAction(pAc);
	return true;
}

bool ApiCocos2dx::ActionSkewTo( Node* pNode,float sx,float sy,float fDuration /*= 1.f*/ )
{
	if (!pNode)return false;

	pNode->stopActionByTag(COCOS_ACTION_SKEW_TO);
	Action* pAc = SkewTo::create(fDuration,sx,sy);
	if (!pAc)return false;
	pAc->setTag(COCOS_ACTION_SKEW_TO);

	pNode->runAction(pAc);
	return true;
}

bool ApiCocos2dx::ActionSkewBy( Node* pNode,float sx,float sy,float fDuration /*= 1.f*/ )
{
	if (!pNode)return false;

	Action* pAc = SkewBy::create(fDuration,sx,sy);
	if (!pAc)return false;

	pNode->runAction(pAc);
	return true;
}

bool ApiCocos2dx::ActionJumpTo( Node* pNode,const Vec2& ptPostion,float fHeight,int nJumps,float fDuration /*= 1.f*/ )
{
	if (!pNode)return false;

	pNode->stopActionByTag(COCOS_ACTION_JUMP_TO);
	Action* pAc = JumpTo::create(fDuration,ptPostion,fHeight,nJumps);
	if (!pAc)return false;
	pAc->setTag(COCOS_ACTION_JUMP_TO);

	pNode->runAction(pAc);
	return true;
}

bool ApiCocos2dx::ActionJumpBy( Node* pNode,const Vec2& ptPostion,float fHeight,int nJumps,float fDuration /*= 1.f*/ )
{
	if (!pNode)return false;

	Action* pAc = JumpBy::create(fDuration,ptPostion,fHeight,nJumps);
	if (!pAc)return false;

	pNode->runAction(pAc);
	return true;
}

bool ApiCocos2dx::ActionScaleTo( Node* pNode,float fScale,float fDuration /*= 1.f*/ )
{
	if (!pNode)return false;

	//缩放是需要独占的
	pNode->stopActionByTag(COCOS_ACTION_SCALE_TO);
	Action* pAc = ScaleTo::create(fDuration,fScale);
	if (!pAc)return false;
	pAc->setTag(COCOS_ACTION_SCALE_TO);

	pNode->runAction(pAc);
	return true;
}

bool ApiCocos2dx::ActionScaleBy( Node* pNode,float fScale,float fDuration /*= 1.f*/ )
{
	if (!pNode)return false;

	Action* pAc = ScaleBy::create(fDuration,fScale);
	if (!pAc)return false;

	pNode->runAction(pAc);
	return true;
}

bool ApiCocos2dx::ActionBlink( Node* pNode,int nBlinks,float fDuration /*= 1.f*/ )
{
	if (!pNode)return false;

	Action* pAc = Blink::create(fDuration,nBlinks);
	if (!pAc)return false;

	pNode->runAction(pAc);
	return true;
}

bool ApiCocos2dx::ActionFadeTo( Node* pNode,GLubyte opacity,float fDuration /*= 1.f*/ )
{
	if (!pNode)return false;

	pNode->stopActionByTag(COCOS_ACTION_FADE_TO);
	Action* pAc = FadeTo::create(fDuration,opacity);
	if (!pAc)return false;
	pAc->setTag(COCOS_ACTION_FADE_TO);

	pNode->runAction(pAc);
	return true;
}

bool ApiCocos2dx::ActionFadeIn( Node* pNode,float fDuration /*= 1.f*/ )
{
	if (!pNode)return false;

	pNode->stopActionByTag(COCOS_ACTION_FADE_TO);
	Action* pAc = FadeIn::create(fDuration);
	if (!pAc)return false;
	pAc->setTag(COCOS_ACTION_FADE_TO);

	pNode->runAction(pAc);
	return true;
}

bool ApiCocos2dx::ActionFadeOut( Node* pNode,float fDuration /*= 1.f*/ )
{
	if (!pNode)return false;

	pNode->stopActionByTag(COCOS_ACTION_FADE_TO);
	Action* pAc = FadeOut::create(fDuration);
	if (!pAc)return false;
	pAc->setTag(COCOS_ACTION_FADE_TO);
	
	pNode->runAction(pAc);
	return true;
}

bool ApiCocos2dx::ActionTintTo( Node* pNode,GLubyte red, GLubyte green, GLubyte blue,float fDuration /*= 1.f*/ )
{
	if (!pNode)return false;

	pNode->stopActionByTag(COCOS_ACTION_TINT_TO);
	Action* pAc = TintTo::create(fDuration,red,green,blue);
	if (!pAc)return false;
	pNode->setTag(COCOS_ACTION_TINT_TO);

	pNode->runAction(pAc);
	return true;
}

bool ApiCocos2dx::ActionTintBy( Node* pNode,GLubyte red, GLubyte green, GLubyte blue,float fDuration /*= 1.f*/ )
{
	if (!pNode)return false;

	Action* pAc = TintBy::create(fDuration,red,green,blue);
	if (!pAc)return false;

	pNode->runAction(pAc);
	return true;
}

bool ApiCocos2dx::IsDistanceLessThan( const Vec2& pt1,const Vec2& pt2,float fDistance )
{
	return CalDistanceSquared(pt1,pt2) < fDistance*fDistance;
}

bool ApiCocos2dx::IsDistanceGreaterThan( const Vec2& pt1,const Vec2& pt2,float fDistance )
{
	return CalDistanceSquared(pt1,pt2) > fDistance*fDistance;
}

ParticleSystemQuad* ApiCocos2dx::PlayParticle( const std::string& sFile )
{
	ParticleSystemQuad* pParticle = ParticleSystemQuad::create(sFile);
	if (!pParticle)return nullptr;

	pParticle->setPosition(0.f,0.f);

	return pParticle;
}

Node* ApiCocos2dx::FindRootNode(Node* pNode){
	if (!pNode)return nullptr;
	while(pNode->getParent()){
		pNode = pNode->getParent();
	}
	return pNode;
};

bool ApiCocos2dx::SleepFreeTime()
{
	double fTime = Director::getInstance()->getAnimationInterval() - Director::getInstance()->getSecondsPerFrame() ;
	if (fTime>0)
		ToolFrame::Sleep(fTime*1000);

	return true;
}

bool ApiCocos2dx::PurgeCachedData()
{
	ApiCocos2dx::PurgeActionCache();
	ApiCocos2dx::PurgeArmatureCache();
	ApiCocos2dx::PurgeSpineSkeletonDataCache();
	ApiCocos2dx::PurgeSpineAtlasCache();		//清理Spine
	Director::getInstance()->purgeCachedData();
	return true;
}

bool ApiCocos2dx::PurgeArmatureCache()
{
	ArmatureDataManager::getInstance()->destroyInstance();
	return true;
}

bool ApiCocos2dx::SetName( Widget* pWidget,const std::string& sName )
{
	if (!pWidget)return false;

	pWidget->setName(sName);
	return true;
}

ImageView* ApiCocos2dx::CreateImageView( const std::string& sFile,Widget::TextureResType texType /*= Widget::TextureResType::LOCAL*/)
{
	return ImageView::create(sFile,texType);
}

LoadingBar* ApiCocos2dx::CreateLoadingBar( const std::string& sPath )
{
	return LoadingBar::create(sPath);
}

TMXTiledMap* ApiCocos2dx::CreateTiledMap( const std::string& sPath)
{
	return TMXTiledMap::create(sPath);
}

Skin* ApiCocos2dx::CreateSkin( const std::string& sPath)
{
	return Skin::create(sPath);
}

bool ApiCocos2dx::CacheSpriteFrames( const std::string& sPath)
{
 	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(sPath);
	return true;
}

bool ApiCocos2dx::LoadTexture( LoadingBar* pBar,const std::string& sPath,ui::Widget::TextureResType texType /*= TextureResType::LOCAL*/)
{
	if (!pBar)return false;
	if (sPath.empty())return false;

	pBar->loadTexture(sPath,texType);
	return true;
}

bool ApiCocos2dx::LoadTexture( ImageView* pImageView,const std::string& sPath,ui::Widget::TextureResType texType /*= TextureResType::LOCAL*/)
{
	if (!pImageView)return false;
	if (sPath.empty())return false;

	pImageView->ignoreContentAdaptWithSize(true);
	pImageView->loadTexture(sPath,texType);
	
	return true;
}

bool ApiCocos2dx::LoadTexture( Button* btn, const std::string& sPath,ui::Widget::TextureResType texType /*= ui::Widget::TextureResType::LOCAL*/)
{
	if (!btn)return false;
	if (sPath.empty())return false;

	btn->ignoreContentAdaptWithSize(true);
	btn->loadTextureNormal(sPath,texType);
	
	return true;
}

SpriteFrame* ApiCocos2dx::CreateSpriteFrame( const std::string& sPath,const Rect& rRect)
{
	return SpriteFrame::create(sPath,rRect);
}

bool ApiCocos2dx::IsTargetWidgetBegin( const Ref* pObj,const std::string& sName )
{
	if (!pObj)return false;
	if (sName.empty())return false;

	const Widget* pWidget = dynamic_cast<const Widget*>(pObj);
	if (!pWidget)return false;

	return ToolFrame::IsBeginWith(pWidget->getName(),sName);
}

bool ApiCocos2dx::SetText( TextField* pText,const std::string& sText )
{
	if (!pText)return false;
	pText->setText("");
	pText->setText(sText);
	return true;
}

bool ApiCocos2dx::SetText( Text* pText,const std::string& sText )
{
	if (!pText)return false;
	pText->setText("                                       ");//先置空
	pText->setText(sText);
	return true;
}

void ApiCocos2dx::DrawSolidSector( DrawNode* pNode ,const Vec2 &orign,const float fBeginAngle, const float radius1, const float radius2, const float fAngelFanShaped, const int segments, const Color4F &color )
{
	float angle = M_PI * fBeginAngle / 180.f;
	float radian = M_PI * fAngelFanShaped / 180.f;
	//angle = atanf(1);
	//float angle = atanf(vecBegin.x / vecBegin.y);
	float coef = radian/segments;
	Vec2 *vertices1 = new (std::nothrow) Vec2[segments+1];
	if( ! vertices1 )
		return;
	Vec2 *vertices2 = new (std::nothrow) Vec2[segments+1];
	if( ! vertices2 )
		return;

	for(int i = 0;i <= segments; i++)
	{
		float rads = i*coef;
		GLfloat j = radius1 * cosf(rads + angle) + orign.y;
		GLfloat k = radius1 * sinf(rads + angle) + orign.x;

		vertices1[i].x = k;
		vertices1[i].y = j;

		GLfloat l = radius2 * cosf(rads + angle) + orign.y;
		GLfloat m = radius2 * sinf(rads + angle) + orign.x;

		vertices2[i].x = m;
		vertices2[i].y = l;
	}

	V2F_C4B_T2F_Triangle *triangles = new V2F_C4B_T2F_Triangle[segments*2];

	int triCount = 0;
	for (int i=0; i<segments; i++) {
		triangles[triCount].a.vertices = vertices1[i];
		triangles[triCount].b.vertices = vertices2[i];
		triangles[triCount++].c.vertices = vertices2[i+1];

		triangles[triCount].a.vertices = vertices1[i];
		triangles[triCount].b.vertices = vertices1[i+1];
		triangles[triCount++].c.vertices = vertices2[i+1];
	}

	for (int i=0; i<segments*2; i++) {
		pNode->drawTriangle(triangles[i].a.vertices, triangles[i].b.vertices, triangles[i].c.vertices, color);
	}

	CC_SAFE_DELETE_ARRAY(vertices1);
	CC_SAFE_DELETE_ARRAY(vertices2);
	CC_SAFE_DELETE_ARRAY(triangles);
}

Sprite* ApiCocos2dx::MakeSpriteAnnularSector ( float fRadius1,float fRadius2,float fAngel,const Color4F& rFill,int nSegments /*= 40*/ )
{
	if (fRadius1 < 0.f || fRadius2 <= 0.f)return nullptr;
	if (fRadius1 >= fRadius2)return nullptr;
	
	DrawNode* pNode = DrawNode::create();
	CCRenderTexture *rt = CCRenderTexture::create(fRadius2 * 2, fRadius2 * 2);

	rt->begin();

	DrawSolidSector(pNode,Vec2(fRadius2,fRadius2), -fAngel/2, fRadius1, fRadius2, fAngel, nSegments,rFill );
	pNode->visit();

	rt->end();

	Sprite*  pSprite = Sprite::createWithTexture(rt->getSprite()->getTexture());
	if (!pSprite)return nullptr;
	pSprite->setFlippedY(true);
	return pSprite;
}

Vec2 ApiCocos2dx::ToVec(const ToolFrame::CPoint2d& pt){
	return Vec2(pt.GetX(),pt.GetY());
}

ToolFrame::CPoint2d ApiCocos2dx::ToPoint2d(const Vec2& vec2){
	return ToolFrame::CPoint2d(vec2.x,vec2.y);
}

Sprite* ApiCocos2dx::MakeSpriteLine ( const ToolFrame::VectorPoint2d& vPoint, float fRadius, const Color4F& clr )
{
	if (fRadius <= 0.f)return nullptr;
	if (vPoint.empty())return nullptr;

	ToolFrame::CRect2d rBoundingBox = ToolFrame::MakeBoundingBox(vPoint);
	if (rBoundingBox.GetWidth()<1.f || rBoundingBox.GetHeight()<1.f)return nullptr;

	ToolFrame::CPoint2d ptCenter = vPoint.front();
	DrawNode* pNode = DrawNode::create();
	CCRenderTexture *rt = CCRenderTexture::create(rBoundingBox.GetWidth(),rBoundingBox.GetHeight());

	rt->begin();

	ToolFrame::VectorPoint2d::const_iterator itr;
	foreach(itr,vPoint){
		ToolFrame::VectorPoint2d::const_iterator itrNext=itr;
		++itrNext;
		if (itrNext != vPoint.end())
		{
			pNode->drawSegment(ToVec(*itr),ToVec(*itrNext),fRadius,clr);
		}
	}

	pNode->visit();

	rt->end();

	Sprite*  pSprite = Sprite::createWithTexture(rt->getSprite()->getTexture());
	if (!pSprite)return nullptr;
	//计算锚点
	pSprite->setAnchorPoint(Vec2(ptCenter.GetX()/rBoundingBox.GetWidth(),ptCenter.GetY()/rBoundingBox.GetHeight()));
	pSprite->setFlippedY(true);
	return pSprite;
}
float ApiCocos2dx::GetRotation( Node* pNode )
{
	if (!pNode)return 0.f;
	return pNode->getRotation();
}

Widget* ApiCocos2dx::FindWidgetByTag( const VectorWidget& vWidget,int nTag )
{
	VectorWidget::const_iterator itr;
	foreach(itr,vWidget){
		Widget* pWiget = *itr;
		if (pWiget && pWiget->getTag() == nTag)
			return pWiget;
	}

	return nullptr;
}

Node* ApiCocos2dx::FindChildByTag(const Node* pWidget,int nTag){
	if (!pWidget)return nullptr;

	return pWidget->getChildByTag(nTag);
}

bool ApiCocos2dx::RemoveAllChildren( Node* pWidget){
	if(!pWidget)return false;

	pWidget->removeAllChildren();
	return true;
}

bool ApiCocos2dx::IsTouchedNode(const Node* pNode,const Touch* touch){
	if (!pNode || !touch)return false;
	return pNode->boundingBox().containsPoint( pNode->getParent()->convertTouchToNodeSpace( (Touch*)touch ));
}
bool ApiCocos2dx::IsTouchedNode(const Widget* pNode,const Touch* touch){
	if (!pNode || !touch)return false;
	return pNode->boundingBox().containsPoint( pNode->getParent()->convertTouchToNodeSpace( (Touch*)touch ));
}

Node* ApiCocos2dx::FindTouchedNode(const VectorNode& vNode,const Touch* touch){
	if (vNode.empty())return nullptr;
	if (!touch)return nullptr;

	VectorNode::const_iterator itr;
	foreach(itr,vNode){
		Node* pNode = *itr;
		if (pNode  && IsTouchedNode(pNode,touch))
			return pNode;
	}
	return nullptr;
}

Widget* ApiCocos2dx::FindTouchedNode(const VectorWidget& vNode,const Touch* touch)
{
	if (vNode.empty())return nullptr;
	if (!touch)return nullptr;
	
	VectorWidget::const_iterator itr;
	foreach(itr,vNode){
		Widget* pNode = *itr;
		if (pNode  && IsTouchedNode(pNode,touch))
			return pNode;
	}
	return nullptr;
}

Widget* ApiCocos2dx::FindTouchedNode( const MapIntWidget& vNode,const Touch* touch )
{
	if (vNode.empty())return nullptr;
	if (!touch)return nullptr;

	MapIntWidget::const_iterator itr;
	foreach(itr,vNode){
		Widget* pNode = itr->second;
		if (pNode  && IsTouchedNode(pNode,touch))
			return pNode;
	}
	return nullptr;
}

Node* ApiCocos2dx::FindTouchedNode( const Touch* touch,Node* pNode )
{
	if (IsTouchedNode(pNode,touch))return pNode;
	return nullptr;
}

Node* ApiCocos2dx::FindTouchedNode( const Touch* touch,Node* pNode1,Node* pNode2 )
{
	if (IsTouchedNode(pNode1,touch))return pNode1;
	if (IsTouchedNode(pNode2,touch))return pNode2;
	return nullptr;
}

Node* ApiCocos2dx::FindTouchedNode( const Touch* touch,Node* pNode1,Node* pNode2,Node* pNode3 )
{
	if (IsTouchedNode(pNode1,touch))return pNode1;
	if (IsTouchedNode(pNode2,touch))return pNode2;
	if (IsTouchedNode(pNode3,touch))return pNode3;
	return nullptr;
}

Node* ApiCocos2dx::FindTouchedNode( const Touch* touch,Node* pNode1,Node* pNode2,Node* pNode3,Node* pNode4 )
{
	if (IsTouchedNode(pNode1,touch))return pNode1;
	if (IsTouchedNode(pNode2,touch))return pNode2;
	if (IsTouchedNode(pNode3,touch))return pNode3;
	if (IsTouchedNode(pNode4,touch))return pNode4;
	return nullptr;
}

Node* ApiCocos2dx::FindTouchedNode( const Touch* touch,Node* pNode1,Node* pNode2,Node* pNode3,Node* pNode4,Node* pNode5 )
{
	if (IsTouchedNode(pNode1,touch))return pNode1;
	if (IsTouchedNode(pNode2,touch))return pNode2;
	if (IsTouchedNode(pNode3,touch))return pNode3;
	if (IsTouchedNode(pNode4,touch))return pNode4;
	if (IsTouchedNode(pNode5,touch))return pNode5;
	return nullptr;
}

spAtlas* ApiCocos2dx::CacheSpineAtlas( const std::string& atlasFile )
{
	spAtlas* pData = ToolFrame::GetPtrValueByKey(g_vSpineAtlas,atlasFile);
	if (pData)return pData;

	pData = spAtlas_createFromFile(atlasFile.c_str(), 0);
	CCASSERT(pData, "Error reading atlas file.");
	if (!pData)return nullptr;

	ToolFrame::Insert(g_vSpineAtlas,atlasFile,pData);
	return pData;
}

spSkeletonData* ApiCocos2dx::CacheSpineSkeletonData( const std::string& skeletonDataFile, const std::string& atlasFile, float scale/*=1.0f*/ )
{
	spAtlas* atlas = CacheSpineAtlas(atlasFile);
	if (!atlas)return nullptr;

	spSkeletonData* pData = nullptr;

	spAttachmentLoader* pLoader = SUPER(Cocos2dAttachmentLoader_create(atlas));
	auto skeletonFileType = cocos2d::FileUtils::getInstance()->getFileExtension(skeletonDataFile);
	if (skeletonFileType == ".json") {
		spSkeletonJson* json = spSkeletonJson_createWithLoader(pLoader);
		json->scale = scale;
		pData = spSkeletonJson_readSkeletonDataFile(json, skeletonDataFile.c_str());
		CCASSERT(pData, json->error ? json->error : "Error reading skeleton data file.");
		spSkeletonJson_dispose(json);
	}
	else if (skeletonFileType == ".skel") {
		spSkeletonBinary* binary = spSkeletonBinary_createWithLoader(pLoader);
		binary->scale = scale;
		pData = spSkeletonBinary_readSkeletonDataFile(binary, skeletonDataFile.c_str());
		CCASSERT(pData, binary->error ? binary->error : "Error reading skeleton data file.");
		spSkeletonBinary_dispose(binary);
	}	return pData;


// 	spSkeletonData* pData = ToolFrame::GetPtrValueByKey(g_vSpineSkeletonData,skeletonDataFile);
// 	if (pData)return pData;
// 
// 	spAttachmentLoader* _attachmentLoader = SUPER(Cocos2dAttachmentLoader_create(atlas));

// 	auto skeletonFileType = cocos2d::FileUtils::getInstance()->getFileExtension(skeletonDataFile);
// 	if (skeletonFileType == ".json") {
// 		spSkeletonJson* json = spSkeletonJson_createWithLoader(_attachmentLoader);
// 		json->scale = scale;
// 		pData = spSkeletonJson_readSkeletonDataFile(json, skeletonDataFile.c_str());
// 		CCASSERT(pData, json->error ? json->error : "Error reading skeleton data file.");
// 		spSkeletonJson_dispose(json);
// 	}
// 	else if (skeletonFileType == ".skel") {
// 		spSkeletonBinary* binary = spSkeletonBinary_createWithLoader(_attachmentLoader);
// 		binary->scale = scale;
// 		pData = spSkeletonBinary_readSkeletonDataFile(binary, skeletonDataFile.c_str());
// 		CCASSERT(pData, binary->error ? binary->error : "Error reading skeleton data file.");
// 		spSkeletonBinary_dispose(binary);
// 	}// 
// 	if (!pData)return nullptr;
// 	 
// 	ToolFrame::Insert(g_vSpineSkeletonData,skeletonDataFile,pData);
//	return pData;
}

bool ApiCocos2dx::PurgeSpineAtlasCache()
{
	if (ToolFrame::IsEmpty(g_vSpineAtlas))return false;

	MapStringAtlas::iterator itr;
	foreach(itr,g_vSpineAtlas){
		spAtlas* pData = itr->second;
		ASSERT_LOG_ERROR(pData);

		spAtlas_dispose(pData);
	}

	ToolFrame::Clear(g_vSpineAtlas);
	return true;
}

bool ApiCocos2dx::PurgeSpineSkeletonDataCache()
{
	if (ToolFrame::IsEmpty(g_vSpineSkeletonData))return false;

	MapStringSkeletonData::iterator itr;
	foreach(itr,g_vSpineSkeletonData){
		spSkeletonData* pData = itr->second;
		ASSERT_LOG_ERROR(pData);

		spSkeletonData_dispose(pData);
	}

	ToolFrame::Clear(g_vSpineSkeletonData);
	return true;
}

SkeletonAnimation* ApiCocos2dx::CreateSpineAnimation( const std::string& skeletonDataFile, const std::string& atlasFile, float scale/*=1.0f*/ )
{
	spSkeletonData* pData = CacheSpineSkeletonData(skeletonDataFile, atlasFile,scale);
	if (!pData)return nullptr;

	SkeletonAnimation* pAnimation = SkeletonAnimation::createWithData(pData);
	if (!pAnimation)return nullptr;
	pAnimation->setAnchorPoint(ccp(0.5f, 0.5f));
	return pAnimation;
}

bool ApiCocos2dx::GetSpineAnimationName( VectorString& vName,const SkeletonAnimation* pAnimation )
{
	if (!pAnimation)return false;

	const spSkeletonData* pData =  ((SkeletonAnimation*)pAnimation)->getSkeleton()->data;
	if (!pData)return false;

	for(int nIndex =0;nIndex < pData->animationsCount;++nIndex){
		const spAnimation* pAnimationSub = pData->animations[nIndex];
		ASSERT_LOG_ERROR(pAnimationSub);
		vName.push_back(pAnimationSub->name);
	}

	return true;
}

const spAnimation* ApiCocos2dx::FindAnimationByName(const SkeletonAnimation* pAnimation, const std::string& sName)
{
	if (!pAnimation)return nullptr;

	const spSkeletonData* pData = ((SkeletonAnimation*)pAnimation)->getSkeleton()->data;
	if (!pData)return nullptr;

	for (int nIndex = 0; nIndex < pData->animationsCount; ++nIndex) {
		const spAnimation* pAnimationSub = pData->animations[nIndex];
		ASSERT_LOG_ERROR(pAnimationSub);
		if (sName == pAnimationSub->name)
			return pAnimationSub;
	}

	return nullptr;
}

float ApiCocos2dx::GetAnimationDuration(const SkeletonAnimation* pAnimation, const std::string& sName)
{
	const spAnimation* pAnimationSub = FindAnimationByName(pAnimation, sName);
	if (!pAnimationSub)return 0.f;
	return pAnimationSub->duration;
}

SkeletonAnimation* ApiCocos2dx::PlaySpineAnimation(const std::string& skeletonDataFile, const std::string& atlasFile, const VectorString& vName, int nLoop/*=-1*/, float fDelay)
{
	SkeletonAnimation* pAnimation = CreateSpineAnimation(skeletonDataFile,atlasFile);
	if (!pAnimation)return nullptr;

	return PlaySpineAnimation(pAnimation,vName,nLoop,fDelay);
}

SkeletonAnimation* ApiCocos2dx::PlaySpineAnimation( const std::string& skeletonDataFile, const std::string& atlasFile,int nLoop/*=-1*/,float fDelay )
{
	SkeletonAnimation* pAnimation = CreateSpineAnimation(skeletonDataFile,atlasFile);
	if (!pAnimation)return nullptr;

	VectorString vName;
	if (!GetSpineAnimationName(vName,pAnimation))return nullptr;

	return PlaySpineAnimation(pAnimation,vName,nLoop,fDelay);
}

SkeletonAnimation* ApiCocos2dx::PlaySpineAnimation( const std::string& skeletonDataFile, const std::string& atlasFile,const std::string& sName,int nLoop/*=-1*/,float fDelay)
{
	SkeletonAnimation* pNode = CreateSpineAnimation(skeletonDataFile,atlasFile);
	if (!pNode)return nullptr;

	VectorString vName;
	vName.push_back(sName);

	return PlaySpineAnimation(pNode,vName,nLoop,fDelay);
}

SkeletonAnimation* ApiCocos2dx::PlaySpineAnimation( const std::string& skeletonDataFile, const std::string& atlasFile,const std::string& sName1,const std::string& sName2,int nLoop/*=-1*/ ,float fDelay)
{
	SkeletonAnimation* pNode = CreateSpineAnimation(skeletonDataFile,atlasFile);
	if (!pNode)return nullptr;

	VectorString vName;
	vName.push_back(sName1);
	vName.push_back(sName2);

	return PlaySpineAnimation(pNode,vName,nLoop,fDelay);
}

SkeletonAnimation* ApiCocos2dx::PlaySpineAnimation( SkeletonAnimation* pAnimation,const VectorString& vName,int nLoop/*=-1*/,float fDelay/*=0.f*/)
{
	if (!pAnimation)return nullptr;

	VectorString vNameVaild;

	VectorString vNameHas;
	ApiCocos2dx::GetSpineAnimationName(vNameHas,pAnimation);

	ToolFrame::Intersection(vNameVaild,vName,vNameHas);

	if (vNameVaild.empty())return nullptr;

	spTrackEntry* pEntryEnd = nullptr;

	std::string sNamePer;
	for (uint uIndex = 0; uIndex < vNameVaild.size(); ++uIndex){
		//检查名字有效性

		//添加补间动画
		if (fDelay > 0.f){
			if (!sNamePer.empty())
				pAnimation->setMix(sNamePer,vNameVaild[uIndex],fDelay);

			sNamePer = vNameVaild[uIndex];
		}

		const std::string& sAniName = vNameVaild[uIndex];
		bool bLoop = uIndex+1 == vNameVaild.size();

		auto pAnimClip = pAnimation->findAnimation(sAniName);
		if (pAnimClip->duration == 0.0f)
			bLoop = false;

		if (0 == uIndex)
			pEntryEnd = pAnimation->setAnimation(0,sAniName,bLoop);
		else
			pEntryEnd = pAnimation->addAnimation(0,sAniName,bLoop,fDelay);
	}

	ASSERT_LOG_ERROR(pEntryEnd);

	//绑定监视
	bool bReqRemove = nLoop >= 0;
	CActionSpineMonitor* pMonitor = ApiCocos2dx::FindActionByTag<CActionSpineMonitor>(pAnimation, COCOS_ACTION_SPINE_MONITOR);
	if (!pMonitor)
	{
		pMonitor = CActionSpineMonitor::create(nLoop, bReqRemove);
		if (pMonitor) {
			pMonitor->SetEntryEnd(pEntryEnd);
			pAnimation->runAction(pMonitor);
		}
	}
	else {
		pMonitor->SetLoop(nLoop);
		pMonitor->SetRemove(bReqRemove);
		pMonitor->SetEntryEnd(pEntryEnd);
	}
	return pAnimation;
}

SkeletonAnimation* ApiCocos2dx::SetSpineCallBackEvent(SkeletonAnimation* pAnimation, FnActionSpineEvent fnEvent)
{
	if (!pAnimation)return nullptr;

	CActionSpineMonitor* pMonitor = ApiCocos2dx::FindActionByTag<CActionSpineMonitor>(pAnimation, COCOS_ACTION_SPINE_MONITOR);
	if (!pMonitor)return nullptr;

	pMonitor->SetCallBackEvent(fnEvent);

	return pAnimation;
}

SkeletonAnimation* ApiCocos2dx::SetSpineCallBackEventErr(SkeletonAnimation* pAnimation, FnActionSpineEvent fnEvent)
{
	if (!pAnimation)return nullptr;

	CActionSpineMonitor* pMonitor = ApiCocos2dx::FindActionByTag<CActionSpineMonitor>(pAnimation, COCOS_ACTION_SPINE_MONITOR);
	if (!pMonitor)return nullptr;

	pMonitor->SetCallBackEventErr(fnEvent);

	return pAnimation;
}

SkeletonAnimation* ApiCocos2dx::SetSpineCallBackOver(SkeletonAnimation* pAnimation, FnActionSpineOver fnOver)
{
	if (!pAnimation)return nullptr;

	CActionSpineMonitor* pMonitor = ApiCocos2dx::FindActionByTag<CActionSpineMonitor>(pAnimation, COCOS_ACTION_SPINE_MONITOR);
	if (!pMonitor)return nullptr;

	pMonitor->SetCallBackOver(fnOver);

	return pAnimation;
}

spine::SkeletonAnimation* ApiCocos2dx::SetSpineRemove(SkeletonAnimation* pAnimation, bool bRemove)
{
	if (!pAnimation)return nullptr;

	CActionSpineMonitor* pMonitor = ApiCocos2dx::FindActionByTag<CActionSpineMonitor>(pAnimation, COCOS_ACTION_SPINE_MONITOR);
	if (!pMonitor)return nullptr;

	pMonitor->SetRemove(bRemove);

	return pAnimation;
}

bool ApiCocos2dx::RunCommand(std::string sEvent, std::string sEventArg, const XCommandArg* pArg /*= nullptr*/)
{
	if (sEvent.empty())return false;
	ToolFrame::ToUpperCase(sEvent);

	//根据使用频率排序 可以提高性能
	if (sEvent == "SHAKE")//震动
	{
		if (!pArg)return false;
		if (!pArg->pNodeShake)return false;

		if (sEventArg == "WEAK")
		{
			ApiCocos2dx::ActionsShake(pArg->pNodeShake, 0.2f, 10, 10);
			return true;
		}
		if (sEventArg == "NORMAL")
		{
			ApiCocos2dx::ActionsShake(pArg->pNodeShake, 0.2f, 50, 10);
			return true;
		}
		if (sEventArg == "STRONG")
		{
			ApiCocos2dx::ActionsShake(pArg->pNodeShake, 0.2f, 100, 10);
			return true;
		}
		return false;
	}

	if (sEvent == "SHAKE_KEEP")//震动
	{
		if (!pArg)return false;
		if (!pArg->pNodeShake)return false;

		VectorString vArg;
		ToolFrame::SplitString(vArg, sEventArg, ",");
		if (vArg.size() < 2)return false;
		const std::string& sType = vArg[0];
		float fDuration = 0.f;
		if (!ToolFrame::ToValue(vArg[1], fDuration))return false;

		if (sType == "WEAK")
		{
			ApiCocos2dx::ActionsShake(pArg->pNodeShake, fDuration, 10, 10);
			return true;
		}
		if (sType == "NORMAL")
		{
			ApiCocos2dx::ActionsShake(pArg->pNodeShake, fDuration, 50, 10);
			return true;
		}
		if (sType == "STRONG")
		{
			ApiCocos2dx::ActionsShake(pArg->pNodeShake, fDuration, 100, 10);
			return true;
		}
		return false;
	}

	if (sEvent == "SOUND_FILE")//音效
	{
		//拼接相对路径
		if (pArg && !pArg->sLocalDir.empty())
			sEventArg = pArg->sLocalDir + sEventArg;

		ApiCocos2dx::PlaySound(sEventArg);
		return true;
	}

	if (sEvent == "MUSIC_FILE")//音乐
	{
		//拼接相对路径
		if (pArg && !pArg->sLocalDir.empty())
			sEventArg = pArg->sLocalDir + sEventArg;

		ApiCocos2dx::PlayMusic(sEventArg);
		return true;
	}

	if (sEvent == "PARTICLE_FILE")//粒子
	{
		//拼接相对路径
		if (pArg && !pArg->sLocalDir.empty())
			sEventArg = pArg->sLocalDir + sEventArg;

		return false;
	}

	return false;
}

SkeletonAnimation* ApiCocos2dx::PlaySpineAnimation(SkeletonAnimation* pAnimation, const std::string& sName, int nLoop/*=-1*/, float fDelay/*=0.3f*/)
{
	VectorString vName;
	vName.push_back(sName);

	return PlaySpineAnimation(pAnimation,vName,nLoop,fDelay);
}

SkeletonAnimation* ApiCocos2dx::PlaySpineAnimation( SkeletonAnimation* pAnimation,const std::string& sName1,const std::string& sName2,int nLoop/*=-1*/,float fDelay/*=0.3f*/ )
{
	VectorString vName;
	vName.push_back(sName1);
	vName.push_back(sName2);
	return PlaySpineAnimation(pAnimation,vName,nLoop,fDelay);
}

SkeletonAnimation* ApiCocos2dx::PlaySpineAnimation( const Point& ptPostion,const std::string& skeletonDataFile, const std::string& atlasFile,int nLoop/*=-1*/,float fDelay/*=0.f*/ )
{
	SkeletonAnimation* pNode = PlaySpineAnimation(skeletonDataFile,atlasFile,nLoop,fDelay);
	if (!pNode)return nullptr;

	pNode->setPosition(ptPostion);
	return pNode;
}

SkeletonAnimation* ApiCocos2dx::PlaySpineAnimation( const Point& ptPostion,const std::string& skeletonDataFile, const std::string& atlasFile,const std::string& sName,int nLoop/*=-1*/,float fDelay/*=0.f*/ )
{
	SkeletonAnimation* pNode = PlaySpineAnimation(skeletonDataFile,atlasFile,sName,nLoop,fDelay);
	if (!pNode)return nullptr;

	pNode->setPosition(ptPostion);
	return pNode;
}

SkeletonAnimation* ApiCocos2dx::PlaySpineAnimation( const Point& ptPostion,const std::string& skeletonDataFile, const std::string& atlasFile,const std::string& sName1,const std::string& sName2,int nLoop/*=-1*/,float fDelay/*=0.f*/ )
{
	SkeletonAnimation* pNode = PlaySpineAnimation(skeletonDataFile,atlasFile,sName1,sName2,nLoop,fDelay);
	if (!pNode)return nullptr;

	pNode->setPosition(ptPostion);
	return pNode;
}

SkeletonAnimation* ApiCocos2dx::PlaySpineAnimation( const Point& ptPostion,const std::string& skeletonDataFile, const std::string& atlasFile,const VectorString& vName,int nLoop/*=-1*/,float fDelay/*=0.f*/ )
{
	SkeletonAnimation* pNode = PlaySpineAnimation(skeletonDataFile,atlasFile,vName,nLoop,fDelay);
	if (!pNode)return nullptr;

	pNode->setPosition(ptPostion);
	return pNode;
}

SkeletonAnimation* ApiCocos2dx::BindSpineNode(SkeletonAnimation* pAnimation, const std::string& sBone, Node* pNode)
{
	Action* pAction = CActionSpineBindBones::create(pAnimation,sBone,pNode);
	if (!pAction)return nullptr;

	pAnimation->runAction(pAction);
	return pAnimation;
}

std::string ApiCocos2dx::GetSpineAnimationNameCur( SkeletonAnimation* pAnimation,int nTrackIndex /*=0 */ )
{
	const spTrackEntry* pTrackEntry = pAnimation->getCurrent(nTrackIndex);
	if (!pTrackEntry)return "";
	const spAnimation* pAni = pTrackEntry->animation;
	if (!pAni)return "";
	return pAni->name;
}

bool ApiCocos2dx::SetPostionCenter(Node* pNode) {
	return SetPostionCenter(pNode,ccp(0.5,0.5));
}

bool ApiCocos2dx::SetPostionCenter( Node* pNode,const Point& pt )
{
	if (!pNode)return false;

	Node* pParent = pNode->getParent();
	if (!pParent)return false;

	const Size& r = pParent->getContentSize();
	pNode->setPosition(r.width * pt.x,r.height * pt.y);
	return true;
}

bool ApiCocos2dx::SetWorldAnchorPoint(Node* pNode,const Vec2& ptWorld){
	if (!pNode)return false;
	const Size& rSize = pNode->getContentSize();
	if (rSize.width == 0 || rSize.height == 0 )
		return false;

	Vec2 pt = pNode->convertToNodeSpace(ptWorld);
	pNode->setAnchorPoint(Vec2(pt.x/rSize.width,pt.y/rSize.height));
	return true;
}

bool ApiCocos2dx::RemoveChildren(VectorNode& vNode,bool bClean){
	VectorNode::iterator itr;
	foreach(itr,vNode){
		Node* pNode = *itr;
		ASSERT_LOG_ERROR(pNode);

		pNode->removeAllChildrenWithCleanup(bClean);
	}

	return true;
}
bool ApiCocos2dx::RemoveChildren(VectorWidget& vNode,bool bClean){
	VectorWidget::iterator itr;
	foreach(itr,vNode){
		Node* pNode = *itr;
		ASSERT_LOG_ERROR(pNode);

		pNode->removeAllChildrenWithCleanup(bClean);
	}

	return true;
}

bool ApiCocos2dx::ChangeParentNode(VectorNode& vNode,const VectorNode& vParent,bool bKeepWorld,bool bCleanUp){
	if (vNode.empty())return true;
	if (vNode.size() > vParent.size())return false;
	for (uint nIndex =0;nIndex<vNode.size();++nIndex)
		ApiCocos2dx::ChangeParentNode(vNode[nIndex],vParent[nIndex],bKeepWorld,bCleanUp);

	return true;
}

bool ApiCocos2dx::ChangeParentNode( VectorNode& vNode,Node* pParent,bool bKeepWorld /*= true*/,bool bCleanUp /*= true*/ )
{
	if (!pParent)return false;

	if (vNode.empty())return true;
	
	for (uint nIndex =0;nIndex<vNode.size();++nIndex)
		ApiCocos2dx::ChangeParentNode(vNode[nIndex],pParent,bKeepWorld,bCleanUp);

	return true;
}

bool ApiCocos2dx::RemoveChildByTag(VectorNode& vNode,int nTag,bool bClean){
	if (vNode.empty())return true;
	VectorNode::const_iterator itr;
	foreach(itr,vNode){
		Node* pNode = *itr;
		if (pNode)
			pNode->removeChildByTag(nTag,bClean);
	}
	return true;
}

bool ApiCocos2dx::RemoveFromParentByTag( VectorNode& vNode,int nTag,bool bClean /*=true*/ )
{
	if (vNode.empty())return true;
	VectorNode::iterator itr;
	foreach(itr,vNode)
	{
		Node* pNode = *itr;
		if (pNode && pNode->getTag() == nTag){
			pNode->removeFromParentAndCleanup(bClean);
			vNode.erase(itr);
			return true;
		}
	}
	return false;
}

bool ApiCocos2dx::RemoveFromParentByTag( VectorWidget& vNode,int nTag,bool bClean /*=true*/ )
{
	if (vNode.empty())return true;
	VectorWidget::iterator itr;
	foreach(itr,vNode)
	{
		Widget* pNode = *itr;
		if (pNode && pNode->getTag() == nTag){
			pNode->removeFromParentAndCleanup(bClean);
			vNode.erase(itr);
			return true;
		}
	}
	return false;
}

int ApiCocos2dx::RemoveFromParentAllByTag( VectorNode& vNode,int nTag,bool bClean /*=true*/ )
{
	if (vNode.empty())return true;
	int nCounter=0;
	VectorNode::iterator itr = vNode.begin();
	while (itr != vNode.end())
	{
		Node* pNode = *itr;
		if (pNode && pNode->getTag() == nTag){
			pNode->removeFromParentAndCleanup(bClean);

			++nCounter;
			itr = ToolFrame::EraseByItr(vNode,itr);
			continue;
		}

		++itr;
	}

	return nCounter;
}

int ApiCocos2dx::RemoveFromParentAllByTag( VectorWidget& vNode,int nTag,bool bClean /*=true*/ )
{
	if (vNode.empty())return true;
	int nCounter=0;
	VectorWidget::iterator itr = vNode.begin();
	while (itr != vNode.end())
	{
		Widget* pNode = *itr;
		if (pNode && pNode->getTag() == nTag){
			pNode->removeFromParentAndCleanup(bClean);

			++nCounter;
			itr = ToolFrame::EraseByItr(vNode,itr);
			continue;
		}

		++itr;
	}

	return nCounter;
}

bool ApiCocos2dx::ActionsShake( Node* pNode,float fduration,int nStrength,int nFrequency,const Vec2& ptDirect )
{
	if (!pNode)return false;
	if (fduration<=0)return false;
	if (nStrength<=0)return false;
	if (nFrequency<=0)return false;

	if (pNode->getActionByTag(COCOS_ACTION_SHAKE))return false;//如果已经在抖动了 则 不再抖了

	float fFrequencySec = 1.f / nFrequency;//计算一次振动多少时间

	Sequence* pActionSequence = Sequence::create( MoveBy::create(fFrequencySec/2, ptDirect.getNormalized()*nStrength)
		,MoveBy::create(fFrequencySec/2, ptDirect.getNormalized()* -nStrength)
		,nullptr);

	if (!pActionSequence)return false;


	Action* pAction  = Repeat::create(pActionSequence,(unsigned int)(fduration/fFrequencySec+0.5f));
	if (!pAction)return false;

	pAction->setTag(COCOS_ACTION_SHAKE);

	pNode->stopAllActions();
	pNode->runAction(pAction);
	return true;
}

bool ApiCocos2dx::ActionsShake( Node* pNode,float fduration,int nStrength,int nFrequency/*=1*/ )
{
	return ActionsShake(pNode,fduration,nStrength,nFrequency,Vec2::ANCHOR_TOP_RIGHT);
}

bool ApiCocos2dx::StopAllAction( Node* pNode )
{
	if (!pNode)return false;

	pNode->stopAllActions();
	return true;
}

bool ApiCocos2dx::StopActionByTag( Node* pNode ,int nTag)
{
	if (!pNode)return false;

	pNode->stopActionByTag(nTag);
	return true;
}

bool ApiCocos2dx::StopAction( Node* pNode,Action* pAction )
{
	if (!pNode)return false;

	pNode->stopAction(pAction);
	return true;
}

int& ApiCocos2dx::GetTouchBlurDistance()
{
	static int g_nTouchFar = 30;
	return g_nTouchFar;
}

int& ApiCocos2dx::SetTouchBlurDistance( int nTouchFar )
{
	return GetTouchBlurDistance() = nTouchFar;
}

bool ApiCocos2dx::IsTouchBlur( Touch* touch )
{
	return IsTouchBlur(touch,GetTouchBlurDistance());
}

bool ApiCocos2dx::IsTouchBlur( Touch* touch,int nDistance )
{
	if (!touch)return false;
	return ApiCocos2dx::IsDistanceGreaterThan(touch->getStartLocation(),	touch->getLocation(),nDistance);
}

bool ApiCocos2dx::IsOutScreen( const Node* pNode )
{
	Point pos = pNode->getPosition();
	float fWidthMax = ApiCocos2dx::GetVisibleRect().size.width;
	float fHeightMax = ApiCocos2dx::GetVisibleRect().size.height;

	return pos.x < 0 || pos.x > fWidthMax || pos.y < 0 || pos.y > fHeightMax;
}

bool ApiCocos2dx::FixPositionInPanel( Node* pPanel )
{
	if (!pPanel)return false;
	Vector<Node*>& vChildren = pPanel->getChildren();
	if (vChildren.empty())return true;

	const Vec2& ptCenter = pPanel->getAnchorPointInPoints();

	Vector<Node*>::iterator itr;
	foreach(itr,vChildren){
		Node* pChild = *itr;
		ASSERT_LOG_ERROR(pChild);

		pChild->setPosition(ptCenter + pChild->getPosition());
	}
	return true;
}

bool ApiCocos2dx::SetColor( VectorNode& vNode,const Color3B& clr )
{
	VectorNode::iterator itr;
	foreach(itr,vNode)
	{
		Node* pNode = *itr;
		if (!pNode)return false;

		pNode->setColor(clr);
	}

	return true;
}

bool ApiCocos2dx::SetColor( Node* pNode,const Color3B& clr )
{
	if (!pNode)return false;
	
	pNode->setColor(clr);
	return true;
}

bool ApiCocos2dx::PlayArmature( Armature* pArmature, const std::string& sName, int nLoop /*= -1*/ )
{
	if (!pArmature)return false;
	if (sName.empty())return false;

	VectorString vName;
	vName.push_back(sName);

	return PlayArmature(pArmature,vName,nLoop);
}

bool ApiCocos2dx::PlayArmature( Armature* pArmature, const std::string& sName1, const std::string& sName2,int nLoop /*= -1*/ )
{
	if (!pArmature)return false;
	if (sName1.empty())return false;
	if (sName2.empty())return false;

	VectorString vName;
	vName.push_back(sName1);
	vName.push_back(sName2);

	return PlayArmature(pArmature,vName,nLoop);
}

bool ApiCocos2dx::PlayArmature( Armature* pArmature, const VectorString& vName, int nLoop /*= -1*/ )
{
	if (!pArmature)return false;
	if (vName.empty())return false;
	
	if (!pArmature)return false;
	if (vName.empty())return false;

	ArmatureAnimation* pAnimation = pArmature->getAnimation();
	if (!pAnimation)return false;

	VectorString vVaildName;

	VectorString::const_iterator itr;
	foreach(itr,vName){
		const std::string& sName = *itr;

		//检查是否符合要求
		if (sName.empty())
			continue;
		if (!IsHasMovementID(pArmature,sName)) 
			continue;
		if (IsEmptyMovement(pArmature,sName)) 
			continue;

		vVaildName.push_back(sName);
	}
	if (vVaildName.empty())return false;

	pArmature->stopActionByTag(COCOS_ACTION_ARMATURE_MONITOR);
	Action* pAction = CActionArmatureMonitor::create(nLoop, vVaildName);
	if (pAction)
		pArmature->runAction(pAction);

	if (vVaildName.size()>1){
		pAnimation->playWithNames(vVaildName,-1,true);
	}
	else
	{
		pAnimation->play(vVaildName[0],-1,nLoop);
	}

	
	return true;
}

Armature* ApiCocos2dx::PlayArmature( const std::string& sFileName, const std::string& sName, int nLoop /*= -1*/ )
{
	if (sFileName.empty())return nullptr;
	if (sName.empty())return nullptr;

	VectorString vName;
	vName.push_back(sName);

	return PlayArmature(sFileName,vName,nLoop);
}

Armature* ApiCocos2dx::PlayArmature( const std::string& sFileName, const std::string& sName1, const std::string& sName2,int nLoop /*= -1*/ )
{
	if (sFileName.empty())return nullptr;
	if (sName1.empty())return nullptr;
	if (sName2.empty())return nullptr;

	VectorString vName;
	vName.push_back(sName1);
	vName.push_back(sName2);

	return PlayArmature(sFileName,vName,nLoop);
}

Armature* ApiCocos2dx::PlayArmature( const std::string& sFileName, const VectorString& vName, int nLoop /*= -1*/ )
{
	if (sFileName.empty())return nullptr;
	if (vName.empty())return nullptr;

	if (!CacheArmatureFile(sFileName))return nullptr;

	std::string sArmature = ToolFrame::PickFileNameWithOutExt(sFileName);
	Armature* pArmature = CreateArmature(sArmature);
	if (!pArmature)return nullptr;

	if (!PlayArmature(pArmature,vName,nLoop))return nullptr;

	return pArmature;
}

Armature* ApiCocos2dx::PlayArmature( const std::string& sFileName, int nLoop /*= -1*/ )
{
	if (sFileName.empty())return nullptr;

	if (!CacheArmatureFile(sFileName))return nullptr;

	std::string sArmature = ToolFrame::PickFileNameWithOutExt(sFileName);
	Armature* pArmature = CreateArmature(sArmature);
	if (!pArmature)return nullptr;

	if (!PlayArmature(pArmature,GetMovementName(pArmature),nLoop))return nullptr;

	return pArmature;
}

bool ApiCocos2dx::PlayArmature( Armature* pArmature, int nLoop /*= -1*/ )
{
	return PlayArmature(pArmature,GetMovementName(pArmature),nLoop);
}

Armature* ApiCocos2dx::PlayArmature( const Point& ptPostion,const std::string& sFileName, int nLoop /*= -1*/ )
{
	Armature* pArmature = PlayArmature(sFileName,nLoop);
	if (!pArmature)return nullptr;

	ApiCocos2dx::SetPostion(pArmature,ptPostion);
	return pArmature;
}

Armature* ApiCocos2dx::PlayArmature( const Point& ptPostion,const std::string& sFileName, const std::string& sName, int nLoop /*= -1*/ )
{
	if (sFileName.empty())return nullptr;
	if (sName.empty())return nullptr;

	VectorString vName;
	vName.push_back(sName);

	return PlayArmature(ptPostion,sFileName,vName,nLoop);
}

Armature* ApiCocos2dx::PlayArmature( const Point& ptPostion,const std::string& sFileName, const std::string& sName1, const std::string& sName2,int nLoop /*= -1*/ )
{
	if (sFileName.empty())return nullptr;
	if (sName1.empty())return nullptr;
	if (sName2.empty())return nullptr;

	VectorString vName;
	vName.push_back(sName1);
	vName.push_back(sName2);

	return PlayArmature(ptPostion,sFileName,vName,nLoop);
}

Armature* ApiCocos2dx::PlayArmature( const Point& ptPostion,const std::string& sFileName, const VectorString& vName, int nLoop /*= -1*/ )
{
	Armature* pArmature = PlayArmature(sFileName,vName,nLoop);
	if (!pArmature)return nullptr;
	
	ApiCocos2dx::SetPostion(pArmature,ptPostion);
	return pArmature;
}

Node* ApiCocos2dx::FindNodeByTag( const VectorNode& vNode,int nTag )
{
	VectorNode::const_iterator itr;
	foreach(itr,vNode){
		Node* pNode = *itr;
		if (pNode && nTag == pNode->getTag())
			return pNode;
	}

	return nullptr;
}

Widget* ApiCocos2dx::FindNodeByTag( const VectorWidget& vNode,int nTag )
{
	VectorWidget::const_iterator itr;
	foreach(itr,vNode){
		Widget* pNode = *itr;
		if (pNode && nTag == pNode->getTag())
			return pNode;
	}

	return nullptr;
}

Action* ApiCocos2dx::FindActionByTag(Node* pNode,int nTag)
{
	if (!pNode)return nullptr;
	return pNode->getActionByTag(nTag);
}

int ApiCocos2dx::GetActionsCount( Node* pNode )
{
	if (!pNode)return 0;

	return pNode->getNumberOfRunningActions();
}

bool ApiCocos2dx::SetPostionOffset( Node* pTarget,const Point& ptPostion )
{
	if (!pTarget)return false;
	
	pTarget->setPosition(pTarget->getPosition() + ptPostion);
	return true;
}

int ApiCocos2dx::CalLines(const std::string& sString,int nWidth,int nFontSize){
	int nLines = 0;

	std::u16string utf16String;
	if (!StringUtils::UTF8ToUTF16(sString, utf16String))return nLines;

	int nLineWidth =0;//当前行长度
	size_t stringLen = utf16String.length();
	for (size_t nIndex = 0; nIndex < stringLen-1; ++nIndex)
	{
		//如果遇到换行符
		if (utf16String[nIndex] == '\n')
		{
			++nLines;
			nLineWidth = 0;
			continue;
		}

		nLineWidth += nFontSize;

		//如果超过行数
		if (nLineWidth > nWidth)
		{
			++nLines;
			nLineWidth = nFontSize;
			continue;
		}

		//如果刚好
		if (nLineWidth == nWidth)
		{
			++nLines;
			nLineWidth =0;
			continue;
		}
	}

	//不满一行
	if (nLineWidth>0)
		++nLines;

	return nLines;
}

bool ApiCocos2dx::AutoHeight( Text* pNode,int nSpaceHeight,int nSpaceWidth )
{
	if (!pNode)return false;

	if (pNode->getStringLength()<=0)return false;

	int nFontSize = pNode->getFontSize();

	//求出每行可以容纳字数
	int nWidth = pNode->getSize().width;

	int nLines = CalLines(pNode->getString(),nWidth,nFontSize + nSpaceWidth);
	int nHeight = nLines * (nFontSize + nSpaceHeight);

	return ApiCocos2dx::SetContentSize(pNode,Size(nWidth,nHeight));
}

bool ApiCocos2dx::SpineSkipBy( SkeletonAnimation* pAnimation,float fTimeNext )
{
	if (!pAnimation)return false;

	pAnimation->update(fTimeNext);
	return true;
}

bool ApiCocos2dx::SetAutoPurgeCache( bool bAuto )
{
	g_bAutoPurgeCache = bAuto;
	return true;
}

bool ApiCocos2dx::IsAutoPurgeCache()
{
	return g_bAutoPurgeCache;
}

bool ApiCocos2dx::Merge(VectorNode& vNode,const VectorSpineAnimation& vSrc){
	VectorSpineAnimation::const_iterator itr;
	foreach(itr,vSrc){
		vNode.push_back(*itr);
	}

	return true;
}

bool ApiCocos2dx::Merge(VectorNode& vNode,Node* pNode){
	vNode.push_back(pNode);
	return true;
}

bool ApiCocos2dx::SetTagWhithIndex( const VectorNode& vNode,int nIndexBegin /*=0*/ )
{
	if (vNode.empty())return true;

	VectorNode::const_iterator itr;
	foreach(itr,vNode){
		SetTag(*itr,nIndexBegin++);
	}

	return true;
}

bool ApiCocos2dx::SetTagWhithIndex( const VectorWidget& vNode,int nIndexBegin /*=0*/ )
{
	if (vNode.empty())return true;

	VectorWidget::const_iterator itr;
	foreach(itr,vNode){
		SetTag(*itr,nIndexBegin++);
	}

	return true;
}

bool ApiCocos2dx::UpdateNode( Node* pNode,float fDelta /*= 0.f*/ )
{
	if (!pNode)return false;
	pNode->update(fDelta);
	return true;
}

bool ApiCocos2dx::VisitNode( Node* pNode )
{
	if (!pNode)return false;
	pNode->visit();
	return true;
}

bool ApiCocos2dx::UpdateVisitNode( Node* pNode,float fDelta /*= 0.f*/ )
{
	if (!pNode)return false;
	pNode->update(fDelta);
	pNode->visit();
	return true;
}

const Point ApiCocos2dx::GetVisibleRectLeftTop()
{
	return ccp(0, ApiCocos2dx::GetVisibleRect().size.height);
}

const Point ApiCocos2dx::GetVisibleRectRightTop()
{
	return ApiCocos2dx::GetVisibleRect().size;
}

const Point ApiCocos2dx::GetVisibleRectLeftDown()
{
	return ccp(0,0);
}

const Point ApiCocos2dx::GetVisibleRectRightDown()
{
	return ccp(ApiCocos2dx::GetVisibleRect().size.width, 0);
}

bool ApiCocos2dx::SetAnchorPoint( Node* pNode,const Vec2& pt )
{
	if (!pNode)return false;
	pNode->setAnchorPoint(pt);
	return true;
}

bool ApiCocos2dx::SetAnchorPoint( Node* pNode,int x,int y )
{
	if (!pNode)return false;
	return SetAnchorPoint(pNode,ccp(x,y));
}

bool ApiCocos2dx::FixAnchorPoint( Node* pNode )
{
	if (!pNode)return false;

	Vec2 ptOld = pNode->getAnchorPoint();
	Vec2 ptNew = Vec2::ZERO;
	if (ptOld.equals(Vec2::ZERO))
		ptNew = ccp(1,1);
	SetAnchorPoint(pNode,ptNew);
	return SetAnchorPoint(pNode,ptOld);
}

const Vec2& ApiCocos2dx::GetAnchorPoint( Node* pNode )
{
	return pNode->getAnchorPoint();
}

bool ApiCocos2dx::ReleaseNextFrame( Ref* ref )
{
	if (!ref)return false;

	ref->retain();
	PoolManager::getInstance()->getCurrentPool()->addObject(ref);
	return true;
}

bool ApiCocos2dx::Retain( Ref* ref )
{
	if (!ref)return false;

	ref->retain();
	return true;
}

bool ApiCocos2dx::Release( Ref* ref )
{
	if (!ref)return false;

	ref->release();
	return true;
}

Scene* ApiCocos2dx::GetRunningSceneNode()
{
	return Director::getInstance()->getRunningScene();
}

bool ApiCocos2dx::IsIntersects( const Node* pNode1,const Node* pNode2 )
{
	if (!pNode1)return false;
	if (!pNode2)return false;

	return pNode1->getBoundingBox().intersectsRect(pNode2->getBoundingBox());
}

bool ApiCocos2dx::SetPostionZero( Node* pTarget )
{
	if (!pTarget)return false;

	pTarget->setPosition(0,0);
	return true;
}

bool ApiCocos2dx::InitTemplate(Node* pNode, bool bIgnoreContentAdaptWithSize/*=true*/)
{
	if (!pNode)return false;

	pNode->setVisible(false);
	pNode->setPosition(0, 0);
	return true;
}

bool ApiCocos2dx::SetIgnoreContentAdaptWithSize(Node* pNode, bool bIgnoreContentAdaptWithSize /*= true*/, bool bChildren /*= true*/)
{
	if (!pNode)return false;

	Widget* pWidget = dynamic_cast<Widget*>(pNode);
	if (pWidget)
		pWidget->ignoreContentAdaptWithSize(bIgnoreContentAdaptWithSize);

	if (bChildren)
	{
		Vector<Node*>::const_iterator itr;
		foreach(itr, pNode->getChildren()) {
			SetIgnoreContentAdaptWithSize(*itr, bIgnoreContentAdaptWithSize, bChildren);
		}
	}

	return true;
}

bool ApiCocos2dx::ReplaceNode(Node* pNode, Node* pNodeTarget)
{
	if (!pNode)return false;
	if (!pNodeTarget)return false;
	if (!pNodeTarget->getParent())return false;

	pNode->setLocalZOrder(pNodeTarget->getLocalZOrder());
	pNode->setPosition(pNodeTarget->getPosition());
	pNodeTarget->getParent()->addChild(pNode);

	ApiCocos2dx::SetWorldBoundingBox(pNode,ApiCocos2dx::GetWorldBoundingBox(pNodeTarget));

	pNodeTarget->removeFromParentAndCleanup(true);

	return true;
}

bool ApiCocos2dx::ReplaceNode( Node* pNode,Node* pNodeTargetRoot,const std::string& sName)
{
	if (!pNode)return false;
	if (!pNodeTargetRoot)return false;

	return ReplaceNode(pNode,ApiCocos2dx::FindNode(pNodeTargetRoot,sName));
}

bool ApiCocos2dx::PositionNode( Node* pNode,Node* pNodePosition )
{
	if (!pNode)return false;
	if (!pNodePosition)return false;
	if (!pNodePosition->getParent())return false;

	pNode->setLocalZOrder(pNodePosition->getLocalZOrder());
	pNode->setPosition(pNodePosition->getPosition());
	pNodePosition->getParent()->addChild(pNode);

	return true;
}

bool ApiCocos2dx::PositionNode( Node* pNode,Node* pNodePositionRoot,const std::string& sName )
{
	if (!pNode)return false;
	if (!pNodePositionRoot)return false;

	return ReplaceNode(pNode,ApiCocos2dx::FindNode(pNodePositionRoot,sName));
}

Node* ApiCocos2dx::FindNode(const Node* pNode,const std::string& sName )
{
	if (!pNode)return nullptr;
	
	if (pNode->getName() == sName)return (Node*)(pNode);

	Vector<Node*>::const_iterator itr;
	foreach(itr,pNode->getChildren()){
		Node* pFind = FindNode(*itr,sName);
		if (pFind)
			return pFind;
	}
	
	return nullptr;
}

bool ApiCocos2dx::SetFlippedX( Node* pNode,bool bFlipped )
{
	Widget* pWidget = dynamic_cast<Widget*>(pNode);
	if (!pWidget)return false;

	pWidget->setFlippedX(bFlipped);
	return true;
}

bool ApiCocos2dx::SetFlippedY( Node* pNode,bool bFlipped )
{
	Widget* pWidget = dynamic_cast<Widget*>(pNode);
	if (!pWidget)return false;

	pWidget->setFlippedY(bFlipped);
	return true;
}

bool ApiCocos2dx::IsFlippedX( Node* pNode )
{
	Widget* pWidget = dynamic_cast<Widget*>(pNode);
	if (!pWidget)return false;

	return pWidget->isFlippedX();
}

bool ApiCocos2dx::IsFlippedY( Node* pNode )
{
	Widget* pWidget = dynamic_cast<Widget*>(pNode);
	if (!pWidget)return false;

	return pWidget->isFlippedY();
}

int ApiCocos2dx::PlayAudio(const std::string& sPath, bool bLoop /*= true*/, float fVolume /*= 1.0f*/)
{
	if (sPath.empty())return INVALID_ID;

	return experimental::AudioEngine::play2d(sPath, bLoop, fVolume);
}

bool ApiCocos2dx::SetAudioLoop(int nAudioID, bool bLoop)
{
	if (experimental::AudioEngine::INVALID_AUDIO_ID == nAudioID)
		return false;

	experimental::AudioEngine::setLoop(nAudioID, bLoop);
	return true;
}

bool ApiCocos2dx::SetAudioVolume(int nAudioID, float fVolume)
{
	if (experimental::AudioEngine::INVALID_AUDIO_ID == nAudioID)
		return false;

	experimental::AudioEngine::setVolume(nAudioID, fVolume);
	return true;
}

bool ApiCocos2dx::SetAudioPause(int nAudioID, bool bPause /*= true*/)
{
	if (experimental::AudioEngine::INVALID_AUDIO_ID == nAudioID)
		return false;

	bPause ? experimental::AudioEngine::pause(nAudioID): experimental::AudioEngine::resume(nAudioID);
	return true;
}

bool ApiCocos2dx::SetAudioStop(int nAudioID)
{
	if (experimental::AudioEngine::INVALID_AUDIO_ID == nAudioID)
		return false;

	experimental::AudioEngine::stop(nAudioID);
	return true;
}

bool ApiCocos2dx::SetAudioCurrentTime(int nAudioID, float fSecond)
{
	if (experimental::AudioEngine::INVALID_AUDIO_ID == nAudioID)
		return false;

	return experimental::AudioEngine::setCurrentTime(nAudioID, fSecond);
}

bool ApiCocos2dx::SetAudioFinishCallback(int nAudioID, const std::function<void(int, const std::string&)>& callback)
{
	if (experimental::AudioEngine::INVALID_AUDIO_ID == nAudioID)
		return false;

	experimental::AudioEngine::setFinishCallback(nAudioID, callback);
	return true;
}

bool ApiCocos2dx::SetAudioMute(int nAudioID, bool bMute /*= true*/)
{
	if (experimental::AudioEngine::INVALID_AUDIO_ID == nAudioID)
		return false;

	experimental::AudioEngine::mute(nAudioID, bMute);
	return true;
}

bool ApiCocos2dx::IsAudioLoop(int nAudioID)
{
	if (experimental::AudioEngine::INVALID_AUDIO_ID == nAudioID)
		return false;

	return experimental::AudioEngine::isLoop(nAudioID);
}

float ApiCocos2dx::GetAudioVolume(int nAudioID)
{
	if (experimental::AudioEngine::INVALID_AUDIO_ID == nAudioID)
		return 0.f;

	return experimental::AudioEngine::getVolume(nAudioID);
}

float ApiCocos2dx::GetAudioCurrentTime(int nAudioID)
{
	if (experimental::AudioEngine::INVALID_AUDIO_ID == nAudioID)
		return 0.f;

	return experimental::AudioEngine::getCurrentTime(nAudioID);
}

float ApiCocos2dx::GetAudioDuration(int nAudioID)
{
	if (experimental::AudioEngine::INVALID_AUDIO_ID == nAudioID)
		return 0.f;

	return experimental::AudioEngine::getDuration(nAudioID);
}

int ApiCocos2dx::GetAudioState(int nAudioID)
{
	return (int)experimental::AudioEngine::getState(nAudioID);
}

bool ApiCocos2dx::SetAudioPauseAll(bool bPause /*= true*/)
{
	bPause ? experimental::AudioEngine::pauseAll() : experimental::AudioEngine::resumeAll();
	return true;
}

bool ApiCocos2dx::SetAudioStopAll()
{
	experimental::AudioEngine::stopAll();
	return true;
}

bool ApiCocos2dx::AudioUncache(const std::string& sPath)
{
	if (sPath.empty())return false;

	experimental::AudioEngine::uncache(sPath);
	return true;
}

bool ApiCocos2dx::AudioUncacheAll()
{
	experimental::AudioEngine::uncacheAll();
	return true;
}

int ApiCocos2dx::PlaySound(const std::string& sPath, bool bLoop /*= false*/, float fVolume /*= 1.0f*/)
{
	int nAudioID = PlayAudio(sPath, bLoop, fVolume);
	if (g_bSoundMute)
		SetAudioMute(nAudioID);

	return nAudioID;
}

int ApiCocos2dx::PlayMusic(const std::string& sPath, bool bLoop /*= true*/, float fVolume /*= 1.0f*/)
{
	SetAudioStop(g_nAudioMusic);
	g_nAudioMusic = PlayAudio(sPath, bLoop);
	if (g_bMusicMute || g_bSoundMute)
		SetAudioMute(g_nAudioMusic);

	return g_nAudioMusic;
}	

bool ApiCocos2dx::StopSound(int nAudioID)
{
	return SetAudioStop(nAudioID);
}

bool ApiCocos2dx::StopMusic()
{
	return SetAudioStop(g_nAudioMusic);
}

bool ApiCocos2dx::SetSoundMute(bool bMute)
{
	g_bSoundMute = bMute;

	const experimental::AudioEngine::MapAudioInfo& vAudioInfo = experimental::AudioEngine::GetMapAudioInfo();
	experimental::AudioEngine::MapAudioInfo::const_iterator itr;
	foreach(itr, vAudioInfo) {
		SetAudioMute(itr->first, g_bMusicMute || g_bSoundMute);
	}

	return true;
}

bool ApiCocos2dx::SetMusicMute(bool bMute)
{
	g_bMusicMute = bMute;
	return SetAudioMute(g_nAudioMusic, g_bMusicMute || g_bSoundMute);
}

bool ApiCocos2dx::IsSoundMute()
{
	return g_bSoundMute;
}

bool ApiCocos2dx::IsMusicMute()
{
	return g_bMusicMute;
}

int ApiCocos2dx::GetMusicAudioID()
{
	return g_nAudioMusic;
}

#endif //MACRO_LIB_COCOS2D
