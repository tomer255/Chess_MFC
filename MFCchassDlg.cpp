
// MFCchassDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCchass.h"
#include "MFCchassDlg.h"
#include "afxdialogex.h"
#include "board.h"
#include "Helper.h"
#include "PieceSelect.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCchassDlg dialog

Board board;
COORD from;
COORD to;

CMFCchassDlg::CMFCchassDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCHASS_DIALOG, pParent)
	, turnDS(_T("לבן"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	isPressed = false;
}

void CMFCchassDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, turnDS);
}

BEGIN_MESSAGE_MAP(CMFCchassDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCchassDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCchassDlg::OnBnClickedButton2)
	ON_EN_CHANGE(IDC_EDIT1, &CMFCchassDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCchassDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCchassDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CMFCchassDlg message handlers

BOOL CMFCchassDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control

}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.


double bloks;
void CMFCchassDlg::OnPaint()
{
	double bloks_size = 0;
	double piece_size = 0;
	double piece_sener = 0;
	GetDesktopResolution(bloks, bloks_size, piece_size, piece_sener);
	CPaintDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	CFont font;
	//font.CreatePointFont(BLOKS*BLOKS_SIZE, _T("MS Gothic"));
	font.CreatePointFont(bloks*bloks_size, _T("MS Gothic"));
	CFont *oldFont = dc.SelectObject(&font);
	dc.SetBkMode(TRANSPARENT);
	CString string;
	
	string = _T("■");

	for (int j = 0; j < 8; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			//Sleep(100);
			dc.SetTextColor((i + j) % 2 ? RGB(130, 70, 0) : RGB(220, 169, 40));
			//dc.SetTextColor((i + j) % 2 ? RGB(255, 255, 255) : RGB(0, 0, 0));
			dc.DrawText(string, &rect,DT_VCENTER/* DT_CALCRECT*/);
			//rect.OffsetRect(BLOKS, 0);
			rect.OffsetRect(bloks, 0);

		}
		rect.OffsetRect(-8* bloks, bloks);
	}
	GetClientRect(&rect);
	rect.OffsetRect(bloks / piece_sener, bloks / piece_sener);
	font.DeleteObject();
	font.CreatePointFont(bloks*piece_size, _T("MS Gothic"));
	dc.SelectObject(&font);
	for (int j = 0; j < 8; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			COORD loc = { (SHORT)i,(SHORT)j };
			//board[loc] != nullptr ? Sleep(100) : Sleep(0);
			wchar_t s = board[loc] != nullptr ? board[loc]->getIcon() + 6 : L' ';
			string = s;
			int p = board[loc] != nullptr ? board[loc]->getPlayer() : 0;
			dc.SetTextColor(p ? RGB(255, 255, 255) : RGB(0, 0, 0));
			dc.DrawText(string, &rect, DT_VCENTER);
			string = board[loc] != nullptr ? board[loc]->getIcon() : L' ';
			dc.SetTextColor(p ? RGB(0, 0, 0) : RGB(255, 255, 255));
			dc.DrawText(string, &rect, DT_VCENTER);
			rect.OffsetRect(bloks, 0);
			//---------
			//string = board[loc] != nullptr ? board[loc]->getIcon() : L' ';
			//int p = board[loc] != nullptr ? board[loc]->getPlayer() : 0;
			//dc.SetTextColor(p ? RGB(255, 255, 255) : RGB(0, 0, 0));
			//dc.DrawText(string, &rect, DT_VCENTER);
			//rect.OffsetRect(BLOKS, 0);
		}
		rect.OffsetRect(-8 * bloks, bloks);
	}

	dc.SelectObject(oldFont);
}


// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCchassDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCchassDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	startP = point;
	isPressed = true;
	CDialog::OnLButtonDown(nFlags, point);
	from = ConvLoc({ (SHORT)startP.x,(SHORT)startP.y },bloks );

}
void CMFCchassDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (isPressed)
	{
		endP = point;
		isPressed = false;
	}
	CDialog::OnLButtonUp(nFlags, point);
	to = ConvLoc({ (SHORT)endP.x,(SHORT)endP.y },bloks );
	if ((board[from] != nullptr && board[from]->getPlayer() == board.getTurn()))
	{
		if (validLoc(to) && validLoc(from)) {
			if (board.MovePiece(from, to)) {
				if (((to.Y == 0 && board.getTurn() == 1)||(to.Y == 7 && board.getTurn() == 0)) && board[to]->getIcon() == IPawn)
				{
					PieceSelect dlg;
					dlg.DoModal();
					board.ChangePiece(to, dlg.Select);
				}
				board.getTurn() = (board.getTurn() + 1) % 2;
				Invalidate();
				turnDS = board.getTurn() ? L"לבן" : L"שחור";
				UpdateData(false);
			}
			from = { -1,-1 };
			to = { -1,-1 };
		}
	}
}
void CMFCchassDlg::OnMouseMove(UINT nFlags, CPoint point)
{

}

void CMFCchassDlg::OnBnClickedButton1()
{
	CFile file;
	file.Open(L"boardInfo.chs", CFile::modeCreate | CFile::modeWrite);
	CArchive ar(&file, CArchive::store);
	board.Serialize(ar);
	ar.Close();
}


void CMFCchassDlg::OnBnClickedButton2()
{
	CFile file;
	file.Open(L"boardInfo.chs", CFile::modeRead);
	CArchive ar(&file, CArchive::load);
	board.Serialize(ar);
	ar.Close();
	file.Close();
	Invalidate();
	turnDS = board.getTurn() ? L"לבן" : L"שחור";
	UpdateData(false);
}


void CMFCchassDlg::OnEnChangeEdit1()
{
}


void CMFCchassDlg::OnBnClickedButton3()
{
	board.CleanBoard();
	board.setNewBoard();
	board.getTurn() = 1;
	turnDS = L"לבן";
	Invalidate();
	UpdateData(false);
}


void CMFCchassDlg::OnBnClickedButton5()
{
	switch (MessageBox(L"האם לשמור לפני יציאה לצאת?", L"יצאה", MB_YESNOCANCEL | MB_ICONQUESTION))
	{
	case IDYES: this->OnBnClickedButton1();
	case IDNO: this->EndDialog(0);
	default:
		break;
	}
}
