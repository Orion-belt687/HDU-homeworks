#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <graphics.h>
#include <windows.h>
#include <tchar.h>  
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
time_t startTime, endTime;

void playSoundEffect(const TCHAR* filename) {
    PlaySound(filename, NULL, SND_FILENAME | SND_ASYNC);
}//y��Ч
int show_menu() {
   cleardevice();  
   settextstyle(40, 0, _T("KaiTi"));
   settextcolor(BROWN);  
   outtextxy(200,220, _T("              ===ƴͼ��Ϸ===\n"));
   outtextxy(200,300, _T("��ѡ��1. ��ʼ��Ϸ  2. ��Ϸ˵��  ESC. �˳�"));
   // ���ư�ť
   setfillcolor(LIGHTBLUE);
   fillrectangle(100, 450, 300, 530);
   fillrectangle(500, 450, 700, 530);
   fillrectangle(900, 450, 1100, 530);
   settextcolor(WHITE);
   setbkcolor(LIGHTBLUE);
   settextstyle(25, 0, _T("KaiTi"));
   outtextxy(150, 475, _T("1. ��ʼ"));
   outtextxy(525, 475, _T("2. ��Ϸ˵��"));
   outtextxy(950, 475, _T("ESC. �˳�"));
   settextcolor(BROWN);
   setbkcolor(0xe0e0d0); // background

   while (true) {
       // ����������12��esc
       if (GetAsyncKeyState('1') & 0x8000) return 1;
       if (GetAsyncKeyState('2') & 0x8000) return 2;
       if (GetAsyncKeyState(27) & 0x8000) return 3;

       // �����Ҳ�ɱ���
       if (MouseHit()) {
           MOUSEMSG m = GetMouseMsg();
           if (m.uMsg == WM_LBUTTONDOWN) {
               if (m.y >= 450 && m.y <= 530) {
                   if (m.x >= 100 && m.x <= 300) return 1;
                   if (m.x >= 500 && m.x <= 700) return 2;
                   if (m.x >= 900 && m.x <= 1100) return 3;
               }
           }
       }
       Sleep(10); // ��ֹCPUռ�ù���
   }
};  

