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
}//y音效
int show_menu() {
   cleardevice();  
   settextstyle(40, 0, _T("KaiTi"));
   settextcolor(BROWN);  
   outtextxy(200,220, _T("              ===拼图游戏===\n"));
   outtextxy(200,300, _T("请选择：1. 开始游戏  2. 游戏说明  ESC. 退出"));
   // 绘制按钮
   setfillcolor(LIGHTBLUE);
   fillrectangle(100, 450, 300, 530);
   fillrectangle(500, 450, 700, 530);
   fillrectangle(900, 450, 1100, 530);
   settextcolor(WHITE);
   setbkcolor(LIGHTBLUE);
   settextstyle(25, 0, _T("KaiTi"));
   outtextxy(150, 475, _T("1. 开始"));
   outtextxy(525, 475, _T("2. 游戏说明"));
   outtextxy(950, 475, _T("ESC. 退出"));
   settextcolor(BROWN);
   setbkcolor(0xe0e0d0); // background

   while (true) {
       // 检测键盘输入12，esc
       if (GetAsyncKeyState('1') & 0x8000) return 1;
       if (GetAsyncKeyState('2') & 0x8000) return 2;
       if (GetAsyncKeyState(27) & 0x8000) return 3;

       // 鼠标点击也可保留
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
       Sleep(10); // 防止CPU占用过高
   }
};  

