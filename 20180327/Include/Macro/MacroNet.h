#pragma once
#include "Macro.h"
#include "MacroDefineEx.h"
#include "MLoger.h"

//����������
//��ע:�������������ʧ�� �� ��������ʧ�ܡ�
//������ ��������ʧ�� �Ǵ��� ���Ӳ�û��ִ�� �������쳣��ʧ���ˡ���ͨ���Ǵ�������BUG
//����ʧ�� �Ǵ��� ִ�й�����֮�� ��Ϊ ������� ���ֲ��ɿ����� ��ʧ���ˡ���ͨ���ǲ��ɿ���,�Ǵ��뼶�����⣬���� ���߸���û�Ӻ�
enum ENetErrCode{
	NET_ERRCODE_INVAILD=0,
	NET_ERRCODE_ACTIVE,				//�����Ͽ�
	NET_ERRCODE_CONNECT,			//����ʧ��
	NET_ERRCODE_RECV,				//����ʧ��
	NET_ERRCODE_SEND,				//����ʧ��
	NET_ERRCODE_REQ_RECV,			//�������ʧ��
	NET_ERRCODE_REQ_SEND,			//������ʧ��
	NET_ERRCODE_REQ_CLOSE,			//����ر�
	NET_ERRCODE_REQ_SEND_BUFF_FULL,	//���ͻ�������
	NET_ERRCODE_REQ_RECV_BUFF_FULL,	//���ջ�������
	NET_ERRCODE_LENGTH_LIMIT,		//���ȳ�������
	NET_ERRCODE_VAILD_PACK,			//��Ч��
	NET_ERRCODE_RECVED_ERR,			//�ϲ��հ������ش���
	NET_ERRCODE_HEART_TIMEOUT,		//(�ϲ��߼�)������ʱ
	NET_ERRCODE_USER_RECONNECT_FAILD,//(�ϲ��߼�)�Զ�����ʧ��
	NET_ERRCODE_REFUSED,			//(�ϲ��߼�)�������ܾ�����

	NET_ERRCODE_MAX,
};

//��������
enum ELinkType{
	LINK_TYPE_INVAILD = 0,
	LINK_TYPE_NET_TCP,	//������Tcp��ʽ����
	LINK_TYPE_NET_UDP,	//������Udp��ʽ����
	LINK_TYPE_MEM,		//�ڴ�
	LINK_TYPE_BLUETOOTH,//����
	LINK_TYPE_MAX,
};

