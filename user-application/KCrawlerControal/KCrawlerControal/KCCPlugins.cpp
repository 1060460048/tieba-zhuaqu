// KCCPlugins.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KCrawlerControal.h"
#include "KCCPlugins.h"
#include "afxdialogex.h"


// KCCPlugins �Ի���

IMPLEMENT_DYNAMIC(KCCPlugins, CDialogEx)

KCCPlugins::KCCPlugins(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_USE_PLUGINS, pParent)
{

}

KCCPlugins::~KCCPlugins()
{
	delete[] pluginlist;
}

void KCCPlugins::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO2, m_pluginslist);
}

void KCCPlugins::loadPlugins()
{
	CStdioFile cfg;
	cfg.Open(PATH_PLUGINS_INDEX_FILE, CFile::modeRead);
	CString line = _T("");
	int pluginscount = 0;
	//�������
	while (cfg.ReadString(line))
	{
		//����ɣ�KCCPLUGINS=�����=������=����ļ���
		if (line.Find(_T("KCCPLUGINS")) >= 0)
		{
			pluginscount++;
		}
		line = _T("");
	}
	if (pluginscount < 1)
	{
		MessageBox(_T("δ�ҵ��κο��ò����������޷������κ����ݷ���������"), _T("����"), MB_ICONERROR | MB_OK);
		cfg.Close();
		return;
	}
	cfg.SeekToBegin();
	pluginlist = new Plugin[pluginscount];
	//ѭ�����ز��
	int i = 0;
	while (cfg.ReadString(line))
	{
		//��������ṹ��ÿһ�д���һ�����
		//����ɣ�KCCPLUGINS=�����=������=����ļ���
		if (line.Find(_T("KCCPLUGINS")) >= 0)
		{
			line = line.Right(line.GetLength() - line.Find(_T("=")) - 1);
			CString name = line.Left(line.Find(_T("=")));
			line = line.Right(line.GetLength() - line.Find(_T("=")) - 1);
			CString descri = line.Left(line.Find(_T("=")));
			line = line.Right(line.GetLength() - line.Find(_T("=")) - 1);
			CString exefilename = line;
			if (exefilename.GetLength() < 3 || name.GetLength() == 0)
			{
				continue;
			}
			CString liststr = name + _T("->") + descri;
			m_pluginslist.AddString(liststr);
			//��������Ϣ��һ�����з���ִ��
			pluginlist[i].name = name;
			pluginlist[i].descri = descri;
			pluginlist[i].exefilename = exefilename;
			i++;
		}
		line = _T("");
	}
	cfg.Close();
}


BEGIN_MESSAGE_MAP(KCCPlugins, CDialogEx)
END_MESSAGE_MAP()


// KCCPlugins ��Ϣ�������


BOOL KCCPlugins::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	loadPlugins();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