int check(int** puz, int k) {//检查拼图是否复原
    int r = k;
    int** last = new int* [r];//生成正确的拼图模板
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
int drawpuz(int** puz, int k) {//画出修改后的图像
    int imgSize = 250-(k-3)*50; // 每个拼图块的显示大小，可根据实际调整
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
void showcostom(int**puz,int i,int k) {//找出生成哪个传统文化介绍,并且输出
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
            outtextxy(20, 250, _T("京剧:中国国粹，融合唱念做打，"));
            outtextxy(20, 290, _T("以脸谱象征角色性格，讲究程式"));
            outtextxy(20, 330, _T("化表演，代表剧目《霸王别姬》"));
            outtextxy(20, 370, _T("《贵妃醉酒》。"));
            break;
        case 2:
            outtextxy(20, 250, _T("中国结:以红色丝线编织的吉祥"));
            outtextxy(20, 290, _T("装饰，结式多样（如盘长结、"));
            outtextxy(20, 330, _T("如意结），象征团结、福运，"));
            outtextxy(20, 370, _T("常用于节日馈赠。"));
            break;
        case 3:
            outtextxy(20, 250, _T("剪纸:用剪刀或刻刀在红纸上创作"));
            outtextxy(20, 290, _T("镂空图案，题材多为吉祥纹样、"));
            outtextxy(20, 330, _T("民俗故事，是春节窗花的主要"));
            outtextxy(20, 370, _T("形式。"));
            break;
        case 4:
            outtextxy(20, 250, _T("书法:以毛笔书写汉字的艺术，"));
            outtextxy(20, 290, _T("讲究笔法、结构、章法，分"));
            outtextxy(20, 330, _T("篆隶楷行草五体，承载文人"));
            outtextxy(20, 370, _T("精神与美学。"));
            break;
        case 5:
            outtextxy(20, 250, _T("国画:水墨为魂，追求“气韵"));
            outtextxy(20, 290, _T("生动”分山水、花鸟、人物"));
            outtextxy(20, 330, _T("三科，留白造境，体现天人"));
            outtextxy(20, 370, _T("合一哲学。"));
            break;
        case 6:
            outtextxy(20, 250, _T("瓷器艺术:中国“瓷国”象征，"));
            outtextxy(20, 290, _T("青花、粉彩等工艺闻名，宋代"));
            outtextxy(20, 330, _T("五大名窑（汝官哥钧定）"));
            outtextxy(20, 370, _T("代表技艺巅峰。"));
            break;
        case 7:
            outtextxy(20, 250, _T("刺绣艺术:四大名绣（苏湘粤蜀）"));
            outtextxy(20, 290, _T("各具特色，以针代笔、丝为墨，"));
            outtextxy(20, 330, _T("绣出花鸟山水，兼具实用与"));
            outtextxy(20, 370, _T("收藏价值。"));
            break;
        case 8:
            outtextxy(20, 250, _T("皮影戏：用兽皮雕刻人偶，借灯"));
            outtextxy(20, 290, _T("光投影于幕布表演，配以唱腔与"));
            outtextxy(20, 330, _T("乐器，是古老的叙事光影艺术。"));
            break;
        case 9:
            outtextxy(20, 250, _T("灯笼：竹骨绢面，绘有图案诗词"));
            outtextxy(20, 290, _T("元宵灯会为核心场景，象征团圆"));
            outtextxy(20, 330, _T("光明，红灯笼为传统建筑符号。"));
            break;
        case 10:
            outtextxy(20, 250, _T("扇子：折扇、团扇为文人雅士必"));
            outtextxy(20, 290, _T("备，扇面书画抒怀，亦作舞蹈道"));
            outtextxy(20, 330, _T("具，蕴含“清风徐来”的东方"));
            outtextxy(20, 370, _T("意境。"));
            break;
        case 11:
            outtextxy(20, 250, _T("风筝：古称“纸鸢”，以竹为架"));
            outtextxy(20, 290, _T("彩纸为翼，春秋已有记载，潍坊"));
            outtextxy(20, 330, _T("风筝节延续千年技艺与童趣。"));
            break;
        case 12:
            outtextxy(20, 250, _T("对联：春节门旁张贴的竖排对偶"));
            outtextxy(20, 290, _T("诗文，红纸金字，平仄工整，"));
            outtextxy(20, 330, _T("表达祈福驱邪的愿景。"));
            break;
        case 13:
            outtextxy(20, 250, _T("年画：木版套色印刷民间绘画，"));
            outtextxy(20, 290, _T("门神、福娃为经典题材，天津"));
            outtextxy(20, 330, _T("杨柳青、苏州桃花坞最负盛名。"));
            break;
        case 14:
            outtextxy(20, 250, _T("印章：以石材镌刻姓名或闲章，"));
            outtextxy(20, 290, _T("篆书为主，朱红印泥钤于书画，"));
            outtextxy(20, 330, _T("是作者身份与品味的信物。"));
            break;
        case 15:
            outtextxy(20, 250, _T("茶艺：以茶修身的生活方式，"));
            outtextxy(20, 290, _T("从择器、冲泡到品饮皆有仪轨，"));
            outtextxy(20, 330, _T("体现“和敬清寂”的哲学思想。"));
            break;
        case 16:
            outtextxy(20, 250, _T("围棋：古称“弈”，黑白棋子围"));
            outtextxy(20, 290, _T("地攻防，策略深奥，蕴含兵法智"));
            outtextxy(20, 330, _T("慧与宇宙观，为四艺之一。"));
            break;
        case 17:
            outtextxy(20, 250, _T("武术：统称“功夫”，分内外家"));
            outtextxy(20, 290, _T("拳种（如太极、少林），重武德，"));
            outtextxy(20, 330, _T("是身体与精神的双重修炼。"));
            break;
        case 18:
            outtextxy(20, 250, _T("长城：古代军事防御工程，绵延"));
            outtextxy(20, 290, _T("万里，凝聚智慧与血汗，象征中"));
            outtextxy(20, 330, _T("华民族坚韧不屈的精神图腾。"));
            break;
        case 19:
            outtextxy(20, 250, _T("油纸伞：竹为骨，纸为面，桐油"));
            outtextxy(20, 290, _T("防水，江南烟雨中独具诗意，"));
            outtextxy(20, 330, _T("是爱情信物。"));
            break;
        case 20:
            outtextxy(20, 250, _T("传统美食之粽子：糯米裹馅以"));
            outtextxy(20, 290, _T("箬叶捆扎，端午纪念屈原，咸"));
            outtextxy(20, 330, _T("甜因地而异（如鲜肉粽、豆沙"));
            outtextxy(20, 370, _T("粽），寓意安康。"));
            break;
        case 21:
            outtextxy(20, 250, _T("算术：古代数学成就卓著，《九"));
            outtextxy(20, 290, _T("章算术》体系完整，算盘为传统"));
            outtextxy(20, 330, _T("计算工具，珠算口诀实用高效。"));
            break;
        case 22:
            outtextxy(20, 250, _T("中药：以自然草木矿物入药，讲"));
            outtextxy(20, 290, _T("究四气五味、君臣佐使，针灸、"));
            outtextxy(20, 330, _T("拔罐等疗法体现整体观。"));
            break;
        case 23:
            outtextxy(20, 250, _T("中国象棋：32子分列楚河汉界，"));
            outtextxy(20, 290, _T("车马炮卒博弈，规则简而变局"));
            outtextxy(20, 330, _T("无穷，街头巷尾常见对弈场景。"));
            break;
        case 24:
            outtextxy(20, 250, _T("传统音乐：五声音阶（宫商角"));
            outtextxy(20, 290, _T("徵羽）为基，乐器丰富（古琴"));
            outtextxy(20, 330, _T("、琵琶、二胡等），典雅含蓄，"));
            outtextxy(20, 370, _T("重意境营造。"));
            break;
        default:
            break;
    }
}
int movepuz(int** puz,int k) {//wasd操作以及esc，点击显示传统文化功能实现
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
        }else if(MouseHit()) {//点击位置判断以及显示对应文化
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
    outtextxy(10, 10, _T("===准备开始拼图游戏===\n"));
    outtextxy(10, 50, _T("请选择难度（3-5）"));
    // 绘制按钮
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
        // 检测键盘输入345
        if (GetAsyncKeyState('3') & 0x8000) { 
            outtextxy(10, 90, _T("已选择：难度3"));
            Sleep(500);
            return 3; 
        }
        if (GetAsyncKeyState('4') & 0x8000) { 
            outtextxy(10, 90, _T("已选择：难度4"));
            Sleep(500);
            return 4;
        }
        if (GetAsyncKeyState('5') & 0x8000) {
            outtextxy(10, 90, _T("已选择：难度5"));
            Sleep(500);
            return 5;
        }

        // 鼠标点击也可保留
        if (MouseHit()) {
            MOUSEMSG m = GetMouseMsg();
            if (m.uMsg == WM_LBUTTONDOWN) {
                if (m.y >= 450 && m.y <= 530) {
                    if (m.x >= 100 && m.x <= 300) {
                        outtextxy(10, 90, _T("已选择：难度3"));
                        Sleep(500);
                        return 3;
                    }
                    if (m.x >= 500 && m.x <= 700) {
                        outtextxy(10, 90, _T("已选择：难度4"));
                        Sleep(500);
                        return 4;
                    }
                    if (m.x >= 900 && m.x <= 1100) { 
                        outtextxy(10, 90, _T("已选择：难度5"));
                        Sleep(500);
                        return 5;
                    }
                }
            }
        }
        Sleep(10); // 防止CPU占用过高
    }
    return 0;
}
void showSuccessPage(double usedSeconds,int step) {
    cleardevice();
    settextstyle(60, 0, _T("微软雅黑"));
    outtextxy(400, 300, _T("恭喜通关！"));
    settextstyle(40, 0, _T("微软雅黑"));
    TCHAR buf[64];
    _stprintf_s(buf, _T("用时：%.2f 秒 移动：%d 步"), usedSeconds,step);
    outtextxy(400, 400, buf);
    outtextxy(400, 500, _T("按E返回主菜单"));
    while (1) { if (GetAsyncKeyState('E') & 0x8000) { return; } } // 等待用户按键
}
void initpuzzle(int k) {  //生成拼图，打乱
   int r = k;  
   int** puz = new int*[r]; // 动态分配二维数组,作为拼图的编号使用
   for (int i = 0; i < r; i++) {  
       puz[i] = new int[r];  
   }  
   for (int i = 0; i < k; i++) {  
       for (int j = 0; j < k; j++) {  
           puz[i][j] = i * k + j;  
       }  
   }
   for (int i = 0; i < 2*k; i++) {//打乱这个数组，然后准备生成拼图界面
       int x = rand() % r;
       int y = rand() % r;
       int z = rand() % r;
       int w = rand() % r;
       int t = puz[x][y];
       puz[x][y] = puz[z][w];
       puz[z][w] = t;
   }

   cleardevice();
   outtextxy(10, 10, _T("===开始拼图游戏!===\n"));
   outtextxy(10, 50, _T("加油！使用wasd或方向键移动拼图"));
   outtextxy(10, 90, _T("ESC返回主菜单"));
   playSoundEffect(_T("music\\tick.wav"));

   drawpuz(puz,r);//生成界面
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
       _stprintf_s(buf, _T("已移动： % d 步"), step);
       outtextxy(10, 130, buf);
   }
   //Sleep(2000);
   //step = 50;
   time(&endTime);
   if (a == 0) {
       showSuccessPage(difftime(endTime, startTime),step);
   }
   printf("准备释放内存");
   // 释放动态分配的内存
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
    outtextxy(220, 10, _T("                   ===游戏说明==="));
    outtextxy(220, 50, _T("这是一个传统文化主题的数字拼图游戏，目标是通过移动拼图块，"));
    outtextxy(220, 90, _T("           使所有数字按顺序排列，右下角为空白格。"));
    settextcolor(BLACK);
    settextstyle(25, 0, _T("KaiTi"));
    outtextxy(500, 130, _T("方向键 - 移动拼图"));
    outtextxy(500, 250, _T("ESC - 退出游戏"));
    outtextxy(500, 370, _T("点击图标可以查看传统文化元素"));
    outtextxy(500, 490, _T("按E或点击鼠标返回主菜单..."));
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
    // 播放背景音乐
    mciSendString(_T("open \"music\\music.mp3\" alias bgm"), NULL, 0, NULL);
    mciSendString(_T("play bgm repeat"), NULL, 0, NULL);
    initgraph(1280, 900,EX_WINDOW);//召唤图形化界面
    setbkcolor(0xe0e0d0); // background  

    while (1) {
        int i = show_menu();
        if (i == 1) {
            int k = show_puzzle();//得到拼图阶数
            initpuzzle(k);//生成
        }
        else if (i == 2) {
            show_hint();
            printf("还在开发\n");
        }
        else if (i == 3) {
            // 关闭音乐
            mciSendString(_T("close bgm"), NULL, 0, NULL);
            return 0;
        }
        printf("%d\n", i);
    }
    return 0;
}