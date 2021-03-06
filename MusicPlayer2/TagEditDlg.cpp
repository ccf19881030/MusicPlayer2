// TagEditDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MusicPlayer2.h"
#include "TagEditDlg.h"
#include "afxdialogex.h"


// CTagEditDlg 对话框

IMPLEMENT_DYNAMIC(CTagEditDlg, CDialog)

CTagEditDlg::CTagEditDlg(vector<ItemInfo>& file_list, int index, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_TAG_EDIT_DIALOG, pParent), m_file_list{ file_list }, m_index{ index }
{

}

CTagEditDlg::~CTagEditDlg()
{
}

void CTagEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GENRE_COMBO, m_genre_combo);
}

void CTagEditDlg::ShowInfo()
{
	if (m_index < 0 || m_index >= static_cast<int>(m_file_list.size()))
		return;
	const ItemInfo& item{ m_file_list[m_index] };
	SetDlgItemText(IDC_PATH_EDIT, item.file_path.c_str());
	SetDlgItemText(IDC_TITEL_EDIT, item.song_info.title.c_str());
	SetDlgItemText(IDC_ARTIST_EDIT, item.song_info.artist.c_str());
	SetDlgItemText(IDC_ALBUM_EDIT, item.song_info.album.c_str());
	SetDlgItemText(IDC_TRACK_EDIT, CAudioCommon::TrackToString(item.song_info.track));
	SetDlgItemText(IDC_GENRE_COMBO, item.song_info.genre.c_str());
	SetDlgItemText(IDC_COMMENT_EDIT, item.song_info.comment.c_str());
	CString info_str;
	info_str.Format(_T("%d/%d"), m_index + 1, m_file_list.size());
	SetDlgItemText(IDC_ITEM_STATIC, info_str);
}


BEGIN_MESSAGE_MAP(CTagEditDlg, CDialog)
	ON_BN_CLICKED(IDC_PREVIOUS_BUTTON, &CTagEditDlg::OnBnClickedPreviousButton)
	ON_BN_CLICKED(IDC_NEXT_BUTTON, &CTagEditDlg::OnBnClickedNextButton)
	ON_BN_CLICKED(IDC_SAVE_BUTTON, &CTagEditDlg::OnBnClickedSaveButton)
END_MESSAGE_MAP()


// CTagEditDlg 消息处理程序


BOOL CTagEditDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	//初始化流派列表
	for (int i{}; i < GENRE_MAX; i++)
	{
		m_genre_combo.AddString(GENRE_TABLE[i]);
	}
	CRect rect;
	m_genre_combo.SetMinVisibleItems(15);		//设置下拉列表的高度

	ShowInfo();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CTagEditDlg::OnBnClickedPreviousButton()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_file_list.size() <= 1)
		return;
	m_index--;
	if (m_index < 0) m_index = m_file_list.size() - 1;
	if (m_index < 0) m_index = 0;
	ShowInfo();
}


void CTagEditDlg::OnBnClickedNextButton()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_file_list.size() <= 1)
		return;
	m_index++;
	if (m_index >= static_cast<int>(m_file_list.size())) m_index = 0;
	ShowInfo();
}


void CTagEditDlg::OnBnClickedSaveButton()
{
	// TODO: 在此添加控件通知处理程序代码
	ItemInfo& item{ m_file_list[m_index] };
	CString temp;
	GetDlgItemText(IDC_TITEL_EDIT, temp);
	item.song_info.title = temp;
	GetDlgItemText(IDC_ARTIST_EDIT, temp);
	item.song_info.artist = temp;
	GetDlgItemText(IDC_ALBUM_EDIT, temp);
	item.song_info.album = temp;
	GetDlgItemText(IDC_TRACK_EDIT, temp);
	item.song_info.track = _ttoi(temp);
	GetDlgItemText(IDC_GENRE_COMBO, temp);
	item.song_info.genre = temp;
	GetDlgItemText(IDC_COMMENT_EDIT, temp);
	item.song_info.comment = temp;
}
