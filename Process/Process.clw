; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CProcessDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Process.h"

ClassCount=3
Class1=CProcessApp
Class2=CProcessDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_PROCESS_DIALOG

[CLS:CProcessApp]
Type=0
HeaderFile=Process.h
ImplementationFile=Process.cpp
Filter=N

[CLS:CProcessDlg]
Type=0
HeaderFile=ProcessDlg.h
ImplementationFile=ProcessDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_BUTTON_HAVE_SIGNAL

[CLS:CAboutDlg]
Type=0
HeaderFile=ProcessDlg.h
ImplementationFile=ProcessDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_PROCESS_DIALOG]
Type=1
Class=CProcessDlg
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_BUTTON_CREATE_EVENT_OBJECT,button,1342242816
Control4=IDC_BUTTON_CREATE_CHILD_PROCESS,button,1342242816
Control5=IDC_BUTTON_HAVE_SIGNAL,button,1342242816
Control6=IDC_BUTTON_HAVE_NOT_SIGNAL,button,1342242816
Control7=IDC_BUTTON_EXIT,button,1342242816