int check(int** puz, int k) {//���ƴͼ�Ƿ�ԭ
    int r = k;
    int** last = new int* [r];//������ȷ��ƴͼģ��
    for (int i = 0; i < r; i++) {
        last[i] = new int[r];
    }
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            last[i][j] = (i*k + j + 1)%(r*r);
        }
    }
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            printf("%d ", last[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < r; j++) {
            if (last[i][j]!= puz[i][j]) {
                return 1;
            }
        }
    }
    return 0;
}
int drawpuz(int** puz, int k) {//�����޸ĺ��ͼ��
    int imgSize = 250-(k-3)*50; // ÿ��ƴͼ�����ʾ��С���ɸ���ʵ�ʵ���
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            TCHAR imgPath[100];
            swprintf_s(imgPath, _T("image/%d.png"), puz[i][j]);
            IMAGE img;
            loadimage(&img, imgPath, imgSize, imgSize, true);
            putimage(400 + j * imgSize, 100 + i * imgSize, &img);
            TCHAR numStr[10];
            swprintf_s(numStr, _T("%d"), puz[i][j]);
            outtextxy(400 + j * imgSize, 100 + i * imgSize, numStr);
        }
    }
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            printf("%d ", puz[i][j]);
        }
        printf("\n");
    }
    return 0;
}
void showcostom(int**puz,int i,int k) {//�ҳ������ĸ���ͳ�Ļ�����,�������
    int x = i / k;
    int y = i % k;
    int n = puz[x][y];
    printf("No.%d puz %d %d\n", n,x,y);
    //cleardevice();
    //drawpuz(puz, k);
    setfillcolor(0xe0e0d0);
    fillrectangle(20, 200, 395, 450);
    switch (n) {
        case 1:
            outtextxy(20, 250, _T("����:�й����⣬�ںϳ�������"));
            outtextxy(20, 290, _T("������������ɫ�Ը񣬽�����ʽ"));
            outtextxy(20, 330, _T("�����ݣ������Ŀ�������𼧡�"));
            outtextxy(20, 370, _T("��������ơ���"));
            break;
        case 2:
            outtextxy(20, 250, _T("�й���:�Ժ�ɫ˿�߱�֯�ļ���"));
            outtextxy(20, 290, _T("װ�Σ���ʽ���������̳��ᡢ"));
            outtextxy(20, 330, _T("����ᣩ�������Žᡢ���ˣ�"));
            outtextxy(20, 370, _T("�����ڽ���������"));
            break;
        case 3:
            outtextxy(20, 250, _T("��ֽ:�ü�����̵��ں�ֽ�ϴ���"));
            outtextxy(20, 290, _T("�ο�ͼ������Ķ�Ϊ����������"));
            outtextxy(20, 330, _T("���׹��£��Ǵ��ڴ�������Ҫ"));
            outtextxy(20, 370, _T("��ʽ��"));
            break;
        case 4:
            outtextxy(20, 250, _T("�鷨:��ë����д���ֵ�������"));
            outtextxy(20, 290, _T("�����ʷ����ṹ���·�����"));
            outtextxy(20, 330, _T("׭�����в����壬��������"));
            outtextxy(20, 370, _T("��������ѧ��"));
            break;
        case 5:
            outtextxy(20, 250, _T("����:ˮīΪ�꣬׷������"));
            outtextxy(20, 290, _T("��������ɽˮ����������"));
            outtextxy(20, 330, _T("���ƣ������쾳����������"));
            outtextxy(20, 370, _T("��һ��ѧ��"));
            break;
        case 6:
            outtextxy(20, 250, _T("��������:�й����ɹ���������"));
            outtextxy(20, 290, _T("�໨���۲ʵȹ����������δ�"));
            outtextxy(20, 330, _T("�����Ҥ����ٸ������"));
            outtextxy(20, 370, _T("�������۷塣"));
            break;
        case 7:
            outtextxy(20, 250, _T("��������:�Ĵ����壨��������"));
            outtextxy(20, 290, _T("������ɫ��������ʡ�˿Ϊī��"));
            outtextxy(20, 330, _T("�������ɽˮ�����ʵ����"));
            outtextxy(20, 370, _T("�ղؼ�ֵ��"));
            break;
        case 8:
            outtextxy(20, 250, _T("ƤӰϷ������Ƥ�����ż�����"));
            outtextxy(20, 290, _T("��ͶӰ��Ļ�����ݣ����Գ�ǻ��"));
            outtextxy(20, 330, _T("�������ǹ��ϵ����¹�Ӱ������"));
            break;
        case 9:
            outtextxy(20, 250, _T("��������Ǿ��棬����ͼ��ʫ��"));
            outtextxy(20, 290, _T("Ԫ���ƻ�Ϊ���ĳ�����������Բ"));
            outtextxy(20, 330, _T("�����������Ϊ��ͳ�������š�"));
            break;
        case 10:
            outtextxy(20, 250, _T("���ӣ����ȡ�����Ϊ������ʿ��"));
            outtextxy(20, 290, _T("���������黭�㻳�������赸��"));
            outtextxy(20, 330, _T("�ߣ��̺�������������Ķ���"));
            outtextxy(20, 370, _T("�⾳��"));
            break;
        case 11:
            outtextxy(20, 250, _T("���ݣ��ųơ�ֽ𰡱������Ϊ��"));
            outtextxy(20, 290, _T("��ֽΪ���������м��أ�Ϋ��"));
            outtextxy(20, 330, _T("���ݽ�����ǧ�꼼����ͯȤ��"));
            break;
        case 12:
            outtextxy(20, 250, _T("�����������������������Ŷ�ż"));
            outtextxy(20, 290, _T("ʫ�ģ���ֽ���֣�ƽ�ƹ�����"));
            outtextxy(20, 330, _T("�������а��Ը����"));
            break;
        case 13:
            outtextxy(20, 250, _T("�껭��ľ����ɫӡˢ���滭��"));
            outtextxy(20, 290, _T("���񡢸���Ϊ������ģ����"));
            outtextxy(20, 330, _T("�����ࡢ�����һ����ʢ����"));
            break;
        case 14:
            outtextxy(20, 250, _T("ӡ�£���ʯ���Կ����������£�"));
            outtextxy(20, 290, _T("׭��Ϊ�������ӡ�������黭��"));
            outtextxy(20, 330, _T("�����������Ʒζ�����"));
            break;
        case 15:
            outtextxy(20, 250, _T("���գ��Բ���������ʽ��"));
            outtextxy(20, 290, _T("�����������ݵ�Ʒ�������ǹ죬"));
            outtextxy(20, 330, _T("���֡��;���š�����ѧ˼�롣"));
            break;
        case 16:
            outtextxy(20, 250, _T("Χ�壺�ųơ��ġ����ڰ�����Χ"));
            outtextxy(20, 290, _T("�ع�����������£��̺�������"));
            outtextxy(20, 330, _T("��������ۣ�Ϊ����֮һ��"));
            break;
        case 17:
            outtextxy(20, 250, _T("������ͳ�ơ����򡱣��������"));
            outtextxy(20, 290, _T("ȭ�֣���̫�������֣�������£�"));
            outtextxy(20, 330, _T("�������뾫���˫��������"));
            break;
        case 18:
            outtextxy(20, 250, _T("���ǣ��Ŵ����·������̣�����"));
            outtextxy(20, 290, _T("��������ǻ���Ѫ����������"));
            outtextxy(20, 330, _T("��������Ͳ����ľ���ͼ�ڡ�"));
            break;
        case 19:
            outtextxy(20, 250, _T("��ֽɡ����Ϊ�ǣ�ֽΪ�棬ͩ��"));
            outtextxy(20, 290, _T("��ˮ�����������ж���ʫ�⣬"));
            outtextxy(20, 330, _T("�ǰ������"));
            break;
        case 20:
            outtextxy(20, 250, _T("��ͳ��ʳ֮���ӣ�Ŵ�׹�����"));
            outtextxy(20, 290, _T("��Ҷ���������������ԭ����"));
            outtextxy(20, 330, _T("����ض��죨�������ա���ɳ"));
            outtextxy(20, 370, _T("�գ���Ԣ�ⰲ����"));
            break;
        case 21:
            outtextxy(20, 250, _T("�������Ŵ���ѧ�ɾ�׿��������"));
            outtextxy(20, 290, _T("����������ϵ����������Ϊ��ͳ"));
            outtextxy(20, 330, _T("���㹤�ߣ�����ھ�ʵ�ø�Ч��"));
            break;
        case 22:
            outtextxy(20, 250, _T("��ҩ������Ȼ��ľ������ҩ����"));
            outtextxy(20, 290, _T("��������ζ��������ʹ����ġ�"));
            outtextxy(20, 330, _T("�ι޵��Ʒ���������ۡ�"));
            break;
        case 23:
            outtextxy(20, 250, _T("�й����壺32�ӷ��г��Ӻ��磬"));
            outtextxy(20, 290, _T("�������䲩�ģ����������"));
            outtextxy(20, 330, _T("�����ͷ��β�������ĳ�����"));
            break;
        case 24:
            outtextxy(20, 250, _T("��ͳ���֣��������ף����̽�"));
            outtextxy(20, 290, _T("����Ϊ���������ḻ������"));
            outtextxy(20, 330, _T("�����á������ȣ������ź��"));
            outtextxy(20, 370, _T("���⾳Ӫ�졣"));
            break;
        default:
            break;
    }
}
int movepuz(int** puz,int k) {//wasd�����Լ�esc�������ʾ��ͳ�Ļ�����ʵ��
    int x=0; int y=0;
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            if (puz[i][j] == 0) {
                x = i; y = j;
            }
        }
    }
    while (1) {
        if (GetAsyncKeyState('W') & 0x8000 || GetAsyncKeyState(VK_UP) & 0x8000) {
            if (x > 0 && x < k) {
                int t = puz[x][y];
                puz[x][y] = puz[x - 1][y];
                puz[x - 1][y] = t;
            }
            break;
        }
        else if (GetAsyncKeyState('S') & 0x8000 || GetAsyncKeyState(VK_DOWN) & 0x8000) {
            if (x >= 0 && x < k-1) {
                int t = puz[x][y];
                puz[x][y] = puz[x + 1][y];
                puz[x + 1][y] = t;
            }
            break;
        }
        else if (GetAsyncKeyState('A') & 0x8000 || GetAsyncKeyState(VK_LEFT) & 0x8000) {
            if (y > 0 && y < k) {
                int t = puz[x][y];
                puz[x][y] = puz[x][y-1];
                puz[x][y-1] = t;
            }
            break;
        }
        else if (GetAsyncKeyState('D') & 0x8000 || GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            if (y >= 0 && y < k-1) {
                int t = puz[x][y];
                puz[x][y] = puz[x][y+1];
                puz[x][y+1] = t;
            }
            break;
        }
        else if (GetAsyncKeyState(27) & 0x8000) {
            return 1;
            break;
        }else if(MouseHit()) {//���λ���ж��Լ���ʾ��Ӧ�Ļ�
            MOUSEMSG m = GetMouseMsg();
            if (m.uMsg == WM_LBUTTONDOWN) {
                if (m.x >= 400 && m.x < k* (250 - (k - 3) * 50)+400&&m.y>=100&&m.y<= k*(250 - (k - 3) * 50)+100) {
                    int i = (m.x - 400) / (250 - (k - 3) * 50) + k *((m.y - 100) / (250 - (k - 3) * 50));//y,problem
                    printf("inputnumber=%d\n", i);
                    showcostom(puz,i,k);
                }
            }
        }
    }
    return 0;
}
int show_puzzle() {
    playSoundEffect(_T("music\\tick.wav"));
    cleardevice();
    settextstyle(30, 0, _T("KaiTi"));
    settextcolor(BROWN);
    outtextxy(10, 10, _T("===׼����ʼƴͼ��Ϸ===\n"));
    outtextxy(10, 50, _T("��ѡ���Ѷȣ�3-5��"));
    // ���ư�ť
    setfillcolor(LIGHTBLUE);
    fillrectangle(100, 450, 300, 530);
    fillrectangle(500, 450, 700, 530);
    fillrectangle(900, 450, 1100, 530);
    settextcolor(WHITE);
    setbkcolor(LIGHTBLUE);
    settextstyle(25, 0, _T("KaiTi"));
    outtextxy(190, 475, _T("3"));
    outtextxy(590, 475, _T("4"));
    outtextxy(990, 475, _T("5"));
    settextcolor(BROWN);
    setbkcolor(0xe0e0d0); // background
    while (true) {
        // ����������345
        if (GetAsyncKeyState('3') & 0x8000) { 
            outtextxy(10, 90, _T("��ѡ���Ѷ�3"));
            Sleep(500);
            return 3; 
        }
        if (GetAsyncKeyState('4') & 0x8000) { 
            outtextxy(10, 90, _T("��ѡ���Ѷ�4"));
            Sleep(500);
            return 4;
        }
        if (GetAsyncKeyState('5') & 0x8000) {
            outtextxy(10, 90, _T("��ѡ���Ѷ�5"));
            Sleep(500);
            return 5;
        }

        // �����Ҳ�ɱ���
        if (MouseHit()) {
            MOUSEMSG m = GetMouseMsg();
            if (m.uMsg == WM_LBUTTONDOWN) {
                if (m.y >= 450 && m.y <= 530) {
                    if (m.x >= 100 && m.x <= 300) {
                        outtextxy(10, 90, _T("��ѡ���Ѷ�3"));
                        Sleep(500);
                        return 3;
                    }
                    if (m.x >= 500 && m.x <= 700) {
                        outtextxy(10, 90, _T("��ѡ���Ѷ�4"));
                        Sleep(500);
                        return 4;
                    }
                    if (m.x >= 900 && m.x <= 1100) { 
                        outtextxy(10, 90, _T("��ѡ���Ѷ�5"));
                        Sleep(500);
                        return 5;
                    }
                }
            }
        }
        Sleep(10); // ��ֹCPUռ�ù���
    }
    return 0;
}
void showSuccessPage(double usedSeconds,int step) {
    cleardevice();
    settextstyle(60, 0, _T("΢���ź�"));
    outtextxy(400, 300, _T("��ϲͨ�أ�"));
    settextstyle(40, 0, _T("΢���ź�"));
    TCHAR buf[64];
    _stprintf_s(buf, _T("��ʱ��%.2f �� �ƶ���%d ��"), usedSeconds,step);
    outtextxy(400, 400, buf);
    outtextxy(400, 500, _T("��E�������˵�"));
    while (1) { if (GetAsyncKeyState('E') & 0x8000) { return; } } // �ȴ��û�����
}
void initpuzzle(int k) {  //����ƴͼ������
   int r = k;  
   int** puz = new int*[r]; // ��̬�����ά����,��Ϊƴͼ�ı��ʹ��
   for (int i = 0; i < r; i++) {  
       puz[i] = new int[r];  
   }  
   for (int i = 0; i < k; i++) {  
       for (int j = 0; j < k; j++) {  
           puz[i][j] = i * k + j;  
       }  
   }
   for (int i = 0; i < 2*k; i++) {//����������飬Ȼ��׼������ƴͼ����
       int x = rand() % r;
       int y = rand() % r;
       int z = rand() % r;
       int w = rand() % r;
       int t = puz[x][y];
       puz[x][y] = puz[z][w];
       puz[z][w] = t;
   }

   cleardevice();
   outtextxy(10, 10, _T("===��ʼƴͼ��Ϸ!===\n"));
   outtextxy(10, 50, _T("���ͣ�ʹ��wasd������ƶ�ƴͼ"));
   outtextxy(10, 90, _T("ESC�������˵�"));
   playSoundEffect(_T("music\\tick.wav"));

   drawpuz(puz,r);//���ɽ���
   time(&startTime);
   int a=0;
   int step = 0;
   while (check(puz, r)) {
       a=movepuz(puz,r);
       playSoundEffect(_T("music\\tick.wav"));
       drawpuz(puz, r);
       Sleep(50);
       if (a == 1) {
           break;
       }
       else if (a == 0) {
           step++;
       }
       TCHAR buf[64];
       _stprintf_s(buf, _T("���ƶ��� % d ��"), step);
       outtextxy(10, 130, buf);
   }
   //Sleep(2000);
   //step = 50;
   time(&endTime);
   if (a == 0) {
       showSuccessPage(difftime(endTime, startTime),step);
   }
   printf("׼���ͷ��ڴ�");
   // �ͷŶ�̬������ڴ�
   for (int i = 0; i < r; i++) {  
       delete[] puz[i];  
   }  
   delete[] puz;  
}
void show_hint() {
    playSoundEffect(_T("music\\tick.wav"));
    cleardevice();
    settextstyle(30, 0, _T("KaiTi"));
    settextcolor(BROWN);
    outtextxy(220, 10, _T("                   ===��Ϸ˵��==="));
    outtextxy(220, 50, _T("����һ����ͳ�Ļ����������ƴͼ��Ϸ��Ŀ����ͨ���ƶ�ƴͼ�飬"));
    outtextxy(220, 90, _T("           ʹ�������ְ�˳�����У����½�Ϊ�հ׸�"));
    settextcolor(BLACK);
    settextstyle(25, 0, _T("KaiTi"));
    outtextxy(500, 130, _T("����� - �ƶ�ƴͼ"));
    outtextxy(500, 250, _T("ESC - �˳���Ϸ"));
    outtextxy(500, 370, _T("���ͼ����Բ鿴��ͳ�Ļ�Ԫ��"));
    outtextxy(500, 490, _T("��E������귵�����˵�..."));
    while (1) {
        if (GetAsyncKeyState('E') & 0x8000) {
            break;
        }
        if (MouseHit()) {
            MOUSEMSG m = GetMouseMsg();
            if (m.uMsg == WM_LBUTTONDOWN) {
                break;
            }
        }
        Sleep(10);
    }
}
int main() {  
    // ���ű�������
    mciSendString(_T("open \"music\\music.mp3\" alias bgm"), NULL, 0, NULL);
    mciSendString(_T("play bgm repeat"), NULL, 0, NULL);
    initgraph(1280, 900,EX_WINDOW);//�ٻ�ͼ�λ�����
    setbkcolor(0xe0e0d0); // background  

    while (1) {
        int i = show_menu();
        if (i == 1) {
            int k = show_puzzle();//�õ�ƴͼ����
            initpuzzle(k);//����
        }
        else if (i == 2) {
            show_hint();
            printf("���ڿ���\n");
        }
        else if (i == 3) {
            // �ر�����
            mciSendString(_T("close bgm"), NULL, 0, NULL);
            return 0;
        }
        printf("%d\n", i);
    }
    return 0;
}